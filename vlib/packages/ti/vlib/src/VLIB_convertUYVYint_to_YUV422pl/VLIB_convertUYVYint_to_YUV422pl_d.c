/*******************************************************************************
**+--------------------------------------------------------------------------+**
**|                            ****                                          |**
**|                            ****                                          |**
**|                            ******o***                                    |**
**|                      ********_///_****                                   |**
**|                      ***** /_//_/ ****                                   |**
**|                       ** ** (__/ ****                                    |**
**|                           *********                                      |**
**|                            ****                                          |**
**|                            ***                                           |**
**|                                                                          |**
**|         Copyright (c) 2007-2014 Texas Instruments Incorporated           |**
**|                        ALL RIGHTS RESERVED                               |**
**|                                                                          |**
**| Permission to use, copy, modify, or distribute this software,            |**
**| whether in part or in whole, for any purpose is forbidden without        |**
**| a signed licensing agreement and NDA from Texas Instruments              |**
**| Incorporated (TI).                                                       |**
**|                                                                          |**
**| TI makes no representation or warranties with respect to the             |**
**| performance of this computer program, and specifically disclaims         |**
**| any responsibility for any damages, special or consequential,            |**
**| connected with the use of this program.                                  |**
**|                                                                          |**
**+--------------------------------------------------------------------------+**
*******************************************************************************/

#include "../common/VLIB_test.h"
#include "../common/VLIB_memory.h"
#include "../common/VLIB_profile.h"

#include "VLIB_convertUYVYint_to_YUV422pl.h"
#include "VLIB_convertUYVYint_to_YUV422pl_cn.h"
#include "VLIB_convertUYVYint_to_YUV422pl_idat.h"

/* VLIB_convertUYVYint_to_YUV422pl_d:  Test Driver Routine */
void VLIB_convertUYVYint_to_YUV422pl_d (uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    UYVYint_to_YUV422pl_testParams_t   *prm;

    UYVYint_to_YUV422pl_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(3, "VLIB_convertUYVYint_to_YUV422pl");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Compute buffer sizes */
        uint32_t    inp_size   =  prm[tpi].pitch * prm[tpi].height * 2;
        uint32_t    out_luma   =  prm[tpi].width * prm[tpi].height;
        uint32_t    out_chroma =  prm[tpi].width * prm[tpi].height / 2;

        /* Allocate buffers for each test vector */
        uint8_t   *yc    = (uint8_t *) VLIB_memalign(8, inp_size);
        uint8_t   *y     = (uint8_t *) VLIB_memalign(8, out_luma);
        uint8_t   *cr    = (uint8_t *) VLIB_memalign(8, out_chroma);
        uint8_t   *cb    = (uint8_t *) VLIB_memalign(8, out_chroma);
        uint8_t   *y_cn  = (uint8_t *) malloc(out_luma);
        uint8_t   *cr_cn = (uint8_t *) malloc(out_chroma);
        uint8_t   *cb_cn = (uint8_t *) malloc(out_chroma);

        /* Only run the test if the buffer allocations fit in the heap */
        if( yc && y && cr && cb && y_cn && cr_cn && cb_cn ) {

            int32_t    fail, mode;

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)255,
                            yc, prm[tpi].staticIn,
                            prm[tpi].width, prm[tpi].height, prm[tpi].pitch * 2,
                            sizeof(uint16_t), testPatternString);

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            VLIB_convertUYVYint_to_YUV422pl(yc, prm[tpi].width, prm[tpi].pitch, prm[tpi].height, y, cr, cb);
            VLIB_profile_stop();

            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_convertUYVYint_to_YUV422pl_cn(yc, prm[tpi].width, prm[tpi].pitch, prm[tpi].height, y_cn, cr_cn, cb_cn);
            VLIB_profile_stop();


            /* Compare natural C Output and Optimized Output */
            if( VLIB_compare_mem((void *) y, (void *)y_cn, out_luma) == vlib_KERNEL_FAIL ||
                VLIB_compare_mem((void *) cr, (void *)cr_cn, out_chroma) == vlib_KERNEL_FAIL ||
                VLIB_compare_mem((void *) cb, (void *)cb_cn, out_chroma) == vlib_KERNEL_FAIL ) {
                status_nat_vs_int = vlib_KERNEL_FAIL;
            } else {
                status_nat_vs_int = vlib_KERNEL_PASS;
            }

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOutY != NULL &&
                prm[tpi].staticOutCr != NULL &&
                prm[tpi].staticOutCb != NULL ) {

                if( VLIB_compare_mem((void *) prm[tpi].staticOutY, (void *)y_cn, out_luma) == vlib_KERNEL_FAIL ||
                    VLIB_compare_mem((void *) prm[tpi].staticOutCr, (void *)cr_cn, out_chroma) == vlib_KERNEL_FAIL ||
                    VLIB_compare_mem((void *) prm[tpi].staticOutCb, (void *)cb_cn, out_chroma) == vlib_KERNEL_FAIL ) {
                    status_nat_vs_ref = vlib_KERNEL_FAIL;
                } else {
                    status_nat_vs_ref = vlib_KERNEL_PASS;
                }
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt results compared to NatC results | width=%d, pitch=%d, height=%d, num_pts=%d",
                    testPatternString, prm[tpi].width, prm[tpi].pitch, prm[tpi].height, out_luma);
            mode = (prm[tpi].pitch == prm[tpi].width) ? 1 : 2;
            VLIB_formula_add_test(out_luma, prm[tpi].height, NULL, fail, desc, mode);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "width=%d, pitch=%d, height=%d, num_pts=%d",
                    prm[tpi].width, prm[tpi].pitch, prm[tpi].height, out_luma);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        free(cb_cn);
        free(cr_cn);
        free(y_cn);
        VLIB_align_free(cb);
        VLIB_align_free(cr);
        VLIB_align_free(y);
        VLIB_align_free(yc);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_setMode(1, 2, "pitch == width", 0); /* Mode 1 */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = width * height",
                              "width * height");

    VLIB_profile_setMode(2, 3, "pitch > width", 1); /* Mode 2 */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = width * height; M = height",
                              "width * height");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_convertUYVYint_to_YUV422pl");
    } else {
        VLIB_convertUYVYint_to_YUV422pl_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_convertUYVYint_to_YUV422ple_d.c                      */
/* ======================================================================== */

