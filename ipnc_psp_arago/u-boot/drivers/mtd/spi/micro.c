/*
 * (C) Copyright 2000-2002
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * Copyright 2008, Network Appliance Inc.
 * Jason McMullan <mcmullan@netapp.com>
 *
 * Copyright (C) 2004-2007 Freescale Semiconductor, Inc.
 * TsiChung Liew (Tsi-Chung.Liew@freescale.com)
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include <malloc.h>
#include <spi_flash.h>

#include "spi_flash_internal.h"

/* M25Pxx-specific commands */
#define CMD_N25QXX_WREN		0x06	/* Write Enable */
#define CMD_N25QXX_WRDI		0x04	/* Write Disable */
#define CMD_N25QXX_RDSR		0x05	/* Read Status Register */
#define CMD_N25QXX_WRSR		0x01	/* Write Status Register */
#define CMD_N25QXX_READ		0x03	/* Read Data Bytes */
#define CMD_N25QXX_FAST_READ	0x0b	/* Read Data Bytes at Higher Speed */
#define CMD_N25QXX_PP		0x02	/* Page Program */
#define CMD_N25QXX_SE		0xd8	/* Sector Erase */
#define CMD_N25QXX_SBE		0x20	/* sub sector erase */
#define CMD_N25QXX_BE		0xc7	/* Bulk Erase */
#define CMD_N25QXX_DP		0xb9	/* Deep Power-down */
#define CMD_N25QXX_RES		0xab	/* Release from DP, and Read Signature */

#define MICRO_ID_N25Q256	0x19

#define MICRO_SR_WIP		(1 << 0)	/* Write-in-Progress */

struct micro_spi_flash_params {
	u8 idcode1;
	u16 page_size;
	u16 pages_per_sector;
	u16 nr_sectors;
	const char *name;
};

/* spi_flash needs to be first so upper layers can free() it */
struct micro_spi_flash {
	struct spi_flash flash;
	const struct micro_spi_flash_params *params;
};

static inline struct micro_spi_flash *to_micro_spi_flash(struct spi_flash
							     *flash)
{
	return container_of(flash, struct micro_spi_flash, flash);
}

static const struct micro_spi_flash_params micro_spi_flash_table[] = {
	{
		.idcode1 = MICRO_ID_N25Q256,
		.page_size = 256,
		.pages_per_sector = 256,
		.nr_sectors = 512,
		.name = "N25Q256",
	}
};

static int micro_wait_ready(struct spi_flash *flash, unsigned long timeout)
{
	struct spi_slave *spi = flash->spi;
	unsigned long timebase;
	int ret;
	u8 cmd = CMD_N25QXX_RDSR;
	u8 status;

	ret = spi_xfer(spi, 8, &cmd, NULL, SPI_XFER_BEGIN);
	if (ret) {
		debug("SF: Failed to send command %02x: %d\n", cmd, ret);
		return ret;
	}

	timebase = get_timer(0);
	do {
		ret = spi_xfer(spi, 8, NULL, &status, 0);
		if (ret)
			return -1;

		if ((status & MICRO_SR_WIP) == 0)
			break;

	} while (get_timer(timebase) < timeout);

	spi_xfer(spi, 0, NULL, NULL, SPI_XFER_END);

	if ((status & MICRO_SR_WIP) == 0)
		return 0;

	/* Timed out */
	return -1;
}

static int micro_read_fast(struct spi_flash *flash,
			     u32 offset, size_t len, void *buf)
{
	struct micro_spi_flash *stm = to_micro_spi_flash(flash);
	unsigned long page_addr;
	unsigned long page_size;
	u8 cmd[5];

	page_size = stm->params->page_size;
	page_addr = offset / page_size;

	cmd[0] = CMD_READ_ARRAY_FAST;
	cmd[1] = page_addr >> 8;
	cmd[2] = page_addr;
	cmd[3] = offset % page_size;
	cmd[4] = 0x00;

	return spi_flash_read_common(flash, cmd, sizeof(cmd), buf, len);
}

