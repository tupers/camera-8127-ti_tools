/* ======================================================================= */
/* DSPF_sp_fircirc_d.c -- Circular FIR Filter                              */
/*                Driver code; tests kernel and reports result in stdout   */
/*                                                                         */
/* Rev 0.0.1                                                               */
/*                                                                         */
/* Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/  */ 
/*                                                                         */
/*                                                                         */
/*  Redistribution and use in source and binary forms, with or without     */
/*  modification, are permitted provided that the following conditions     */
/*  are met:                                                               */
/*                                                                         */
/*    Redistributions of source code must retain the above copyright       */
/*    notice, this list of conditions and the following disclaimer.        */
/*                                                                         */
/*    Redistributions in binary form must reproduce the above copyright    */
/*    notice, this list of conditions and the following disclaimer in the  */
/*    documentation and/or other materials provided with the               */
/*    distribution.                                                        */
/*                                                                         */
/*    Neither the name of Texas Instruments Incorporated nor the names of  */
/*    its contributors may be used to endorse or promote products derived  */
/*    from this software without specific prior written permission.        */
/*                                                                         */
/*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS    */
/*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT      */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR  */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT   */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,  */
/*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT       */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,  */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY  */
/*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT    */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE  */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.   */
/*                                                                         */
/* ======================================================================= */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <c6x.h>

/* ======================================================================= */
/* Interface header files for the natural C and optimized C code           */
/* ======================================================================= */
#include "DSPF_sp_fircirc_cn.h"
#include "DSPF_sp_fircirc.h"

/* Defines */
#if defined(__TI_EABI__)
#define kernel_size _kernel_size
#endif

extern char kernel_size;
#define FLT_THRES             1E-20
#define FORMULA_SIZE          4
#define FORMULA_DEVIDE        3
#define CYCLE_FORMULA_NY_PT1  32
#define CYCLE_FORMULA_NY_PT2  20 
#define CYCLE_FORMULA_NH_PT1  16
#define CYCLE_FORMULA_NH_PT2  12

/* inverse of [32*16 32 16 1] */
/*            [32*12 32 12 1] */
/*            [20*16 20 16 1] */
/*            [20*12 20 12 1] */

float form_inv[FORMULA_SIZE][FORMULA_SIZE] = 
{{ 0.0208,   -0.0208,   -0.0208,    0.0208},
 {-0.2500,    0.3333,    0.2500,   -0.3333},
 {-0.4167,    0.4167,    0.6667,   -0.6667},
 { 5.0000,   -6.6667,   -8.0000,   10.6667}
};

float form_temp  [FORMULA_SIZE];
int   form_cycle [FORMULA_SIZE];
int   form_result[FORMULA_SIZE];
/* ======================================================================= */
/* Tell compiler arrays are double word alligned                           */
/* ======================================================================= */
#pragma DATA_ALIGN(ptr_y_i, 8);
#pragma DATA_ALIGN(ptr_y_cn, 8);
#pragma DATA_ALIGN(ptr_h, 8);
#pragma DATA_ALIGN(ptr_x, 16);    // generally: align to 1 << (NC + 1)

/* ======================================================================= */
/* Parameters of fixed dataset                                             */
/* ======================================================================= */
#define NY (32)
#define NH (16)
#define NC (3)

float ptr_y_i[NY];
float ptr_y_cn[NY];
float ptr_x[1 << (NC + 1)];
float ptr_h[NH];

/* ======================================================================= */
/* Prototypes for timing functions                                         */
/* ======================================================================= */
clock_t time_i(int nh, int ny);
clock_t time_cn(int nh, int ny);

/* ======================================================================= */
/* Prototypes for utility functions                                        */
/* ======================================================================= */
void UTIL_fillRandSP(float *ptr_x, int N, float factor);
void UTIL_fillRandFilterSP(float *ptr_h, int N);

