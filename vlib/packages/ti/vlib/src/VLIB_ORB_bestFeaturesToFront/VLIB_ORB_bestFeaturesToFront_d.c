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
**|         Copyright (c) 2007-2012 Texas Instruments Incorporated           |**
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
#include "../common/VLIB_orb_utilities.h"

#include "VLIB_ORB_bestFeaturesToFront.h"
#include "VLIB_ORB_bestFeaturesToFront_cn.h"
#include "VLIB_ORB_bestFeaturesToFront_idat.h"

void VLIB_ORB_bestFeaturesToFront_d(uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    orb_bestFeaturesToFront_testParams_t   *prm;

    orb_bestFeaturesToFront_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_ORB_bestFeaturesToFront");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* In this test, the number of features going into this function is already known in the test vector, so
         * it is being set here to the known size to minimize the memory usage for the test.  However, in an application,
         * the memory allocation for the number of features will be done before the features are found, so the memory
         * allocation should assume the MAX number of features supported by the feature detector : CORB_MAX_FEATURES */
        //uint32_t    nfeatures = CORB_MAX_FEATURES;           /* Typical in production */
        uint32_t    nfeatures = prm[tpi].true_num_features;   /* Used for the sake of this test for memory savings */

        /*  Initialization  */
        const CORBParameters    orbParams = getCORBParameters(prm[tpi].imageWidth, prm[tpi].imageHeight, 10, 20, prm[tpi].desired_num_features);
        uint32_t                orbScratchSize;

        /* Allocate buffers for each test vector */
        uint32_t     *dummyPtr      = (uint32_t *)1;
        CORBInput    *orbInput      = (CORBInput  *) malloc(sizeof(CORBInput));
        CORBOutput   *orbOutput     = (CORBOutput *) VLIB_malloc(sizeof(CORBOutput));
        CORBOutput   *orbOutput_cn  = (CORBOutput *) malloc(sizeof(CORBOutput));

        if( orbInput && orbOutput && orbOutput_cn ) {
            orbOutput->n_features       = prm[tpi].true_num_features;
            orbOutput->features         = (CORBFeature *) VLIB_malloc((nfeatures) * sizeof(CORBFeature));

            orbOutput_cn->n_features    = prm[tpi].true_num_features;
            orbOutput_cn->features      = (CORBFeature *) malloc((nfeatures) * sizeof(CORBFeature));

            /* In this test, the number of features going into this function is already known in the test vector, so
             * it used to set the scratch size to minimize the memory usage for the test.  However, in an application,
             * the memory allocation for the scratch could potentially be done before the features are found, so the memory
             * allocation should assume the MAX number of features supported by the feature detector, which is what the
             * getRequiredScratchSize() function already considers. */
            //orbScratchSize = getRequiredScratchSize(&orbParams, BOOL_FALSE, BOOL_TRUE);  /* Typical in production */
            orbScratchSize = (orbOutput->n_features + 1024) * 2;  /* Used for the sake of this test for memory savings */
            orbInput->scratchBuffer = (char *)VLIB_memalign(8, orbScratchSize);

        } else {
            dummyPtr = NULL;
        }

        /* Only run the test if the buffer allocations fit in the heap */
        if( dummyPtr && orbOutput->features && orbOutput_cn->features && orbInput->scratchBuffer ) {

            int32_t    fail;
            int32_t    i;

            /* Fill input arrays according to desired test pattern */
            for( i=0; i < prm[tpi].true_num_features; i++ ) {
                orbOutput->features[i].x = prm[tpi].staticInFeatures[2 * i];
                orbOutput_cn->features[i].x = prm[tpi].staticInFeatures[2 * i];
                orbOutput->features[i].y = prm[tpi].staticInFeatures[2 * i + 1];
                orbOutput_cn->features[i].y = prm[tpi].staticInFeatures[2 * i + 1];
                if( prm[tpi].testPattern == STATIC ) {
                    orbOutput->features[i].harrisResponse = prm[tpi].staticInHarris[i];
                    orbOutput_cn->features[i].harrisResponse = prm[tpi].staticInHarris[i];
                } else if( prm[tpi].testPattern == SEQUENTIAL ) {
                    orbOutput->features[i].harrisResponse = i;
                    orbOutput_cn->features[i].harrisResponse = i;
                } else if( prm[tpi].testPattern == SEQUENTIAL_NEGATIVE ) {
                    orbOutput->features[i].harrisResponse = -i;
                    orbOutput_cn->features[i].harrisResponse = -i;
                }
            }

            /* Calling with null pointers will only set the testPatternString variable */
            VLIB_fillBuffer(prm[tpi].testPattern, 0, NULL, NULL,
                            0, 0, 0, sizeof(uint8_t), testPatternString);

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            VLIB_ORB_bestFeaturesToFront(&orbParams, orbInput, orbOutput);
            VLIB_profile_stop();

            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_ORB_bestFeaturesToFront_cn(&orbParams, orbInput, orbOutput_cn);
            VLIB_profile_stop();

            /* Compare natural C Output and Optimized Output */
            for( i=0; i < orbOutput->n_features; i++ ) {
                if((orbOutput->features[i].x != orbOutput_cn->features[i].x) ||
                   (orbOutput->features[i].y != orbOutput_cn->features[i].y)) {
                    status_nat_vs_int = vlib_KERNEL_FAIL;
                    if( LevelOfFeedback > 0 ) {
                        printf(" Mismatch in Index = %u \n", i);
                    }
                    break;
                }
            }

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOut != NULL ) {
                for( i=0; i < orbOutput->n_features; i++ ) {
                    if((orbOutput_cn->features[i].x != prm[tpi].staticOut[2 * i]) ||
                       (orbOutput_cn->features[i].y != prm[tpi].staticOut[2 * i + 1])) {
                        status_nat_vs_ref = vlib_KERNEL_FAIL;
                        if( LevelOfFeedback > 0 ) {
                            printf(" Mismatch in Index = %u \n", i);
                        }
                        break;
                    }
                }
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) ||
                    (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt and NatC results compared | input n_features= %d, desired output features= %d, actual output n_features= %d, %s",
                    testPatternString, prm[tpi].true_num_features, prm[tpi].desired_num_features, orbOutput->n_features, prm[tpi].desc);

            VLIB_formula_add_test(prm[tpi].true_num_features, NULL, NULL, fail, desc, NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "input n_features= %d, desired output features= %d",
                    prm[tpi].true_num_features, prm[tpi].desired_num_features);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        VLIB_align_free(orbInput->scratchBuffer);
        free(orbOutput_cn->features);
        VLIB_free(orbOutput->features);
        free(orbOutput_cn);
        VLIB_free(orbOutput);
        free(orbInput);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_RANGE,
                              NULL,
                              "number of input features;\n  Min (best case) is when input is already sorted.\n  Max (worst case) is where input is sorted in reverse order.");

    /* Provide memory requirements */
    VLIB_kernel_memory();

}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_ORB_bestFeaturesToFront");
    } else {
        VLIB_ORB_bestFeaturesToFront_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_ORB_bestFeaturesToFront_d.c                          */
/* ======================================================================== */

