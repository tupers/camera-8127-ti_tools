#include <common.h>
#include <command.h>

int do_menu(cmd_tbl_t *cmdtp,int flag,int argc,char *argv[])
{
	printf("do menu test\n");
}


U_BOOT_CMD(
	menu,3,0,do_menu,
	"menu - display a menu,to select the items to do something\n",
	"-display a menu,to select the items to do something"
);