/* ======================================================================= */
/* Main -- Top level driver for testing the algorithm                      */
/* ======================================================================= */
void main()
{
    clock_t t_overhead, t_start, t_stop, t_opt, t_cn;
    int i, j, k = 1, ny, nh;
    int form_error = 0;
    float pct_diff = 0, max_pct_diff = 0;
  
    /* ------------------------------------------------------------------- */
    /* Compute the overhead of calling clock twice to get timing info      */
    /* ------------------------------------------------------------------- */
    /* Initialize timer for clock */
    TSCL= 0,TSCH=0;
    t_start = _itoll(TSCH, TSCL);
    t_stop = _itoll(TSCH, TSCL);
    t_overhead = t_stop - t_start;
  
    /* ------------------------------------------------------------------- */
    /*  Generate random input (with zero padding) and MA filter.           */
    /* ------------------------------------------------------------------- */
    UTIL_fillRandSP(ptr_x, 1 << (NC + 1), 10.0);
    UTIL_fillRandFilterSP(ptr_h, NH);
  
    for(ny = 8; ny <= NY; ny += 4) {
      for(nh = 4; nh <= NH; nh += 4) {
        /* --------------------------------------------------------------- */
        /*  Clear state/output buffers with fixed values.                  */
        /* --------------------------------------------------------------- */
        memset(ptr_y_i,  0, sizeof(ptr_y_i));
        memset(ptr_y_cn, 0, sizeof(ptr_y_cn));
      
        /* --------------------------------------------------------------- */
        /* Call the individual timing routines                             */
        /* --------------------------------------------------------------- */
        t_opt  = time_i(nh, ny) - t_overhead;
        t_cn = time_cn(nh, ny)  - t_overhead;
      
        printf("DSPF_sp_fircirc\tIter#: %d\t", k++);
      
        /* --------------------------------------------------------------- */
        /* compute percent difference and track max difference             */
        /* --------------------------------------------------------------- */
        for(i=0; i< ny; i++)  {
          pct_diff = 0;
          if (abs((ptr_y_i[i]) > FLT_THRES) || (abs(ptr_y_cn[i]) > FLT_THRES))
            pct_diff = (ptr_y_cn[i] - ptr_y_i[i]) / ptr_y_cn[i] * 100.0;
          if (pct_diff < 0) pct_diff *= -1;
          if (pct_diff > max_pct_diff) max_pct_diff = pct_diff;
        }
        if (max_pct_diff > 0.05)
          printf("Result Failure, max_pct_diff = %f", max_pct_diff);
        else
          printf("Result Successful");

        /* --------------------------------------------------------------- */
        /* Print timing results                                            */
        /* --------------------------------------------------------------- */
        printf("\tNX = %d\tNH = %d\tnatC: %d\toptC: %d\n", ny, nh, t_cn, t_opt);
      
        if (ny == CYCLE_FORMULA_NY_PT1 && nh == CYCLE_FORMULA_NH_PT1)
          form_cycle[0] = t_opt;
        if (ny == CYCLE_FORMULA_NY_PT1 && nh == CYCLE_FORMULA_NH_PT2)
          form_cycle[1] = t_opt;
        if (ny == CYCLE_FORMULA_NY_PT2 && nh == CYCLE_FORMULA_NH_PT1)
          form_cycle[2] = t_opt;
        if (ny == CYCLE_FORMULA_NY_PT2 && nh == CYCLE_FORMULA_NH_PT2)
          form_cycle[3] = t_opt;    
      }
    }
    /* Provide memory information */
#ifdef __TI_COMPILER_VERSION__            // for TI compiler only
    printf("Memory:  %d bytes\n", &kernel_size);
#endif
  
    /* Provide profiling information */
    for (i = 0; i < FORMULA_SIZE; i++) {
        form_temp[i] = 0;
        for (j = 0; j < FORMULA_SIZE; j++) {
            form_temp[i] += form_inv[i][j] * form_cycle[j];
        }
        if (i != (FORMULA_SIZE-1)) {
            form_result[i] = (int) (form_temp[i] * FORMULA_DEVIDE + 0.5);
            if ((form_result[i] - form_temp[i] * FORMULA_DEVIDE) >  0.1 ||
                (form_result[i] - form_temp[i] * FORMULA_DEVIDE) < -0.1) {
                form_error = 1;
            }
        }
        else {
            form_result[i] = (int) (form_temp[i] + 0.5);
        }
    }
  
    if (!form_error) {
      printf("Cycles:  ");
      if (form_result[0])
        printf("%d/%d*Ny*Nh + ", form_result[0], FORMULA_DEVIDE);
      if (form_result[1])
        printf("%d/%d*Ny + ", form_result[1], FORMULA_DEVIDE);
      if (form_result[2])
        printf("%d/%d*Nh + ", form_result[2], FORMULA_DEVIDE);
      if (form_result[3])
        printf("%d\n", form_result[3]);
    }
    else
      printf("Cycles Formula Not Available\n");    
  
}

/* ======================================================================= */
/* Prototypes for timing functions                                         */
/* ======================================================================= */
clock_t time_cn(int nh, int ny)
{
    clock_t t_start, t_stop;
  
    /* ------------------------------------------------------------------- */
    /* Measure the cycle count                                             */
    /* ------------------------------------------------------------------- */
    t_start = _itoll(TSCH, TSCL);
    DSPF_sp_fircirc_cn(ptr_x, ptr_h, ptr_y_cn, 0, NC, nh, ny);
    t_stop = _itoll(TSCH, TSCL);
  
    return t_stop - t_start;
}

clock_t time_i(int nh, int ny)
{
    clock_t t_start, t_stop;
    
    /* ------------------------------------------------------------------- */
    /* Measure the cycle count                                             */
    /* ------------------------------------------------------------------- */
    t_start = _itoll(TSCH, TSCL);
    DSPF_sp_fircirc(ptr_x, ptr_h, ptr_y_i, 0, NC, nh, ny);
    t_stop = _itoll(TSCH, TSCL);
  
    return t_stop - t_start;
}

void UTIL_fillRandSP(float *ptr_x, int N, float factor)
{
    float rand_midpoint = RAND_MAX / 2.0;
    int i;

    // fill array with floats in the range (-factor, factor)
    for (i = 0; i < N; i++)
        ptr_x[i] = ((rand() - rand_midpoint) / rand_midpoint) * factor;
}

void UTIL_fillRandFilterSP(float *ptr_h, int N)
{
    float frand_max = RAND_MAX, pair_sum = 2.0 / N;
    int i;

    // create a moving average filter of length N
    // filter taps must be non-negative and sum to 1
    // N must be an even number
    for (i = 0; i < N / 2; i++)
    {
        ptr_h[i] = (rand() / frand_max) * pair_sum;
        ptr_h[N - 1 - i] = pair_sum - ptr_h[i];
    }
}
/* ======================================================================= */
/*  End of file:  DSPF_sp_fircirc_d.c                                      */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2011 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

