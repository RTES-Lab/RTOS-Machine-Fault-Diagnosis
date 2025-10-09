/**
  ******************************************************************************
  * @file    frfconv_data_params.h
  * @author  AST Embedded Analytics Research Platform
  * @date    2025-10-09T14:29:35+0900
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */

#ifndef FRFCONV_DATA_PARAMS_H
#define FRFCONV_DATA_PARAMS_H

#include "ai_platform.h"

/*
#define AI_FRFCONV_DATA_WEIGHTS_PARAMS \
  (AI_HANDLE_PTR(&ai_frfconv_data_weights_params[1]))
*/

#define AI_FRFCONV_DATA_CONFIG               (NULL)


#define AI_FRFCONV_DATA_ACTIVATIONS_SIZES \
  { 32776, }
#define AI_FRFCONV_DATA_ACTIVATIONS_SIZE     (32776)
#define AI_FRFCONV_DATA_ACTIVATIONS_COUNT    (1)
#define AI_FRFCONV_DATA_ACTIVATION_1_SIZE    (32776)



#define AI_FRFCONV_DATA_WEIGHTS_SIZES \
  { 35056, }
#define AI_FRFCONV_DATA_WEIGHTS_SIZE         (35056)
#define AI_FRFCONV_DATA_WEIGHTS_COUNT        (1)
#define AI_FRFCONV_DATA_WEIGHT_1_SIZE        (35056)



#define AI_FRFCONV_DATA_ACTIVATIONS_TABLE_GET() \
  (&g_frfconv_activations_table[1])

extern ai_handle g_frfconv_activations_table[1 + 2];



#define AI_FRFCONV_DATA_WEIGHTS_TABLE_GET() \
  (&g_frfconv_weights_table[1])

extern ai_handle g_frfconv_weights_table[1 + 2];


#endif    /* FRFCONV_DATA_PARAMS_H */
