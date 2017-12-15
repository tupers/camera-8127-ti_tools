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

#include "VLIB_histogram_1D_U16.h"
#include "VLIB_histogram_1D_U16_cn.h"
#include "VLIB_histogram_1D_U16_idat.h"

#include "../VLIB_histogram_1D_Init_U16/VLIB_histogram_1D_Init_U16_cn.h"

/*VLIB_histogram_1D_U16_d:  Test Driver Routine */
void VLIB_histogram_1D_U16_d (uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    histogram_1D_U16_testParams_t   *prm;

    histogram_1D_U16_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_histogram_1D_U16");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Allocate buffers for each test vector */
        uint16_t   *binEdges       =  (uint16_t *) VLIB_malloc(prm[tpi].numBins * sizeof(uint16_t));
        uint16_t   *histArray      =  (uint16_t *) VLIB_malloc(prm[tpi].maxSize * sizeof(uint16_t));
        uint16_t   *X              =  (uint16_t *) VLIB_malloc(prm[tpi].numX * sizeof(uint16_t));
        uint16_t   *H              =  (uint16_t *) VLIB_malloc(prm[tpi].numBins * sizeof(uint16_t));
        uint16_t   *H_cn           =  (uint16_t *) malloc(prm[tpi].numBins * sizeof(uint16_t));
        uint16_t   *H1             =  (uint16_t *) VLIB_malloc(prm[tpi].numBins * sizeof(uint16_t));

        /* Only run the test if the buffer allocations fit in the heap */
        if( binEdges && histArray && X && H && H_cn && H1 ) {

            int32_t    fail, i;

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(STATIC,
                            (uint16_t)1,
                            binEdges, prm[tpi].staticInEdges,
                            prm[tpi].numBins, 1, prm[tpi].numBins * sizeof(binEdges[0]),
                            sizeof(binEdges[0]), testPatternString);

            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint16_t)1,
                            X, prm[tpi].staticInImg,
                            prm[tpi].numX, 1, prm[tpi].numX * sizeof(X[0]),
                            sizeof(X[0]), testPatternString);

            for( i=0; i < prm[tpi].numX; i++ ) {
                if( X[i] > prm[tpi].maxSize - 1 ) {
                    X[i] = prm[tpi].maxSize - 1;
                }
            }

            /* Clear the histArray and run init fn, as per init fn requirement */
            memset(histArray, 0, prm[tpi].maxSize * sizeof(uint16_t));
            /* The natC version of this vlib function is used so that the code size doesn't get counted in this test */
            VLIB_histogram_1D_Init_U16_cn(binEdges, prm[tpi].numBins, histArray);

            /* Clear the H arrays, as per fn requirement */
            memset(H, 0, prm[tpi].numBins * sizeof(uint16_t));
            memset(H1, 0, prm[tpi].numBins * sizeof(uint16_t));

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            VLIB_histogram_1D_U16(X, prm[tpi].numX, prm[tpi].numBins, prm[tpi].binWeight, histArray, H1, H);
            VLIB_profile_stop();

            /* Clear the H arrays, as per fn requirement */
            memset(H_cn, 0, prm[tpi].numBins * sizeof(uint16_t));
            memset(H1, 0, prm[tpi].numBins * sizeof(uint16_t));

            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_histogram_1D_U16_cn(X, prm[tpi].numX, prm[tpi].numBins, prm[tpi].binWeight, histArray, H1, H_cn);
            VLIB_profile_stop();


            /* Compare natural C Output and Optimized Output */
            status_nat_vs_int = VLIB_compare_mem((void *) H, (void *)H_cn, prm[tpi].numBins * sizeof(uint16_t));

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOut != NULL ) {
                status_nat_vs_ref = VLIB_compare_mem((void *) prm[tpi].staticOut, (void *)H_cn, prm[tpi].numBins * sizeof(uint16_t));
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt results compared to NatC results | numBins=%d, maxSize=%d, numX=%d",
                    testPatternString, prm[tpi].numBins, prm[tpi].maxSize, prm[tpi].numX);
            VLIB_formula_add_test(prm[tpi].numX, NULL, NULL, fail, desc, NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "numBins=%d, maxSize=%d, numX=%d",
                    prm[tpi].numBins, prm[tpi].maxSize, prm[tpi].numX);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        VLIB_free(H1);
        free(H_cn);
        VLIB_free(H);
        VLIB_free(X);
        VLIB_free(histArray);
        VLIB_free(binEdges);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = numX",
                              "numX");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_histogram_1D_U16");
    } else {
        VLIB_histogram_1D_U16_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_histogram_1D_U16_d.c                                 */
/* ======================================================================== */