static int micro_write(struct spi_flash *flash,
			 u32 offset, size_t len, const void *buf)
{
	struct micro_spi_flash *stm = to_micro_spi_flash(flash);
	unsigned long page_addr;
	unsigned long byte_addr;
	unsigned long page_size;
	size_t chunk_len;
	size_t actual;
	int ret;
	u8 cmd[4];

	page_size = stm->params->page_size;
	page_addr = offset / page_size;
	byte_addr = offset % page_size;

	ret = spi_claim_bus(flash->spi);
	if (ret) {
		debug("SF: Unable to claim SPI bus\n");
		return ret;
	}

	ret = 0;
	for (actual = 0; actual < len; actual += chunk_len) {
		chunk_len = min(len - actual, page_size - byte_addr);

		cmd[0] = CMD_N25QXX_PP;
		cmd[1] = page_addr >> 8;
		cmd[2] = page_addr;
		cmd[3] = byte_addr;

		printf("PP: 0x%p => cmd = { 0x%02x 0x%02x%02x%02x } chunk_len = %d\n",
		     buf + actual, cmd[0], cmd[1], cmd[2], cmd[3], chunk_len);

		ret = spi_flash_cmd(flash->spi, CMD_N25QXX_WREN, NULL, 0);
		if (ret < 0) {
			debug("SF: Enabling Write failed\n");
			break;
		}

		ret = spi_flash_cmd_write(flash->spi, cmd, 4,
					  buf + actual, chunk_len);
		if (ret < 0) {
			debug("SF: Micro Page Program failed\n");
			break;
		}

		ret = micro_wait_ready(flash, SPI_FLASH_PROG_TIMEOUT);
		if (ret < 0) {
			debug("SF: Micro page programming timed out\n");
			break;
		}

		page_addr++;
		byte_addr = 0;
	}

	debug("SF: Micro: Successfully programmed %u bytes @ 0x%x\n",
	      len, offset);

	spi_release_bus(flash->spi);
	return ret;
}

int micro_erase(struct spi_flash *flash, u32 offset, size_t len)
{
	struct micro_spi_flash *stm = to_micro_spi_flash(flash);
	unsigned long sector_size;
	size_t actual;
	int ret;
	u8 cmd[4];

	/*
	 * This function currently uses sector erase only.
	 * probably speed things up by using bulk erase
	 * when possible.
	 */

	sector_size = stm->params->page_size * stm->params->pages_per_sector;

	if (offset % sector_size || len % sector_size) {
		debug("SF: Erase offset/length not multiple of sector size\n");
		return -1;
	}

	len /= sector_size;
	cmd[0] = CMD_N25QXX_SE;
	cmd[2] = 0x00;
	cmd[3] = 0x00;

	ret = spi_claim_bus(flash->spi);
	if (ret) {
		debug("SF: Unable to claim SPI bus\n");
		return ret;
	}

	ret = 0;
	for (actual = 0; actual < len; actual++) {
		cmd[1] = offset >> 16;
		offset += sector_size;

		ret = spi_flash_cmd(flash->spi, CMD_N25QXX_WREN, NULL, 0);
		if (ret < 0) {
			debug("SF: Enabling Write failed\n");
			break;
		}

		ret = spi_flash_cmd_write(flash->spi, cmd, 4, NULL, 0);
		if (ret < 0) {
			debug("SF: Micro page erase failed\n");
			break;
		}

		ret = micro_wait_ready(flash, SPI_FLASH_PAGE_ERASE_TIMEOUT);
		if (ret < 0) {
			debug("SF: Micro page erase timed out\n");
			break;
		}
	}

	debug("SF: STMicro: Successfully erased %u bytes @ 0x%x\n",
	      len * sector_size, offset);

	spi_release_bus(flash->spi);
	return ret;
}

struct spi_flash *spi_flash_probe_micro(struct spi_slave *spi, u8 * idcode)
{
	const struct micro_spi_flash_params *params;
	struct micro_spi_flash *stm;
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(micro_spi_flash_table); i++) {
		params = &micro_spi_flash_table[i];
		if (params->idcode1 == idcode[2]) {
			break;
		}
	}

	if (i == ARRAY_SIZE(micro_spi_flash_table)) {
		debug("SF: Unsupported STMicro ID %02x\n", idcode[1]);
		return NULL;
	}

	stm = malloc(sizeof(struct micro_spi_flash));
	if (!stm) {
		debug("SF: Failed to allocate memory\n");
		return NULL;
	}

	stm->params = params;
	stm->flash.spi = spi;
	stm->flash.name = params->name;

	stm->flash.write = micro_write;
	stm->flash.erase = micro_erase;
	stm->flash.read = micro_read_fast;
	stm->flash.size = params->page_size * params->pages_per_sector
	    * params->nr_sectors;

	debug("SF: Detected %s with page size %u, total %u bytes\n",
	      params->name, params->page_size, stm->flash.size);

	return &stm->flash;
}
