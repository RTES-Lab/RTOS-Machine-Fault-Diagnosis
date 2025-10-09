/**
  ******************************************************************************
  * @file    frfconv.c
  * @author  AST Embedded Analytics Research Platform
  * @date    2025-10-09T14:29:35+0900
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */


#include "frfconv.h"
#include "frfconv_data.h"

#include "ai_platform.h"
#include "ai_platform_interface.h"
#include "ai_math_helpers.h"

#include "core_common.h"
#include "core_convert.h"

#include "layers.h"



#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_frfconv
 
#undef AI_FRFCONV_MODEL_SIGNATURE
#define AI_FRFCONV_MODEL_SIGNATURE     "0x26475cc1b24c812121e420354d70db54"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     ""
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "2025-10-09T14:29:35+0900"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME    __DATE__ " " __TIME__

#undef AI_FRFCONV_N_BATCHES
#define AI_FRFCONV_N_BATCHES         (1)

static ai_ptr g_frfconv_activations_map[1] = AI_C_ARRAY_INIT;
static ai_ptr g_frfconv_weights_map[1] = AI_C_ARRAY_INIT;



/**  Array declarations section  **********************************************/
/* Array#0 */
AI_ARRAY_OBJ_DECLARE(
  input_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 2048, AI_STATIC)

/* Array#1 */
AI_ARRAY_OBJ_DECLARE(
  _Mul_2_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2048, AI_STATIC)

/* Array#2 */
AI_ARRAY_OBJ_DECLARE(
  _ReduceMean_3_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1, AI_STATIC)

/* Array#3 */
AI_ARRAY_OBJ_DECLARE(
  _ReduceMean_3_output_0_Mul_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1, AI_STATIC)

/* Array#4 */
AI_ARRAY_OBJ_DECLARE(
  _Sqrt_1_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1, AI_STATIC)

/* Array#5 */
AI_ARRAY_OBJ_DECLARE(
  _ReduceMean_1_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1, AI_STATIC)

/* Array#6 */
AI_ARRAY_OBJ_DECLARE(
  _ReduceMean_1_output_0_Mul_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1, AI_STATIC)

/* Array#7 */
AI_ARRAY_OBJ_DECLARE(
  _Sub_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2048, AI_STATIC)

/* Array#8 */
AI_ARRAY_OBJ_DECLARE(
  _Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2048, AI_STATIC)

/* Array#9 */
AI_ARRAY_OBJ_DECLARE(
  _ReduceMean_2_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1, AI_STATIC)

/* Array#10 */
AI_ARRAY_OBJ_DECLARE(
  _ReduceMean_2_output_0_Mul_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1, AI_STATIC)

/* Array#11 */
AI_ARRAY_OBJ_DECLARE(
  _Div_1_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1, AI_STATIC)

/* Array#12 */
AI_ARRAY_OBJ_DECLARE(
  _Sqrt_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1, AI_STATIC)

/* Array#13 */
AI_ARRAY_OBJ_DECLARE(
  _Pow_2_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1, AI_STATIC)

/* Array#14 */
AI_ARRAY_OBJ_DECLARE(
  _Reciprocal_1_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1, AI_STATIC)

/* Array#15 */
AI_ARRAY_OBJ_DECLARE(
  _Pow_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1, AI_STATIC)

/* Array#16 */
AI_ARRAY_OBJ_DECLARE(
  _Reciprocal_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1, AI_STATIC)

/* Array#17 */
AI_ARRAY_OBJ_DECLARE(
  _ReduceMean_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1, AI_STATIC)

/* Array#18 */
AI_ARRAY_OBJ_DECLARE(
  _ReduceMean_output_0_Mul_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1, AI_STATIC)

/* Array#19 */
AI_ARRAY_OBJ_DECLARE(
  _Sub_2_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2048, AI_STATIC)

/* Array#20 */
AI_ARRAY_OBJ_DECLARE(
  _Pow_3_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2048, AI_STATIC)

/* Array#21 */
AI_ARRAY_OBJ_DECLARE(
  _ReduceMean_5_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1, AI_STATIC)

/* Array#22 */
AI_ARRAY_OBJ_DECLARE(
  _ReduceMean_5_output_0_Mul_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1, AI_STATIC)

/* Array#23 */
AI_ARRAY_OBJ_DECLARE(
  _Mul_4_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1, AI_STATIC)

/* Array#24 */
AI_ARRAY_OBJ_DECLARE(
  _Pow_1_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2048, AI_STATIC)

/* Array#25 */
AI_ARRAY_OBJ_DECLARE(
  _ReduceMean_4_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1, AI_STATIC)

/* Array#26 */
AI_ARRAY_OBJ_DECLARE(
  _ReduceMean_4_output_0_Mul_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1, AI_STATIC)

/* Array#27 */
AI_ARRAY_OBJ_DECLARE(
  _Mul_3_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1, AI_STATIC)

/* Array#28 */
AI_ARRAY_OBJ_DECLARE(
  _Abs_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2048, AI_STATIC)

/* Array#29 */
AI_ARRAY_OBJ_DECLARE(
  _ReduceMax_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1, AI_STATIC)

/* Array#30 */
AI_ARRAY_OBJ_DECLARE(
  _Div_2_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1, AI_STATIC)

/* Array#31 */
AI_ARRAY_OBJ_DECLARE(
  _Concat_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 7, AI_STATIC)

/* Array#32 */
AI_ARRAY_OBJ_DECLARE(
  _Slice_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 4, AI_STATIC)

/* Array#33 */
AI_ARRAY_OBJ_DECLARE(
  _Div_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2048, AI_STATIC)

/* Array#34 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv1_conv_conv_0_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2048, AI_STATIC)

/* Array#35 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv1_conv_conv_2_Relu_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2048, AI_STATIC)

/* Array#36 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv2_1_dwconv_dwconv_0_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2048, AI_STATIC)

/* Array#37 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv2_1_dwconv_dwconv_2_Relu_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2048, AI_STATIC)

/* Array#38 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv2_1_pwconv_pwconv_0_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2048, AI_STATIC)

/* Array#39 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv2_1_Add_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2048, AI_STATIC)

/* Array#40 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv2_1_act_Relu_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2048, AI_STATIC)

/* Array#41 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv2_2_dwconv_dwconv_0_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2048, AI_STATIC)

/* Array#42 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv2_2_dwconv_dwconv_2_Relu_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2048, AI_STATIC)

/* Array#43 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv2_2_pwconv_pwconv_0_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2048, AI_STATIC)

/* Array#44 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv2_2_Add_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2048, AI_STATIC)

/* Array#45 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv2_2_act_Relu_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2048, AI_STATIC)

/* Array#46 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv2_3_dwconv_dwconv_0_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2048, AI_STATIC)

/* Array#47 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv2_3_dwconv_dwconv_2_Relu_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2048, AI_STATIC)

/* Array#48 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv2_3_pwconv_pwconv_0_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2048, AI_STATIC)

/* Array#49 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv2_3_Add_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2048, AI_STATIC)

/* Array#50 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv2_3_act_Relu_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2048, AI_STATIC)

/* Array#51 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv2_conv_conv_0_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 256, AI_STATIC)

/* Array#52 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv2_conv_conv_2_Relu_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 256, AI_STATIC)

/* Array#53 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv2_conv_conv_3_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 256, AI_STATIC)

/* Array#54 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv2_conv_conv_5_Relu_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 256, AI_STATIC)

/* Array#55 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv3_0_dwconv_dwconv_0_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 256, AI_STATIC)

/* Array#56 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv3_0_dwconv_dwconv_2_Relu_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 256, AI_STATIC)

/* Array#57 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv3_0_pwconv_pwconv_0_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 256, AI_STATIC)

/* Array#58 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv3_0_Add_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 256, AI_STATIC)

/* Array#59 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv3_0_act_Relu_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 256, AI_STATIC)

/* Array#60 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv3_1_dwconv_dwconv_0_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 256, AI_STATIC)

/* Array#61 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv3_1_dwconv_dwconv_2_Relu_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 256, AI_STATIC)

/* Array#62 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv3_1_pwconv_pwconv_0_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 256, AI_STATIC)

/* Array#63 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv3_1_Add_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 256, AI_STATIC)

/* Array#64 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv3_1_act_Relu_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 256, AI_STATIC)

/* Array#65 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv3_2_dwconv_dwconv_0_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 256, AI_STATIC)

/* Array#66 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv3_2_dwconv_dwconv_2_Relu_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 256, AI_STATIC)

/* Array#67 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv3_2_pwconv_pwconv_0_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 256, AI_STATIC)

/* Array#68 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv3_2_Add_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 256, AI_STATIC)

/* Array#69 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv3_2_act_Relu_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 256, AI_STATIC)

/* Array#70 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv4_conv4_0_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 256, AI_STATIC)

/* Array#71 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv4_conv4_2_Relu_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 256, AI_STATIC)

/* Array#72 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_gap_GlobalAveragePool_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 8, AI_STATIC)

/* Array#73 */
AI_ARRAY_OBJ_DECLARE(
  _Concat_1_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12, AI_STATIC)

/* Array#74 */
AI_ARRAY_OBJ_DECLARE(
  output_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 8, AI_STATIC)

/* Array#75 */
AI_ARRAY_OBJ_DECLARE(
  _Constant_2_output_0_3D_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1, AI_STATIC)

/* Array#76 */
AI_ARRAY_OBJ_DECLARE(
  _Constant_3_output_0_3D_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1, AI_STATIC)

/* Array#77 */
AI_ARRAY_OBJ_DECLARE(
  _Constant_4_output_0_3D_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1, AI_STATIC)

/* Array#78 */
AI_ARRAY_OBJ_DECLARE(
  _Constant_5_output_0_3D_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1, AI_STATIC)

/* Array#79 */
AI_ARRAY_OBJ_DECLARE(
  _Sub_1_output_0_const_3D_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1, AI_STATIC)

/* Array#80 */
AI_ARRAY_OBJ_DECLARE(
  _ReduceMean_3_output_0_Mul_scale_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1, AI_STATIC)

/* Array#81 */
AI_ARRAY_OBJ_DECLARE(
  _ReduceMean_3_output_0_Mul_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1, AI_STATIC)

/* Array#82 */
AI_ARRAY_OBJ_DECLARE(
  _ReduceMean_2_output_0_Mul_scale_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1, AI_STATIC)

/* Array#83 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv1_conv_conv_0_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 512, AI_STATIC)

/* Array#84 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv1_conv_conv_0_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 8, AI_STATIC)

/* Array#85 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv2_1_dwconv_dwconv_0_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2040, AI_STATIC)

/* Array#86 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv2_1_dwconv_dwconv_0_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 8, AI_STATIC)

/* Array#87 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv2_1_pwconv_pwconv_0_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#88 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv2_1_pwconv_pwconv_0_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 8, AI_STATIC)

/* Array#89 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv2_2_dwconv_dwconv_0_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2040, AI_STATIC)

/* Array#90 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv2_2_dwconv_dwconv_0_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 8, AI_STATIC)

/* Array#91 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv2_2_pwconv_pwconv_0_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#92 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv2_2_pwconv_pwconv_0_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 8, AI_STATIC)

/* Array#93 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv2_3_dwconv_dwconv_0_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2040, AI_STATIC)

/* Array#94 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv2_3_dwconv_dwconv_0_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 8, AI_STATIC)

/* Array#95 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv2_3_pwconv_pwconv_0_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#96 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv2_3_pwconv_pwconv_0_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 8, AI_STATIC)

/* Array#97 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv2_conv_conv_0_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 192, AI_STATIC)

/* Array#98 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv2_conv_conv_0_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 8, AI_STATIC)

/* Array#99 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv2_conv_conv_3_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#100 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv2_conv_conv_3_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 8, AI_STATIC)

/* Array#101 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv3_0_dwconv_dwconv_0_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 248, AI_STATIC)

/* Array#102 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv3_0_dwconv_dwconv_0_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 8, AI_STATIC)

/* Array#103 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv3_0_pwconv_pwconv_0_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#104 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv3_0_pwconv_pwconv_0_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 8, AI_STATIC)

/* Array#105 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv3_1_dwconv_dwconv_0_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 248, AI_STATIC)

/* Array#106 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv3_1_dwconv_dwconv_0_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 8, AI_STATIC)

/* Array#107 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv3_1_pwconv_pwconv_0_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#108 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv3_1_pwconv_pwconv_0_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 8, AI_STATIC)

/* Array#109 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv3_2_dwconv_dwconv_0_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 248, AI_STATIC)

/* Array#110 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv3_2_dwconv_dwconv_0_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 8, AI_STATIC)

/* Array#111 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv3_2_pwconv_pwconv_0_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#112 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv3_2_pwconv_pwconv_0_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 8, AI_STATIC)

/* Array#113 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv4_conv4_0_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 576, AI_STATIC)

/* Array#114 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv4_conv4_0_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 8, AI_STATIC)

/* Array#115 */
AI_ARRAY_OBJ_DECLARE(
  output_weights_array, AI_ARRAY_FORMAT_LUT4_FLOAT,
  NULL, NULL, 96, AI_STATIC)

/* Array#116 */
AI_ARRAY_OBJ_DECLARE(
  output_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 8, AI_STATIC)

/* Array#117 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv1_conv_conv_0_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#118 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv2_1_pwconv_pwconv_0_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 8, AI_STATIC)

/* Array#119 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv2_2_pwconv_pwconv_0_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 8, AI_STATIC)

/* Array#120 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv2_3_pwconv_pwconv_0_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 8, AI_STATIC)

/* Array#121 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv2_conv_conv_3_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 8, AI_STATIC)

/* Array#122 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv3_0_pwconv_pwconv_0_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 8, AI_STATIC)

/* Array#123 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv3_1_pwconv_pwconv_0_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 8, AI_STATIC)

/* Array#124 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv3_2_pwconv_pwconv_0_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 8, AI_STATIC)

/* Array#125 */
AI_ARRAY_OBJ_DECLARE(
  _convnet_conv4_conv4_0_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 72, AI_STATIC)

/**  Tensor declarations section  *********************************************/
/* Tensor #0 */
AI_TENSOR_OBJ_DECLARE(
  _Abs_output_0_output, AI_STATIC,
  0, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 2048), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_Abs_output_0_output_array, NULL)

/* Tensor #1 */
AI_TENSOR_OBJ_DECLARE(
  _Concat_1_output_0_output, AI_STATIC,
  1, 0x0,
  AI_SHAPE_INIT(4, 1, 12, 1, 1), AI_STRIDE_INIT(4, 4, 4, 48, 48),
  1, &_Concat_1_output_0_output_array, NULL)

/* Tensor #2 */
AI_TENSOR_OBJ_DECLARE(
  _Concat_output_0_output, AI_STATIC,
  2, 0x0,
  AI_SHAPE_INIT(4, 1, 7, 1, 1), AI_STRIDE_INIT(4, 4, 4, 28, 28),
  1, &_Concat_output_0_output_array, NULL)

/* Tensor #3 */
AI_TENSOR_OBJ_DECLARE(
  _Constant_2_output_0_3D, AI_STATIC,
  3, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_Constant_2_output_0_3D_array, NULL)

/* Tensor #4 */
AI_TENSOR_OBJ_DECLARE(
  _Constant_3_output_0_3D, AI_STATIC,
  4, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_Constant_3_output_0_3D_array, NULL)

/* Tensor #5 */
AI_TENSOR_OBJ_DECLARE(
  _Constant_4_output_0_3D, AI_STATIC,
  5, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_Constant_4_output_0_3D_array, NULL)

/* Tensor #6 */
AI_TENSOR_OBJ_DECLARE(
  _Constant_5_output_0_3D, AI_STATIC,
  6, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_Constant_5_output_0_3D_array, NULL)

/* Tensor #7 */
AI_TENSOR_OBJ_DECLARE(
  _Div_1_output_0_output, AI_STATIC,
  7, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_Div_1_output_0_output_array, NULL)

/* Tensor #8 */
AI_TENSOR_OBJ_DECLARE(
  _Div_2_output_0_output, AI_STATIC,
  8, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_Div_2_output_0_output_array, NULL)

/* Tensor #9 */
AI_TENSOR_OBJ_DECLARE(
  _Div_output_0_output, AI_STATIC,
  9, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 2048), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_Div_output_0_output_array, NULL)

/* Tensor #10 */
AI_TENSOR_OBJ_DECLARE(
  _Mul_2_output_0_output, AI_STATIC,
  10, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 2048), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_Mul_2_output_0_output_array, NULL)

/* Tensor #11 */
AI_TENSOR_OBJ_DECLARE(
  _Mul_3_output_0_output, AI_STATIC,
  11, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_Mul_3_output_0_output_array, NULL)

/* Tensor #12 */
AI_TENSOR_OBJ_DECLARE(
  _Mul_4_output_0_output, AI_STATIC,
  12, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_Mul_4_output_0_output_array, NULL)

/* Tensor #13 */
AI_TENSOR_OBJ_DECLARE(
  _Mul_output_0_output, AI_STATIC,
  13, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 2048), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_Mul_output_0_output_array, NULL)

/* Tensor #14 */
AI_TENSOR_OBJ_DECLARE(
  _Pow_1_output_0_output, AI_STATIC,
  14, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 2048), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_Pow_1_output_0_output_array, NULL)

/* Tensor #15 */
AI_TENSOR_OBJ_DECLARE(
  _Pow_2_output_0_output, AI_STATIC,
  15, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_Pow_2_output_0_output_array, NULL)

/* Tensor #16 */
AI_TENSOR_OBJ_DECLARE(
  _Pow_3_output_0_output, AI_STATIC,
  16, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 2048), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_Pow_3_output_0_output_array, NULL)

/* Tensor #17 */
AI_TENSOR_OBJ_DECLARE(
  _Pow_output_0_output, AI_STATIC,
  17, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_Pow_output_0_output_array, NULL)

/* Tensor #18 */
AI_TENSOR_OBJ_DECLARE(
  _Reciprocal_1_output_0_output, AI_STATIC,
  18, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_Reciprocal_1_output_0_output_array, NULL)

/* Tensor #19 */
AI_TENSOR_OBJ_DECLARE(
  _Reciprocal_output_0_output, AI_STATIC,
  19, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_Reciprocal_output_0_output_array, NULL)

/* Tensor #20 */
AI_TENSOR_OBJ_DECLARE(
  _ReduceMax_output_0_output, AI_STATIC,
  20, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_ReduceMax_output_0_output_array, NULL)

/* Tensor #21 */
AI_TENSOR_OBJ_DECLARE(
  _ReduceMean_1_output_0_Mul_output, AI_STATIC,
  21, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_ReduceMean_1_output_0_Mul_output_array, NULL)

/* Tensor #22 */
AI_TENSOR_OBJ_DECLARE(
  _ReduceMean_1_output_0_output, AI_STATIC,
  22, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_ReduceMean_1_output_0_output_array, NULL)

/* Tensor #23 */
AI_TENSOR_OBJ_DECLARE(
  _ReduceMean_2_output_0_Mul_output, AI_STATIC,
  23, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_ReduceMean_2_output_0_Mul_output_array, NULL)

/* Tensor #24 */
AI_TENSOR_OBJ_DECLARE(
  _ReduceMean_2_output_0_Mul_scale, AI_STATIC,
  24, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_ReduceMean_2_output_0_Mul_scale_array, NULL)

/* Tensor #25 */
AI_TENSOR_OBJ_DECLARE(
  _ReduceMean_2_output_0_output, AI_STATIC,
  25, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_ReduceMean_2_output_0_output_array, NULL)

/* Tensor #26 */
AI_TENSOR_OBJ_DECLARE(
  _ReduceMean_3_output_0_Mul_bias, AI_STATIC,
  26, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_ReduceMean_3_output_0_Mul_bias_array, NULL)

/* Tensor #27 */
AI_TENSOR_OBJ_DECLARE(
  _ReduceMean_3_output_0_Mul_output, AI_STATIC,
  27, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_ReduceMean_3_output_0_Mul_output_array, NULL)

/* Tensor #28 */
AI_TENSOR_OBJ_DECLARE(
  _ReduceMean_3_output_0_Mul_scale, AI_STATIC,
  28, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_ReduceMean_3_output_0_Mul_scale_array, NULL)

/* Tensor #29 */
AI_TENSOR_OBJ_DECLARE(
  _ReduceMean_3_output_0_output, AI_STATIC,
  29, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_ReduceMean_3_output_0_output_array, NULL)

/* Tensor #30 */
AI_TENSOR_OBJ_DECLARE(
  _ReduceMean_4_output_0_Mul_output, AI_STATIC,
  30, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_ReduceMean_4_output_0_Mul_output_array, NULL)

/* Tensor #31 */
AI_TENSOR_OBJ_DECLARE(
  _ReduceMean_4_output_0_output, AI_STATIC,
  31, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_ReduceMean_4_output_0_output_array, NULL)

/* Tensor #32 */
AI_TENSOR_OBJ_DECLARE(
  _ReduceMean_5_output_0_Mul_output, AI_STATIC,
  32, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_ReduceMean_5_output_0_Mul_output_array, NULL)

/* Tensor #33 */
AI_TENSOR_OBJ_DECLARE(
  _ReduceMean_5_output_0_output, AI_STATIC,
  33, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_ReduceMean_5_output_0_output_array, NULL)

/* Tensor #34 */
AI_TENSOR_OBJ_DECLARE(
  _ReduceMean_output_0_Mul_output, AI_STATIC,
  34, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_ReduceMean_output_0_Mul_output_array, NULL)

/* Tensor #35 */
AI_TENSOR_OBJ_DECLARE(
  _ReduceMean_output_0_output, AI_STATIC,
  35, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_ReduceMean_output_0_output_array, NULL)

/* Tensor #36 */
AI_TENSOR_OBJ_DECLARE(
  _Slice_output_0_output, AI_STATIC,
  36, 0x0,
  AI_SHAPE_INIT(4, 1, 4, 1, 1), AI_STRIDE_INIT(4, 4, 4, 16, 16),
  1, &_Slice_output_0_output_array, NULL)

/* Tensor #37 */
AI_TENSOR_OBJ_DECLARE(
  _Sqrt_1_output_0_output, AI_STATIC,
  37, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_Sqrt_1_output_0_output_array, NULL)

/* Tensor #38 */
AI_TENSOR_OBJ_DECLARE(
  _Sqrt_output_0_output, AI_STATIC,
  38, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_Sqrt_output_0_output_array, NULL)

/* Tensor #39 */
AI_TENSOR_OBJ_DECLARE(
  _Sub_1_output_0_const_3D, AI_STATIC,
  39, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_Sub_1_output_0_const_3D_array, NULL)

/* Tensor #40 */
AI_TENSOR_OBJ_DECLARE(
  _Sub_2_output_0_output, AI_STATIC,
  40, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 2048), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_Sub_2_output_0_output_array, NULL)

/* Tensor #41 */
AI_TENSOR_OBJ_DECLARE(
  _Sub_output_0_output, AI_STATIC,
  41, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 2048), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_Sub_output_0_output_array, NULL)

/* Tensor #42 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv1_conv_conv_0_Conv_output_0_bias, AI_STATIC,
  42, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv1_conv_conv_0_Conv_output_0_bias_array, NULL)

/* Tensor #43 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv1_conv_conv_0_Conv_output_0_output, AI_STATIC,
  43, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 256), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv1_conv_conv_0_Conv_output_0_output_array, NULL)

/* Tensor #44 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv1_conv_conv_0_Conv_output_0_scratch0, AI_STATIC,
  44, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 64), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_convnet_conv1_conv_conv_0_Conv_output_0_scratch0_array, NULL)

/* Tensor #45 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv1_conv_conv_0_Conv_output_0_weights, AI_STATIC,
  45, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 64, 8), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv1_conv_conv_0_Conv_output_0_weights_array, NULL)

/* Tensor #46 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv1_conv_conv_2_Relu_output_0_output, AI_STATIC,
  46, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 256), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv1_conv_conv_2_Relu_output_0_output_array, NULL)

/* Tensor #47 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv2_1_Add_output_0_output, AI_STATIC,
  47, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 256), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv2_1_Add_output_0_output_array, NULL)

/* Tensor #48 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv2_1_act_Relu_output_0_output, AI_STATIC,
  48, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 256), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv2_1_act_Relu_output_0_output_array, NULL)

/* Tensor #49 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv2_1_dwconv_dwconv_0_Conv_output_0_bias, AI_STATIC,
  49, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv2_1_dwconv_dwconv_0_Conv_output_0_bias_array, NULL)

/* Tensor #50 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv2_1_dwconv_dwconv_0_Conv_output_0_output, AI_STATIC,
  50, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 256), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv2_1_dwconv_dwconv_0_Conv_output_0_output_array, NULL)

/* Tensor #51 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv2_1_dwconv_dwconv_0_Conv_output_0_weights, AI_STATIC,
  51, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 255, 8), AI_STRIDE_INIT(4, 1, 8, 8, 8),
  1, &_convnet_conv2_1_dwconv_dwconv_0_Conv_output_0_weights_array, NULL)

/* Tensor #52 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv2_1_dwconv_dwconv_2_Relu_output_0_output, AI_STATIC,
  52, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 256), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv2_1_dwconv_dwconv_2_Relu_output_0_output_array, NULL)

/* Tensor #53 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv2_1_pwconv_pwconv_0_Conv_output_0_bias, AI_STATIC,
  53, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv2_1_pwconv_pwconv_0_Conv_output_0_bias_array, NULL)

/* Tensor #54 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv2_1_pwconv_pwconv_0_Conv_output_0_output, AI_STATIC,
  54, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 256), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv2_1_pwconv_pwconv_0_Conv_output_0_output_array, NULL)

/* Tensor #55 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv2_1_pwconv_pwconv_0_Conv_output_0_scratch0, AI_STATIC,
  55, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv2_1_pwconv_pwconv_0_Conv_output_0_scratch0_array, NULL)

/* Tensor #56 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv2_1_pwconv_pwconv_0_Conv_output_0_weights, AI_STATIC,
  56, 0x0,
  AI_SHAPE_INIT(4, 8, 1, 1, 8), AI_STRIDE_INIT(4, 4, 32, 256, 256),
  1, &_convnet_conv2_1_pwconv_pwconv_0_Conv_output_0_weights_array, NULL)

/* Tensor #57 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv2_2_Add_output_0_output, AI_STATIC,
  57, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 256), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv2_2_Add_output_0_output_array, NULL)

/* Tensor #58 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv2_2_act_Relu_output_0_output, AI_STATIC,
  58, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 256), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv2_2_act_Relu_output_0_output_array, NULL)

/* Tensor #59 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv2_2_dwconv_dwconv_0_Conv_output_0_bias, AI_STATIC,
  59, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv2_2_dwconv_dwconv_0_Conv_output_0_bias_array, NULL)

/* Tensor #60 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv2_2_dwconv_dwconv_0_Conv_output_0_output, AI_STATIC,
  60, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 256), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv2_2_dwconv_dwconv_0_Conv_output_0_output_array, NULL)

/* Tensor #61 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv2_2_dwconv_dwconv_0_Conv_output_0_weights, AI_STATIC,
  61, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 255, 8), AI_STRIDE_INIT(4, 1, 8, 8, 8),
  1, &_convnet_conv2_2_dwconv_dwconv_0_Conv_output_0_weights_array, NULL)

/* Tensor #62 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv2_2_dwconv_dwconv_2_Relu_output_0_output, AI_STATIC,
  62, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 256), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv2_2_dwconv_dwconv_2_Relu_output_0_output_array, NULL)

/* Tensor #63 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv2_2_pwconv_pwconv_0_Conv_output_0_bias, AI_STATIC,
  63, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv2_2_pwconv_pwconv_0_Conv_output_0_bias_array, NULL)

/* Tensor #64 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv2_2_pwconv_pwconv_0_Conv_output_0_output, AI_STATIC,
  64, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 256), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv2_2_pwconv_pwconv_0_Conv_output_0_output_array, NULL)

/* Tensor #65 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv2_2_pwconv_pwconv_0_Conv_output_0_scratch0, AI_STATIC,
  65, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv2_2_pwconv_pwconv_0_Conv_output_0_scratch0_array, NULL)

/* Tensor #66 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv2_2_pwconv_pwconv_0_Conv_output_0_weights, AI_STATIC,
  66, 0x0,
  AI_SHAPE_INIT(4, 8, 1, 1, 8), AI_STRIDE_INIT(4, 4, 32, 256, 256),
  1, &_convnet_conv2_2_pwconv_pwconv_0_Conv_output_0_weights_array, NULL)

/* Tensor #67 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv2_3_Add_output_0_output, AI_STATIC,
  67, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 256), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv2_3_Add_output_0_output_array, NULL)

/* Tensor #68 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv2_3_act_Relu_output_0_output, AI_STATIC,
  68, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 256), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv2_3_act_Relu_output_0_output_array, NULL)

/* Tensor #69 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv2_3_dwconv_dwconv_0_Conv_output_0_bias, AI_STATIC,
  69, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv2_3_dwconv_dwconv_0_Conv_output_0_bias_array, NULL)

/* Tensor #70 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv2_3_dwconv_dwconv_0_Conv_output_0_output, AI_STATIC,
  70, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 256), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv2_3_dwconv_dwconv_0_Conv_output_0_output_array, NULL)

/* Tensor #71 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv2_3_dwconv_dwconv_0_Conv_output_0_weights, AI_STATIC,
  71, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 255, 8), AI_STRIDE_INIT(4, 1, 8, 8, 8),
  1, &_convnet_conv2_3_dwconv_dwconv_0_Conv_output_0_weights_array, NULL)

/* Tensor #72 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv2_3_dwconv_dwconv_2_Relu_output_0_output, AI_STATIC,
  72, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 256), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv2_3_dwconv_dwconv_2_Relu_output_0_output_array, NULL)

/* Tensor #73 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv2_3_pwconv_pwconv_0_Conv_output_0_bias, AI_STATIC,
  73, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv2_3_pwconv_pwconv_0_Conv_output_0_bias_array, NULL)

/* Tensor #74 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv2_3_pwconv_pwconv_0_Conv_output_0_output, AI_STATIC,
  74, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 256), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv2_3_pwconv_pwconv_0_Conv_output_0_output_array, NULL)

/* Tensor #75 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv2_3_pwconv_pwconv_0_Conv_output_0_scratch0, AI_STATIC,
  75, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv2_3_pwconv_pwconv_0_Conv_output_0_scratch0_array, NULL)

/* Tensor #76 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv2_3_pwconv_pwconv_0_Conv_output_0_weights, AI_STATIC,
  76, 0x0,
  AI_SHAPE_INIT(4, 8, 1, 1, 8), AI_STRIDE_INIT(4, 4, 32, 256, 256),
  1, &_convnet_conv2_3_pwconv_pwconv_0_Conv_output_0_weights_array, NULL)

/* Tensor #77 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv2_conv_conv_0_Conv_output_0_bias, AI_STATIC,
  77, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv2_conv_conv_0_Conv_output_0_bias_array, NULL)

/* Tensor #78 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv2_conv_conv_0_Conv_output_0_output, AI_STATIC,
  78, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 32), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv2_conv_conv_0_Conv_output_0_output_array, NULL)

/* Tensor #79 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv2_conv_conv_0_Conv_output_0_weights, AI_STATIC,
  79, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 24, 8), AI_STRIDE_INIT(4, 1, 8, 8, 8),
  1, &_convnet_conv2_conv_conv_0_Conv_output_0_weights_array, NULL)

/* Tensor #80 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv2_conv_conv_2_Relu_output_0_output, AI_STATIC,
  80, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 32), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv2_conv_conv_2_Relu_output_0_output_array, NULL)

/* Tensor #81 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv2_conv_conv_3_Conv_output_0_bias, AI_STATIC,
  81, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv2_conv_conv_3_Conv_output_0_bias_array, NULL)

/* Tensor #82 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv2_conv_conv_3_Conv_output_0_output, AI_STATIC,
  82, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 32), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv2_conv_conv_3_Conv_output_0_output_array, NULL)

/* Tensor #83 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv2_conv_conv_3_Conv_output_0_scratch0, AI_STATIC,
  83, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv2_conv_conv_3_Conv_output_0_scratch0_array, NULL)

/* Tensor #84 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv2_conv_conv_3_Conv_output_0_weights, AI_STATIC,
  84, 0x0,
  AI_SHAPE_INIT(4, 8, 1, 1, 8), AI_STRIDE_INIT(4, 4, 32, 256, 256),
  1, &_convnet_conv2_conv_conv_3_Conv_output_0_weights_array, NULL)

/* Tensor #85 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv2_conv_conv_5_Relu_output_0_output, AI_STATIC,
  85, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 32), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv2_conv_conv_5_Relu_output_0_output_array, NULL)

/* Tensor #86 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv3_0_Add_output_0_output, AI_STATIC,
  86, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 32), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv3_0_Add_output_0_output_array, NULL)

/* Tensor #87 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv3_0_act_Relu_output_0_output, AI_STATIC,
  87, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 32), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv3_0_act_Relu_output_0_output_array, NULL)

/* Tensor #88 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv3_0_dwconv_dwconv_0_Conv_output_0_bias, AI_STATIC,
  88, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv3_0_dwconv_dwconv_0_Conv_output_0_bias_array, NULL)

/* Tensor #89 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv3_0_dwconv_dwconv_0_Conv_output_0_output, AI_STATIC,
  89, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 32), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv3_0_dwconv_dwconv_0_Conv_output_0_output_array, NULL)

/* Tensor #90 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv3_0_dwconv_dwconv_0_Conv_output_0_weights, AI_STATIC,
  90, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 31, 8), AI_STRIDE_INIT(4, 1, 8, 8, 8),
  1, &_convnet_conv3_0_dwconv_dwconv_0_Conv_output_0_weights_array, NULL)

/* Tensor #91 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv3_0_dwconv_dwconv_2_Relu_output_0_output, AI_STATIC,
  91, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 32), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv3_0_dwconv_dwconv_2_Relu_output_0_output_array, NULL)

/* Tensor #92 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv3_0_pwconv_pwconv_0_Conv_output_0_bias, AI_STATIC,
  92, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv3_0_pwconv_pwconv_0_Conv_output_0_bias_array, NULL)

/* Tensor #93 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv3_0_pwconv_pwconv_0_Conv_output_0_output, AI_STATIC,
  93, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 32), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv3_0_pwconv_pwconv_0_Conv_output_0_output_array, NULL)

/* Tensor #94 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv3_0_pwconv_pwconv_0_Conv_output_0_scratch0, AI_STATIC,
  94, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv3_0_pwconv_pwconv_0_Conv_output_0_scratch0_array, NULL)

/* Tensor #95 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv3_0_pwconv_pwconv_0_Conv_output_0_weights, AI_STATIC,
  95, 0x0,
  AI_SHAPE_INIT(4, 8, 1, 1, 8), AI_STRIDE_INIT(4, 4, 32, 256, 256),
  1, &_convnet_conv3_0_pwconv_pwconv_0_Conv_output_0_weights_array, NULL)

/* Tensor #96 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv3_1_Add_output_0_output, AI_STATIC,
  96, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 32), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv3_1_Add_output_0_output_array, NULL)

/* Tensor #97 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv3_1_act_Relu_output_0_output, AI_STATIC,
  97, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 32), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv3_1_act_Relu_output_0_output_array, NULL)

/* Tensor #98 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv3_1_dwconv_dwconv_0_Conv_output_0_bias, AI_STATIC,
  98, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv3_1_dwconv_dwconv_0_Conv_output_0_bias_array, NULL)

/* Tensor #99 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv3_1_dwconv_dwconv_0_Conv_output_0_output, AI_STATIC,
  99, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 32), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv3_1_dwconv_dwconv_0_Conv_output_0_output_array, NULL)

/* Tensor #100 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv3_1_dwconv_dwconv_0_Conv_output_0_weights, AI_STATIC,
  100, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 31, 8), AI_STRIDE_INIT(4, 1, 8, 8, 8),
  1, &_convnet_conv3_1_dwconv_dwconv_0_Conv_output_0_weights_array, NULL)

/* Tensor #101 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv3_1_dwconv_dwconv_2_Relu_output_0_output, AI_STATIC,
  101, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 32), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv3_1_dwconv_dwconv_2_Relu_output_0_output_array, NULL)

/* Tensor #102 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv3_1_pwconv_pwconv_0_Conv_output_0_bias, AI_STATIC,
  102, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv3_1_pwconv_pwconv_0_Conv_output_0_bias_array, NULL)

/* Tensor #103 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv3_1_pwconv_pwconv_0_Conv_output_0_output, AI_STATIC,
  103, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 32), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv3_1_pwconv_pwconv_0_Conv_output_0_output_array, NULL)

/* Tensor #104 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv3_1_pwconv_pwconv_0_Conv_output_0_scratch0, AI_STATIC,
  104, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv3_1_pwconv_pwconv_0_Conv_output_0_scratch0_array, NULL)

/* Tensor #105 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv3_1_pwconv_pwconv_0_Conv_output_0_weights, AI_STATIC,
  105, 0x0,
  AI_SHAPE_INIT(4, 8, 1, 1, 8), AI_STRIDE_INIT(4, 4, 32, 256, 256),
  1, &_convnet_conv3_1_pwconv_pwconv_0_Conv_output_0_weights_array, NULL)

/* Tensor #106 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv3_2_Add_output_0_output, AI_STATIC,
  106, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 32), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv3_2_Add_output_0_output_array, NULL)

/* Tensor #107 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv3_2_act_Relu_output_0_output, AI_STATIC,
  107, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 32), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv3_2_act_Relu_output_0_output_array, NULL)

/* Tensor #108 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv3_2_dwconv_dwconv_0_Conv_output_0_bias, AI_STATIC,
  108, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv3_2_dwconv_dwconv_0_Conv_output_0_bias_array, NULL)

/* Tensor #109 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv3_2_dwconv_dwconv_0_Conv_output_0_output, AI_STATIC,
  109, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 32), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv3_2_dwconv_dwconv_0_Conv_output_0_output_array, NULL)

/* Tensor #110 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv3_2_dwconv_dwconv_0_Conv_output_0_weights, AI_STATIC,
  110, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 31, 8), AI_STRIDE_INIT(4, 1, 8, 8, 8),
  1, &_convnet_conv3_2_dwconv_dwconv_0_Conv_output_0_weights_array, NULL)

/* Tensor #111 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv3_2_dwconv_dwconv_2_Relu_output_0_output, AI_STATIC,
  111, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 32), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv3_2_dwconv_dwconv_2_Relu_output_0_output_array, NULL)

/* Tensor #112 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv3_2_pwconv_pwconv_0_Conv_output_0_bias, AI_STATIC,
  112, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv3_2_pwconv_pwconv_0_Conv_output_0_bias_array, NULL)

/* Tensor #113 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv3_2_pwconv_pwconv_0_Conv_output_0_output, AI_STATIC,
  113, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 32), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv3_2_pwconv_pwconv_0_Conv_output_0_output_array, NULL)

/* Tensor #114 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv3_2_pwconv_pwconv_0_Conv_output_0_scratch0, AI_STATIC,
  114, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv3_2_pwconv_pwconv_0_Conv_output_0_scratch0_array, NULL)

/* Tensor #115 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv3_2_pwconv_pwconv_0_Conv_output_0_weights, AI_STATIC,
  115, 0x0,
  AI_SHAPE_INIT(4, 8, 1, 1, 8), AI_STRIDE_INIT(4, 4, 32, 256, 256),
  1, &_convnet_conv3_2_pwconv_pwconv_0_Conv_output_0_weights_array, NULL)

/* Tensor #116 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv4_conv4_0_Conv_output_0_bias, AI_STATIC,
  116, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv4_conv4_0_Conv_output_0_bias_array, NULL)

/* Tensor #117 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv4_conv4_0_Conv_output_0_output, AI_STATIC,
  117, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 32), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv4_conv4_0_Conv_output_0_output_array, NULL)

/* Tensor #118 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv4_conv4_0_Conv_output_0_scratch0, AI_STATIC,
  118, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 9), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv4_conv4_0_Conv_output_0_scratch0_array, NULL)

/* Tensor #119 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv4_conv4_0_Conv_output_0_weights, AI_STATIC,
  119, 0x0,
  AI_SHAPE_INIT(4, 8, 1, 9, 8), AI_STRIDE_INIT(4, 4, 32, 256, 256),
  1, &_convnet_conv4_conv4_0_Conv_output_0_weights_array, NULL)

/* Tensor #120 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_conv4_conv4_2_Relu_output_0_output, AI_STATIC,
  120, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 32), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_conv4_conv4_2_Relu_output_0_output_array, NULL)

/* Tensor #121 */
AI_TENSOR_OBJ_DECLARE(
  _convnet_gap_GlobalAveragePool_output_0_output, AI_STATIC,
  121, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_convnet_gap_GlobalAveragePool_output_0_output_array, NULL)

/* Tensor #122 */
AI_TENSOR_OBJ_DECLARE(
  input_output, AI_STATIC,
  122, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 2048), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &input_output_array, NULL)

/* Tensor #123 */
AI_TENSOR_OBJ_DECLARE(
  output_bias, AI_STATIC,
  123, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &output_bias_array, NULL)

/* Tensor #124 */
AI_TENSOR_OBJ_DECLARE(
  output_output, AI_STATIC,
  124, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &output_output_array, NULL)

/* Tensor #125 */
AI_TENSOR_OBJ_DECLARE(
  output_weights, AI_STATIC,
  125, 0x0,
  AI_SHAPE_INIT(4, 12, 8, 1, 1), AI_STRIDE_INIT(4, 1, 6, 48, 48),
  1, &output_weights_array, NULL)



/**  Layer declarations section  **********************************************/


AI_TENSOR_CHAIN_OBJ_DECLARE(
  output_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Concat_1_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &output_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &output_weights, &output_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  output_layer, 87,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense,
  &output_chain,
  NULL, &output_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _Concat_1_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_convnet_gap_GlobalAveragePool_output_0_output, &_Slice_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Concat_1_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _Concat_1_output_0_layer, 86,
  CONCAT_TYPE, 0x0, NULL,
  concat, forward_concat,
  &_Concat_1_output_0_chain,
  NULL, &output_layer, AI_STATIC, 
  .axis = AI_SHAPE_CHANNEL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _convnet_gap_GlobalAveragePool_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv4_conv4_2_Relu_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_gap_GlobalAveragePool_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _convnet_gap_GlobalAveragePool_output_0_layer, 84,
  POOL_TYPE, 0x0, NULL,
  pool, forward_ap,
  &_convnet_gap_GlobalAveragePool_output_0_chain,
  NULL, &_Concat_1_output_0_layer, AI_STATIC, 
  .pool_size = AI_SHAPE_2D_INIT(1, 32), 
  .pool_stride = AI_SHAPE_2D_INIT(1, 32), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _convnet_conv4_conv4_2_Relu_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv4_conv4_0_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv4_conv4_2_Relu_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _convnet_conv4_conv4_2_Relu_output_0_layer, 83,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &_convnet_conv4_conv4_2_Relu_output_0_chain,
  NULL, &_convnet_gap_GlobalAveragePool_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _convnet_conv4_conv4_0_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv3_2_act_Relu_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv4_conv4_0_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_convnet_conv4_conv4_0_Conv_output_0_weights, &_convnet_conv4_conv4_0_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_convnet_conv4_conv4_0_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _convnet_conv4_conv4_0_Conv_output_0_layer, 82,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_convnet_conv4_conv4_0_Conv_output_0_chain,
  NULL, &_convnet_conv4_conv4_2_Relu_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 4, 0, 4, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _convnet_conv3_2_act_Relu_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv3_2_Add_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv3_2_act_Relu_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _convnet_conv3_2_act_Relu_output_0_layer, 81,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &_convnet_conv3_2_act_Relu_output_0_chain,
  NULL, &_convnet_conv4_conv4_0_Conv_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _convnet_conv3_2_Add_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_convnet_conv3_1_act_Relu_output_0_output, &_convnet_conv3_2_pwconv_pwconv_0_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv3_2_Add_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _convnet_conv3_2_Add_output_0_layer, 80,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_convnet_conv3_2_Add_output_0_chain,
  NULL, &_convnet_conv3_2_act_Relu_output_0_layer, AI_STATIC, 
  .operation = ai_sum_f32, 
  .buffer_operation = ai_sum_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _convnet_conv3_2_pwconv_pwconv_0_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv3_2_dwconv_dwconv_2_Relu_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv3_2_pwconv_pwconv_0_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_convnet_conv3_2_pwconv_pwconv_0_Conv_output_0_weights, &_convnet_conv3_2_pwconv_pwconv_0_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_convnet_conv3_2_pwconv_pwconv_0_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _convnet_conv3_2_pwconv_pwconv_0_Conv_output_0_layer, 79,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_convnet_conv3_2_pwconv_pwconv_0_Conv_output_0_chain,
  NULL, &_convnet_conv3_2_Add_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _convnet_conv3_2_dwconv_dwconv_2_Relu_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv3_2_dwconv_dwconv_0_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv3_2_dwconv_dwconv_2_Relu_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _convnet_conv3_2_dwconv_dwconv_2_Relu_output_0_layer, 78,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &_convnet_conv3_2_dwconv_dwconv_2_Relu_output_0_chain,
  NULL, &_convnet_conv3_2_pwconv_pwconv_0_Conv_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _convnet_conv3_2_dwconv_dwconv_0_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv3_1_act_Relu_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv3_2_dwconv_dwconv_0_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_convnet_conv3_2_dwconv_dwconv_0_Conv_output_0_weights, &_convnet_conv3_2_dwconv_dwconv_0_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _convnet_conv3_2_dwconv_dwconv_0_Conv_output_0_layer, 77,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_dw_if32of32wf32,
  &_convnet_conv3_2_dwconv_dwconv_0_Conv_output_0_chain,
  NULL, &_convnet_conv3_2_dwconv_dwconv_2_Relu_output_0_layer, AI_STATIC, 
  .groups = 8, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 15, 0, 15, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _convnet_conv3_1_act_Relu_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv3_1_Add_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv3_1_act_Relu_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _convnet_conv3_1_act_Relu_output_0_layer, 76,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &_convnet_conv3_1_act_Relu_output_0_chain,
  NULL, &_convnet_conv3_2_dwconv_dwconv_0_Conv_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _convnet_conv3_1_Add_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_convnet_conv3_0_act_Relu_output_0_output, &_convnet_conv3_1_pwconv_pwconv_0_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv3_1_Add_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _convnet_conv3_1_Add_output_0_layer, 75,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_convnet_conv3_1_Add_output_0_chain,
  NULL, &_convnet_conv3_1_act_Relu_output_0_layer, AI_STATIC, 
  .operation = ai_sum_f32, 
  .buffer_operation = ai_sum_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _convnet_conv3_1_pwconv_pwconv_0_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv3_1_dwconv_dwconv_2_Relu_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv3_1_pwconv_pwconv_0_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_convnet_conv3_1_pwconv_pwconv_0_Conv_output_0_weights, &_convnet_conv3_1_pwconv_pwconv_0_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_convnet_conv3_1_pwconv_pwconv_0_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _convnet_conv3_1_pwconv_pwconv_0_Conv_output_0_layer, 74,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_convnet_conv3_1_pwconv_pwconv_0_Conv_output_0_chain,
  NULL, &_convnet_conv3_1_Add_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _convnet_conv3_1_dwconv_dwconv_2_Relu_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv3_1_dwconv_dwconv_0_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv3_1_dwconv_dwconv_2_Relu_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _convnet_conv3_1_dwconv_dwconv_2_Relu_output_0_layer, 73,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &_convnet_conv3_1_dwconv_dwconv_2_Relu_output_0_chain,
  NULL, &_convnet_conv3_1_pwconv_pwconv_0_Conv_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _convnet_conv3_1_dwconv_dwconv_0_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv3_0_act_Relu_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv3_1_dwconv_dwconv_0_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_convnet_conv3_1_dwconv_dwconv_0_Conv_output_0_weights, &_convnet_conv3_1_dwconv_dwconv_0_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _convnet_conv3_1_dwconv_dwconv_0_Conv_output_0_layer, 72,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_dw_if32of32wf32,
  &_convnet_conv3_1_dwconv_dwconv_0_Conv_output_0_chain,
  NULL, &_convnet_conv3_1_dwconv_dwconv_2_Relu_output_0_layer, AI_STATIC, 
  .groups = 8, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 15, 0, 15, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _convnet_conv3_0_act_Relu_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv3_0_Add_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv3_0_act_Relu_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _convnet_conv3_0_act_Relu_output_0_layer, 71,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &_convnet_conv3_0_act_Relu_output_0_chain,
  NULL, &_convnet_conv3_1_dwconv_dwconv_0_Conv_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _convnet_conv3_0_Add_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_convnet_conv2_conv_conv_5_Relu_output_0_output, &_convnet_conv3_0_pwconv_pwconv_0_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv3_0_Add_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _convnet_conv3_0_Add_output_0_layer, 70,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_convnet_conv3_0_Add_output_0_chain,
  NULL, &_convnet_conv3_0_act_Relu_output_0_layer, AI_STATIC, 
  .operation = ai_sum_f32, 
  .buffer_operation = ai_sum_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _convnet_conv3_0_pwconv_pwconv_0_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv3_0_dwconv_dwconv_2_Relu_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv3_0_pwconv_pwconv_0_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_convnet_conv3_0_pwconv_pwconv_0_Conv_output_0_weights, &_convnet_conv3_0_pwconv_pwconv_0_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_convnet_conv3_0_pwconv_pwconv_0_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _convnet_conv3_0_pwconv_pwconv_0_Conv_output_0_layer, 69,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_convnet_conv3_0_pwconv_pwconv_0_Conv_output_0_chain,
  NULL, &_convnet_conv3_0_Add_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _convnet_conv3_0_dwconv_dwconv_2_Relu_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv3_0_dwconv_dwconv_0_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv3_0_dwconv_dwconv_2_Relu_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _convnet_conv3_0_dwconv_dwconv_2_Relu_output_0_layer, 68,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &_convnet_conv3_0_dwconv_dwconv_2_Relu_output_0_chain,
  NULL, &_convnet_conv3_0_pwconv_pwconv_0_Conv_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _convnet_conv3_0_dwconv_dwconv_0_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv2_conv_conv_5_Relu_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv3_0_dwconv_dwconv_0_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_convnet_conv3_0_dwconv_dwconv_0_Conv_output_0_weights, &_convnet_conv3_0_dwconv_dwconv_0_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _convnet_conv3_0_dwconv_dwconv_0_Conv_output_0_layer, 67,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_dw_if32of32wf32,
  &_convnet_conv3_0_dwconv_dwconv_0_Conv_output_0_chain,
  NULL, &_convnet_conv3_0_dwconv_dwconv_2_Relu_output_0_layer, AI_STATIC, 
  .groups = 8, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 15, 0, 15, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _convnet_conv2_conv_conv_5_Relu_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv2_conv_conv_3_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv2_conv_conv_5_Relu_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _convnet_conv2_conv_conv_5_Relu_output_0_layer, 66,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &_convnet_conv2_conv_conv_5_Relu_output_0_chain,
  NULL, &_convnet_conv3_0_dwconv_dwconv_0_Conv_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _convnet_conv2_conv_conv_3_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv2_conv_conv_2_Relu_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv2_conv_conv_3_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_convnet_conv2_conv_conv_3_Conv_output_0_weights, &_convnet_conv2_conv_conv_3_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_convnet_conv2_conv_conv_3_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _convnet_conv2_conv_conv_3_Conv_output_0_layer, 65,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_convnet_conv2_conv_conv_3_Conv_output_0_chain,
  NULL, &_convnet_conv2_conv_conv_5_Relu_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _convnet_conv2_conv_conv_2_Relu_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv2_conv_conv_0_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv2_conv_conv_2_Relu_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _convnet_conv2_conv_conv_2_Relu_output_0_layer, 64,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &_convnet_conv2_conv_conv_2_Relu_output_0_chain,
  NULL, &_convnet_conv2_conv_conv_3_Conv_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _convnet_conv2_conv_conv_0_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv2_3_act_Relu_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv2_conv_conv_0_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_convnet_conv2_conv_conv_0_Conv_output_0_weights, &_convnet_conv2_conv_conv_0_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _convnet_conv2_conv_conv_0_Conv_output_0_layer, 63,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_dw_if32of32wf32,
  &_convnet_conv2_conv_conv_0_Conv_output_0_chain,
  NULL, &_convnet_conv2_conv_conv_2_Relu_output_0_layer, AI_STATIC, 
  .groups = 8, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 8), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 8, 0, 8, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _convnet_conv2_3_act_Relu_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv2_3_Add_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv2_3_act_Relu_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _convnet_conv2_3_act_Relu_output_0_layer, 62,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &_convnet_conv2_3_act_Relu_output_0_chain,
  NULL, &_convnet_conv2_conv_conv_0_Conv_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _convnet_conv2_3_Add_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_convnet_conv2_2_act_Relu_output_0_output, &_convnet_conv2_3_pwconv_pwconv_0_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv2_3_Add_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _convnet_conv2_3_Add_output_0_layer, 61,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_convnet_conv2_3_Add_output_0_chain,
  NULL, &_convnet_conv2_3_act_Relu_output_0_layer, AI_STATIC, 
  .operation = ai_sum_f32, 
  .buffer_operation = ai_sum_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _convnet_conv2_3_pwconv_pwconv_0_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv2_3_dwconv_dwconv_2_Relu_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv2_3_pwconv_pwconv_0_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_convnet_conv2_3_pwconv_pwconv_0_Conv_output_0_weights, &_convnet_conv2_3_pwconv_pwconv_0_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_convnet_conv2_3_pwconv_pwconv_0_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _convnet_conv2_3_pwconv_pwconv_0_Conv_output_0_layer, 60,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_convnet_conv2_3_pwconv_pwconv_0_Conv_output_0_chain,
  NULL, &_convnet_conv2_3_Add_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _convnet_conv2_3_dwconv_dwconv_2_Relu_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv2_3_dwconv_dwconv_0_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv2_3_dwconv_dwconv_2_Relu_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _convnet_conv2_3_dwconv_dwconv_2_Relu_output_0_layer, 59,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &_convnet_conv2_3_dwconv_dwconv_2_Relu_output_0_chain,
  NULL, &_convnet_conv2_3_pwconv_pwconv_0_Conv_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _convnet_conv2_3_dwconv_dwconv_0_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv2_2_act_Relu_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv2_3_dwconv_dwconv_0_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_convnet_conv2_3_dwconv_dwconv_0_Conv_output_0_weights, &_convnet_conv2_3_dwconv_dwconv_0_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _convnet_conv2_3_dwconv_dwconv_0_Conv_output_0_layer, 58,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_dw_if32of32wf32,
  &_convnet_conv2_3_dwconv_dwconv_0_Conv_output_0_chain,
  NULL, &_convnet_conv2_3_dwconv_dwconv_2_Relu_output_0_layer, AI_STATIC, 
  .groups = 8, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 127, 0, 127, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _convnet_conv2_2_act_Relu_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv2_2_Add_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv2_2_act_Relu_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _convnet_conv2_2_act_Relu_output_0_layer, 57,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &_convnet_conv2_2_act_Relu_output_0_chain,
  NULL, &_convnet_conv2_3_dwconv_dwconv_0_Conv_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _convnet_conv2_2_Add_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_convnet_conv2_1_act_Relu_output_0_output, &_convnet_conv2_2_pwconv_pwconv_0_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv2_2_Add_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _convnet_conv2_2_Add_output_0_layer, 56,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_convnet_conv2_2_Add_output_0_chain,
  NULL, &_convnet_conv2_2_act_Relu_output_0_layer, AI_STATIC, 
  .operation = ai_sum_f32, 
  .buffer_operation = ai_sum_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _convnet_conv2_2_pwconv_pwconv_0_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv2_2_dwconv_dwconv_2_Relu_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv2_2_pwconv_pwconv_0_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_convnet_conv2_2_pwconv_pwconv_0_Conv_output_0_weights, &_convnet_conv2_2_pwconv_pwconv_0_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_convnet_conv2_2_pwconv_pwconv_0_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _convnet_conv2_2_pwconv_pwconv_0_Conv_output_0_layer, 55,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_convnet_conv2_2_pwconv_pwconv_0_Conv_output_0_chain,
  NULL, &_convnet_conv2_2_Add_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _convnet_conv2_2_dwconv_dwconv_2_Relu_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv2_2_dwconv_dwconv_0_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv2_2_dwconv_dwconv_2_Relu_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _convnet_conv2_2_dwconv_dwconv_2_Relu_output_0_layer, 54,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &_convnet_conv2_2_dwconv_dwconv_2_Relu_output_0_chain,
  NULL, &_convnet_conv2_2_pwconv_pwconv_0_Conv_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _convnet_conv2_2_dwconv_dwconv_0_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv2_1_act_Relu_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv2_2_dwconv_dwconv_0_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_convnet_conv2_2_dwconv_dwconv_0_Conv_output_0_weights, &_convnet_conv2_2_dwconv_dwconv_0_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _convnet_conv2_2_dwconv_dwconv_0_Conv_output_0_layer, 53,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_dw_if32of32wf32,
  &_convnet_conv2_2_dwconv_dwconv_0_Conv_output_0_chain,
  NULL, &_convnet_conv2_2_dwconv_dwconv_2_Relu_output_0_layer, AI_STATIC, 
  .groups = 8, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 127, 0, 127, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _convnet_conv2_1_act_Relu_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv2_1_Add_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv2_1_act_Relu_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _convnet_conv2_1_act_Relu_output_0_layer, 52,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &_convnet_conv2_1_act_Relu_output_0_chain,
  NULL, &_convnet_conv2_2_dwconv_dwconv_0_Conv_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _convnet_conv2_1_Add_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_convnet_conv1_conv_conv_2_Relu_output_0_output, &_convnet_conv2_1_pwconv_pwconv_0_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv2_1_Add_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _convnet_conv2_1_Add_output_0_layer, 51,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_convnet_conv2_1_Add_output_0_chain,
  NULL, &_convnet_conv2_1_act_Relu_output_0_layer, AI_STATIC, 
  .operation = ai_sum_f32, 
  .buffer_operation = ai_sum_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _convnet_conv2_1_pwconv_pwconv_0_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv2_1_dwconv_dwconv_2_Relu_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv2_1_pwconv_pwconv_0_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_convnet_conv2_1_pwconv_pwconv_0_Conv_output_0_weights, &_convnet_conv2_1_pwconv_pwconv_0_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_convnet_conv2_1_pwconv_pwconv_0_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _convnet_conv2_1_pwconv_pwconv_0_Conv_output_0_layer, 50,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_convnet_conv2_1_pwconv_pwconv_0_Conv_output_0_chain,
  NULL, &_convnet_conv2_1_Add_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _convnet_conv2_1_dwconv_dwconv_2_Relu_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv2_1_dwconv_dwconv_0_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv2_1_dwconv_dwconv_2_Relu_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _convnet_conv2_1_dwconv_dwconv_2_Relu_output_0_layer, 49,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &_convnet_conv2_1_dwconv_dwconv_2_Relu_output_0_chain,
  NULL, &_convnet_conv2_1_pwconv_pwconv_0_Conv_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _convnet_conv2_1_dwconv_dwconv_0_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv1_conv_conv_2_Relu_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv2_1_dwconv_dwconv_0_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_convnet_conv2_1_dwconv_dwconv_0_Conv_output_0_weights, &_convnet_conv2_1_dwconv_dwconv_0_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _convnet_conv2_1_dwconv_dwconv_0_Conv_output_0_layer, 48,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_dw_if32of32wf32,
  &_convnet_conv2_1_dwconv_dwconv_0_Conv_output_0_chain,
  NULL, &_convnet_conv2_1_dwconv_dwconv_2_Relu_output_0_layer, AI_STATIC, 
  .groups = 8, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 127, 0, 127, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _convnet_conv1_conv_conv_2_Relu_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv1_conv_conv_0_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv1_conv_conv_2_Relu_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _convnet_conv1_conv_conv_2_Relu_output_0_layer, 47,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &_convnet_conv1_conv_conv_2_Relu_output_0_chain,
  NULL, &_convnet_conv2_1_dwconv_dwconv_0_Conv_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _convnet_conv1_conv_conv_0_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Div_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_convnet_conv1_conv_conv_0_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_convnet_conv1_conv_conv_0_Conv_output_0_weights, &_convnet_conv1_conv_conv_0_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_convnet_conv1_conv_conv_0_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _convnet_conv1_conv_conv_0_Conv_output_0_layer, 46,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_convnet_conv1_conv_conv_0_Conv_output_0_chain,
  NULL, &_convnet_conv1_conv_conv_2_Relu_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 8), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 28, 0, 28, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _Div_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &input_output, &_ReduceMax_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Div_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _Div_output_0_layer, 3,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_Div_output_0_chain,
  NULL, &_convnet_conv1_conv_conv_0_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_div_f32, 
  .buffer_operation = ai_div_buffer_f32, 
)


AI_STATIC_CONST ai_u8 _Slice_output_0_axes_data[] = { 2 };
AI_ARRAY_OBJ_DECLARE(
    _Slice_output_0_axes, AI_ARRAY_FORMAT_U8,
    _Slice_output_0_axes_data, _Slice_output_0_axes_data, 1, AI_STATIC_CONST)

AI_STATIC_CONST ai_i16 _Slice_output_0_starts_data[] = { 0 };
AI_ARRAY_OBJ_DECLARE(
    _Slice_output_0_starts, AI_ARRAY_FORMAT_S16,
    _Slice_output_0_starts_data, _Slice_output_0_starts_data, 1, AI_STATIC_CONST)

AI_STATIC_CONST ai_i16 _Slice_output_0_ends_data[] = { 4 };
AI_ARRAY_OBJ_DECLARE(
    _Slice_output_0_ends, AI_ARRAY_FORMAT_S16,
    _Slice_output_0_ends_data, _Slice_output_0_ends_data, 1, AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(
  _Slice_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Concat_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Slice_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _Slice_output_0_layer, 45,
  SLICE_TYPE, 0x0, NULL,
  slice, forward_slice,
  &_Slice_output_0_chain,
  NULL, &_Div_output_0_layer, AI_STATIC, 
  .axes = &_Slice_output_0_axes, 
  .starts = &_Slice_output_0_starts, 
  .ends = &_Slice_output_0_ends, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _Concat_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 7, &_ReduceMean_output_0_Mul_output, &_ReduceMax_output_0_output, &_Sqrt_1_output_0_output, &_Div_2_output_0_output, &_Mul_4_output_0_output, &_Mul_3_output_0_output, &_Sqrt_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Concat_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _Concat_output_0_layer, 38,
  CONCAT_TYPE, 0x0, NULL,
  concat, forward_concat,
  &_Concat_output_0_chain,
  NULL, &_Slice_output_0_layer, AI_STATIC, 
  .axis = AI_SHAPE_CHANNEL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _Div_2_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_ReduceMax_output_0_output, &_Sqrt_1_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Div_2_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _Div_2_output_0_layer, 22,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_Div_2_output_0_chain,
  NULL, &_Concat_output_0_layer, AI_STATIC, 
  .operation = ai_div_f32, 
  .buffer_operation = ai_div_buffer_f32, 
)


AI_STATIC_CONST ai_float _ReduceMax_output_0_neutral_value_data[] = { -AI_FLT_MAX };
AI_ARRAY_OBJ_DECLARE(
    _ReduceMax_output_0_neutral_value, AI_ARRAY_FORMAT_FLOAT,
    _ReduceMax_output_0_neutral_value_data, _ReduceMax_output_0_neutral_value_data, 1, AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(
  _ReduceMax_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Abs_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_ReduceMax_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _ReduceMax_output_0_layer, 2,
  REDUCE_TYPE, 0x0, NULL,
  reduce, forward_reduce,
  &_ReduceMax_output_0_chain,
  NULL, &_Div_2_output_0_layer, AI_STATIC, 
  .operation = ai_max, 
  .neutral_value = &_ReduceMax_output_0_neutral_value, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _Abs_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &input_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Abs_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _Abs_output_0_layer, 1,
  NL_TYPE, 0x0, NULL,
  nl, forward_abs,
  &_Abs_output_0_chain,
  NULL, &_ReduceMax_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _Mul_3_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_Reciprocal_output_0_output, &_ReduceMean_4_output_0_Mul_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Mul_3_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _Mul_3_output_0_layer, 30,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_Mul_3_output_0_chain,
  NULL, &_Abs_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _ReduceMean_4_output_0_Mul_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_ReduceMean_4_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_ReduceMean_4_output_0_Mul_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_ReduceMean_3_output_0_Mul_scale, &_ReduceMean_3_output_0_Mul_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _ReduceMean_4_output_0_Mul_layer, 29,
  BN_TYPE, 0x0, NULL,
  bn, forward_bn,
  &_ReduceMean_4_output_0_Mul_chain,
  NULL, &_Mul_3_output_0_layer, AI_STATIC, 
)


AI_STATIC_CONST ai_float _ReduceMean_4_output_0_neutral_value_data[] = { 0.0f };
AI_ARRAY_OBJ_DECLARE(
    _ReduceMean_4_output_0_neutral_value, AI_ARRAY_FORMAT_FLOAT,
    _ReduceMean_4_output_0_neutral_value_data, _ReduceMean_4_output_0_neutral_value_data, 1, AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(
  _ReduceMean_4_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Pow_1_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_ReduceMean_4_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _ReduceMean_4_output_0_layer, 29,
  REDUCE_TYPE, 0x0, NULL,
  reduce, forward_reduce,
  &_ReduceMean_4_output_0_chain,
  NULL, &_ReduceMean_4_output_0_Mul_layer, AI_STATIC, 
  .operation = ai_sum, 
  .neutral_value = &_ReduceMean_4_output_0_neutral_value, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _Pow_1_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_Sub_2_output_0_output, &_Constant_3_output_0_3D),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Pow_1_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _Pow_1_output_0_layer, 28,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_Pow_1_output_0_chain,
  NULL, &_ReduceMean_4_output_0_layer, AI_STATIC, 
  .operation = ai_pow, 
  .buffer_operation = ai_pow_buffer, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _Mul_4_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_Reciprocal_1_output_0_output, &_ReduceMean_5_output_0_Mul_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Mul_4_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _Mul_4_output_0_layer, 37,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_Mul_4_output_0_chain,
  NULL, &_Pow_1_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _ReduceMean_5_output_0_Mul_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_ReduceMean_5_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_ReduceMean_5_output_0_Mul_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_ReduceMean_3_output_0_Mul_scale, &_ReduceMean_3_output_0_Mul_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _ReduceMean_5_output_0_Mul_layer, 36,
  BN_TYPE, 0x0, NULL,
  bn, forward_bn,
  &_ReduceMean_5_output_0_Mul_chain,
  NULL, &_Mul_4_output_0_layer, AI_STATIC, 
)


AI_STATIC_CONST ai_float _ReduceMean_5_output_0_neutral_value_data[] = { 0.0f };
AI_ARRAY_OBJ_DECLARE(
    _ReduceMean_5_output_0_neutral_value, AI_ARRAY_FORMAT_FLOAT,
    _ReduceMean_5_output_0_neutral_value_data, _ReduceMean_5_output_0_neutral_value_data, 1, AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(
  _ReduceMean_5_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Pow_3_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_ReduceMean_5_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _ReduceMean_5_output_0_layer, 36,
  REDUCE_TYPE, 0x0, NULL,
  reduce, forward_reduce,
  &_ReduceMean_5_output_0_chain,
  NULL, &_ReduceMean_5_output_0_Mul_layer, AI_STATIC, 
  .operation = ai_sum, 
  .neutral_value = &_ReduceMean_5_output_0_neutral_value, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _Pow_3_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_Sub_2_output_0_output, &_Constant_5_output_0_3D),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Pow_3_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _Pow_3_output_0_layer, 35,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_Pow_3_output_0_chain,
  NULL, &_ReduceMean_5_output_0_layer, AI_STATIC, 
  .operation = ai_pow, 
  .buffer_operation = ai_pow_buffer, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _Sub_2_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &input_output, &_ReduceMean_output_0_Mul_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Sub_2_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _Sub_2_output_0_layer, 26,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_Sub_2_output_0_chain,
  NULL, &_Pow_3_output_0_layer, AI_STATIC, 
  .operation = ai_sub_f32, 
  .buffer_operation = ai_sub_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _ReduceMean_output_0_Mul_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_ReduceMean_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_ReduceMean_output_0_Mul_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_ReduceMean_3_output_0_Mul_scale, &_ReduceMean_3_output_0_Mul_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _ReduceMean_output_0_Mul_layer, 4,
  BN_TYPE, 0x0, NULL,
  bn, forward_bn,
  &_ReduceMean_output_0_Mul_chain,
  NULL, &_Sub_2_output_0_layer, AI_STATIC, 
)


AI_STATIC_CONST ai_float _ReduceMean_output_0_neutral_value_data[] = { 0.0f };
AI_ARRAY_OBJ_DECLARE(
    _ReduceMean_output_0_neutral_value, AI_ARRAY_FORMAT_FLOAT,
    _ReduceMean_output_0_neutral_value_data, _ReduceMean_output_0_neutral_value_data, 1, AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(
  _ReduceMean_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &input_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_ReduceMean_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _ReduceMean_output_0_layer, 4,
  REDUCE_TYPE, 0x0, NULL,
  reduce, forward_reduce,
  &_ReduceMean_output_0_chain,
  NULL, &_ReduceMean_output_0_Mul_layer, AI_STATIC, 
  .operation = ai_sum, 
  .neutral_value = &_ReduceMean_output_0_neutral_value, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _Reciprocal_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Pow_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Reciprocal_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _Reciprocal_output_0_layer, 25,
  NL_TYPE, 0x0, NULL,
  nl, forward_reciprocal,
  &_Reciprocal_output_0_chain,
  NULL, &_ReduceMean_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _Pow_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_Sqrt_output_0_output, &_Constant_2_output_0_3D),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Pow_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _Pow_output_0_layer, 24,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_Pow_output_0_chain,
  NULL, &_Reciprocal_output_0_layer, AI_STATIC, 
  .operation = ai_pow, 
  .buffer_operation = ai_pow_buffer, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _Reciprocal_1_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Pow_2_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Reciprocal_1_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _Reciprocal_1_output_0_layer, 33,
  NL_TYPE, 0x0, NULL,
  nl, forward_reciprocal,
  &_Reciprocal_1_output_0_chain,
  NULL, &_Pow_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _Pow_2_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_Sqrt_output_0_output, &_Constant_4_output_0_3D),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Pow_2_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _Pow_2_output_0_layer, 32,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_Pow_2_output_0_chain,
  NULL, &_Reciprocal_1_output_0_layer, AI_STATIC, 
  .operation = ai_pow, 
  .buffer_operation = ai_pow_buffer, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _Sqrt_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Div_1_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Sqrt_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _Sqrt_output_0_layer, 18,
  NL_TYPE, 0x0, NULL,
  nl, forward_sqrt,
  &_Sqrt_output_0_chain,
  NULL, &_Pow_2_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _Div_1_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_ReduceMean_2_output_0_Mul_output, &_Sub_1_output_0_const_3D),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Div_1_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _Div_1_output_0_layer, 17,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_Div_1_output_0_chain,
  NULL, &_Sqrt_output_0_layer, AI_STATIC, 
  .operation = ai_div_f32, 
  .buffer_operation = ai_div_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _ReduceMean_2_output_0_Mul_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_ReduceMean_2_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_ReduceMean_2_output_0_Mul_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_ReduceMean_2_output_0_Mul_scale, &_ReduceMean_3_output_0_Mul_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _ReduceMean_2_output_0_Mul_layer, 14,
  BN_TYPE, 0x0, NULL,
  bn, forward_bn,
  &_ReduceMean_2_output_0_Mul_chain,
  NULL, &_Div_1_output_0_layer, AI_STATIC, 
)


AI_STATIC_CONST ai_float _ReduceMean_2_output_0_neutral_value_data[] = { 0.0f };
AI_ARRAY_OBJ_DECLARE(
    _ReduceMean_2_output_0_neutral_value, AI_ARRAY_FORMAT_FLOAT,
    _ReduceMean_2_output_0_neutral_value_data, _ReduceMean_2_output_0_neutral_value_data, 1, AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(
  _ReduceMean_2_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_ReduceMean_2_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _ReduceMean_2_output_0_layer, 14,
  REDUCE_TYPE, 0x0, NULL,
  reduce, forward_reduce,
  &_ReduceMean_2_output_0_chain,
  NULL, &_ReduceMean_2_output_0_Mul_layer, AI_STATIC, 
  .operation = ai_sum, 
  .neutral_value = &_ReduceMean_2_output_0_neutral_value, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_Sub_output_0_output, &_Sub_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _Mul_output_0_layer, 11,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_Mul_output_0_chain,
  NULL, &_ReduceMean_2_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _Sub_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &input_output, &_ReduceMean_1_output_0_Mul_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Sub_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _Sub_output_0_layer, 10,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_Sub_output_0_chain,
  NULL, &_Mul_output_0_layer, AI_STATIC, 
  .operation = ai_sub_f32, 
  .buffer_operation = ai_sub_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _ReduceMean_1_output_0_Mul_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_ReduceMean_1_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_ReduceMean_1_output_0_Mul_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_ReduceMean_3_output_0_Mul_scale, &_ReduceMean_3_output_0_Mul_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _ReduceMean_1_output_0_Mul_layer, 5,
  BN_TYPE, 0x0, NULL,
  bn, forward_bn,
  &_ReduceMean_1_output_0_Mul_chain,
  NULL, &_Sub_output_0_layer, AI_STATIC, 
)


AI_STATIC_CONST ai_float _ReduceMean_1_output_0_neutral_value_data[] = { 0.0f };
AI_ARRAY_OBJ_DECLARE(
    _ReduceMean_1_output_0_neutral_value, AI_ARRAY_FORMAT_FLOAT,
    _ReduceMean_1_output_0_neutral_value_data, _ReduceMean_1_output_0_neutral_value_data, 1, AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(
  _ReduceMean_1_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &input_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_ReduceMean_1_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _ReduceMean_1_output_0_layer, 5,
  REDUCE_TYPE, 0x0, NULL,
  reduce, forward_reduce,
  &_ReduceMean_1_output_0_chain,
  NULL, &_ReduceMean_1_output_0_Mul_layer, AI_STATIC, 
  .operation = ai_sum, 
  .neutral_value = &_ReduceMean_1_output_0_neutral_value, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _Sqrt_1_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_ReduceMean_3_output_0_Mul_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Sqrt_1_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _Sqrt_1_output_0_layer, 21,
  NL_TYPE, 0x0, NULL,
  nl, forward_sqrt,
  &_Sqrt_1_output_0_chain,
  NULL, &_ReduceMean_1_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _ReduceMean_3_output_0_Mul_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_ReduceMean_3_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_ReduceMean_3_output_0_Mul_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_ReduceMean_3_output_0_Mul_scale, &_ReduceMean_3_output_0_Mul_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _ReduceMean_3_output_0_Mul_layer, 20,
  BN_TYPE, 0x0, NULL,
  bn, forward_bn,
  &_ReduceMean_3_output_0_Mul_chain,
  NULL, &_Sqrt_1_output_0_layer, AI_STATIC, 
)


AI_STATIC_CONST ai_float _ReduceMean_3_output_0_neutral_value_data[] = { 0.0f };
AI_ARRAY_OBJ_DECLARE(
    _ReduceMean_3_output_0_neutral_value, AI_ARRAY_FORMAT_FLOAT,
    _ReduceMean_3_output_0_neutral_value_data, _ReduceMean_3_output_0_neutral_value_data, 1, AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(
  _ReduceMean_3_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Mul_2_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_ReduceMean_3_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _ReduceMean_3_output_0_layer, 20,
  REDUCE_TYPE, 0x0, NULL,
  reduce, forward_reduce,
  &_ReduceMean_3_output_0_chain,
  NULL, &_ReduceMean_3_output_0_Mul_layer, AI_STATIC, 
  .operation = ai_sum, 
  .neutral_value = &_ReduceMean_3_output_0_neutral_value, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _Mul_2_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &input_output, &input_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Mul_2_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _Mul_2_output_0_layer, 19,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_Mul_2_output_0_chain,
  NULL, &_ReduceMean_3_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)


#if (AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 35056, 1, 1),
    35056, NULL, NULL),
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 32776, 1, 1),
    32776, NULL, NULL),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_FRFCONV_IN_NUM, &input_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_FRFCONV_OUT_NUM, &output_output),
  &_Mul_2_output_0_layer, 0x6b7e4b74, NULL)

#else

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 35056, 1, 1),
      35056, NULL, NULL)
  ),
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 32776, 1, 1),
      32776, NULL, NULL)
  ),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_FRFCONV_IN_NUM, &input_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_FRFCONV_OUT_NUM, &output_output),
  &_Mul_2_output_0_layer, 0x6b7e4b74, NULL)

#endif	/*(AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)*/



/******************************************************************************/
AI_DECLARE_STATIC
ai_bool frfconv_configure_activations(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_activations_map(g_frfconv_activations_map, 1, params)) {
    /* Updating activations (byte) offsets */
    
    input_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 8196);
    input_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 8196);
    _Mul_2_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 16388);
    _Mul_2_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 16388);
    _ReduceMean_3_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 8192);
    _ReduceMean_3_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 8192);
    _ReduceMean_3_output_0_Mul_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 8192);
    _ReduceMean_3_output_0_Mul_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 8192);
    _Sqrt_1_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 8192);
    _Sqrt_1_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 8192);
    _ReduceMean_1_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 24576);
    _ReduceMean_1_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 24576);
    _ReduceMean_1_output_0_Mul_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 8188);
    _ReduceMean_1_output_0_Mul_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 8188);
    _Sub_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 16388);
    _Sub_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 16388);
    _Mul_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 0);
    _Mul_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 0);
    _ReduceMean_2_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 16388);
    _ReduceMean_2_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 16388);
    _ReduceMean_2_output_0_Mul_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 0);
    _ReduceMean_2_output_0_Mul_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 0);
    _Div_1_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 4);
    _Div_1_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 4);
    _Sqrt_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 0);
    _Sqrt_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 0);
    _Pow_2_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 16388);
    _Pow_2_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 16388);
    _Reciprocal_1_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 16388);
    _Reciprocal_1_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 16388);
    _Pow_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 24576);
    _Pow_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 24576);
    _Reciprocal_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 4);
    _Reciprocal_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 4);
    _ReduceMean_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 16392);
    _ReduceMean_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 16392);
    _ReduceMean_output_0_Mul_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 8188);
    _ReduceMean_output_0_Mul_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 8188);
    _Sub_2_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 16392);
    _Sub_2_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 16392);
    _Pow_3_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 24584);
    _Pow_3_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 24584);
    _ReduceMean_5_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 8);
    _ReduceMean_5_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 8);
    _ReduceMean_5_output_0_Mul_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 12);
    _ReduceMean_5_output_0_Mul_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 12);
    _Mul_4_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 8);
    _Mul_4_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 8);
    _Pow_1_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 24584);
    _Pow_1_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 24584);
    _ReduceMean_4_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 12);
    _ReduceMean_4_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 12);
    _ReduceMean_4_output_0_Mul_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 16);
    _ReduceMean_4_output_0_Mul_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 16);
    _Mul_3_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 12);
    _Mul_3_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 12);
    _Abs_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 16388);
    _Abs_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 16388);
    _ReduceMax_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 4);
    _ReduceMax_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 4);
    _Div_2_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 16);
    _Div_2_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 16);
    _Concat_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 20);
    _Concat_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 20);
    _Slice_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 48);
    _Slice_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 48);
    _Div_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 16388);
    _Div_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 16388);
    _convnet_conv1_conv_conv_0_Conv_output_0_scratch0_array.data = AI_PTR(g_frfconv_activations_map[0] + 64);
    _convnet_conv1_conv_conv_0_Conv_output_0_scratch0_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 64);
    _convnet_conv1_conv_conv_0_Conv_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 320);
    _convnet_conv1_conv_conv_0_Conv_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 320);
    _convnet_conv1_conv_conv_2_Relu_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 8512);
    _convnet_conv1_conv_conv_2_Relu_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 8512);
    _convnet_conv2_1_dwconv_dwconv_0_Conv_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 64);
    _convnet_conv2_1_dwconv_dwconv_0_Conv_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 64);
    _convnet_conv2_1_dwconv_dwconv_2_Relu_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 16704);
    _convnet_conv2_1_dwconv_dwconv_2_Relu_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 16704);
    _convnet_conv2_1_pwconv_pwconv_0_Conv_output_0_scratch0_array.data = AI_PTR(g_frfconv_activations_map[0] + 0);
    _convnet_conv2_1_pwconv_pwconv_0_Conv_output_0_scratch0_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 0);
    _convnet_conv2_1_pwconv_pwconv_0_Conv_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 64);
    _convnet_conv2_1_pwconv_pwconv_0_Conv_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 64);
    _convnet_conv2_1_Add_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 16704);
    _convnet_conv2_1_Add_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 16704);
    _convnet_conv2_1_act_Relu_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 64);
    _convnet_conv2_1_act_Relu_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 64);
    _convnet_conv2_2_dwconv_dwconv_0_Conv_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 8256);
    _convnet_conv2_2_dwconv_dwconv_0_Conv_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 8256);
    _convnet_conv2_2_dwconv_dwconv_2_Relu_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 16448);
    _convnet_conv2_2_dwconv_dwconv_2_Relu_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 16448);
    _convnet_conv2_2_pwconv_pwconv_0_Conv_output_0_scratch0_array.data = AI_PTR(g_frfconv_activations_map[0] + 0);
    _convnet_conv2_2_pwconv_pwconv_0_Conv_output_0_scratch0_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 0);
    _convnet_conv2_2_pwconv_pwconv_0_Conv_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 8256);
    _convnet_conv2_2_pwconv_pwconv_0_Conv_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 8256);
    _convnet_conv2_2_Add_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 16448);
    _convnet_conv2_2_Add_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 16448);
    _convnet_conv2_2_act_Relu_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 64);
    _convnet_conv2_2_act_Relu_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 64);
    _convnet_conv2_3_dwconv_dwconv_0_Conv_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 8256);
    _convnet_conv2_3_dwconv_dwconv_0_Conv_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 8256);
    _convnet_conv2_3_dwconv_dwconv_2_Relu_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 16448);
    _convnet_conv2_3_dwconv_dwconv_2_Relu_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 16448);
    _convnet_conv2_3_pwconv_pwconv_0_Conv_output_0_scratch0_array.data = AI_PTR(g_frfconv_activations_map[0] + 0);
    _convnet_conv2_3_pwconv_pwconv_0_Conv_output_0_scratch0_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 0);
    _convnet_conv2_3_pwconv_pwconv_0_Conv_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 8256);
    _convnet_conv2_3_pwconv_pwconv_0_Conv_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 8256);
    _convnet_conv2_3_Add_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 16448);
    _convnet_conv2_3_Add_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 16448);
    _convnet_conv2_3_act_Relu_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 64);
    _convnet_conv2_3_act_Relu_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 64);
    _convnet_conv2_conv_conv_0_Conv_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 8256);
    _convnet_conv2_conv_conv_0_Conv_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 8256);
    _convnet_conv2_conv_conv_2_Relu_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 64);
    _convnet_conv2_conv_conv_2_Relu_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 64);
    _convnet_conv2_conv_conv_3_Conv_output_0_scratch0_array.data = AI_PTR(g_frfconv_activations_map[0] + 0);
    _convnet_conv2_conv_conv_3_Conv_output_0_scratch0_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 0);
    _convnet_conv2_conv_conv_3_Conv_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 1088);
    _convnet_conv2_conv_conv_3_Conv_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 1088);
    _convnet_conv2_conv_conv_5_Relu_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 64);
    _convnet_conv2_conv_conv_5_Relu_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 64);
    _convnet_conv3_0_dwconv_dwconv_0_Conv_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 1088);
    _convnet_conv3_0_dwconv_dwconv_0_Conv_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 1088);
    _convnet_conv3_0_dwconv_dwconv_2_Relu_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 2112);
    _convnet_conv3_0_dwconv_dwconv_2_Relu_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 2112);
    _convnet_conv3_0_pwconv_pwconv_0_Conv_output_0_scratch0_array.data = AI_PTR(g_frfconv_activations_map[0] + 0);
    _convnet_conv3_0_pwconv_pwconv_0_Conv_output_0_scratch0_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 0);
    _convnet_conv3_0_pwconv_pwconv_0_Conv_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 1088);
    _convnet_conv3_0_pwconv_pwconv_0_Conv_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 1088);
    _convnet_conv3_0_Add_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 2112);
    _convnet_conv3_0_Add_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 2112);
    _convnet_conv3_0_act_Relu_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 64);
    _convnet_conv3_0_act_Relu_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 64);
    _convnet_conv3_1_dwconv_dwconv_0_Conv_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 1088);
    _convnet_conv3_1_dwconv_dwconv_0_Conv_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 1088);
    _convnet_conv3_1_dwconv_dwconv_2_Relu_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 2112);
    _convnet_conv3_1_dwconv_dwconv_2_Relu_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 2112);
    _convnet_conv3_1_pwconv_pwconv_0_Conv_output_0_scratch0_array.data = AI_PTR(g_frfconv_activations_map[0] + 0);
    _convnet_conv3_1_pwconv_pwconv_0_Conv_output_0_scratch0_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 0);
    _convnet_conv3_1_pwconv_pwconv_0_Conv_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 1088);
    _convnet_conv3_1_pwconv_pwconv_0_Conv_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 1088);
    _convnet_conv3_1_Add_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 2112);
    _convnet_conv3_1_Add_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 2112);
    _convnet_conv3_1_act_Relu_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 64);
    _convnet_conv3_1_act_Relu_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 64);
    _convnet_conv3_2_dwconv_dwconv_0_Conv_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 1088);
    _convnet_conv3_2_dwconv_dwconv_0_Conv_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 1088);
    _convnet_conv3_2_dwconv_dwconv_2_Relu_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 2112);
    _convnet_conv3_2_dwconv_dwconv_2_Relu_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 2112);
    _convnet_conv3_2_pwconv_pwconv_0_Conv_output_0_scratch0_array.data = AI_PTR(g_frfconv_activations_map[0] + 0);
    _convnet_conv3_2_pwconv_pwconv_0_Conv_output_0_scratch0_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 0);
    _convnet_conv3_2_pwconv_pwconv_0_Conv_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 1088);
    _convnet_conv3_2_pwconv_pwconv_0_Conv_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 1088);
    _convnet_conv3_2_Add_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 2112);
    _convnet_conv3_2_Add_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 2112);
    _convnet_conv3_2_act_Relu_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 64);
    _convnet_conv3_2_act_Relu_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 64);
    _convnet_conv4_conv4_0_Conv_output_0_scratch0_array.data = AI_PTR(g_frfconv_activations_map[0] + 1088);
    _convnet_conv4_conv4_0_Conv_output_0_scratch0_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 1088);
    _convnet_conv4_conv4_0_Conv_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 1376);
    _convnet_conv4_conv4_0_Conv_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 1376);
    _convnet_conv4_conv4_2_Relu_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 64);
    _convnet_conv4_conv4_2_Relu_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 64);
    _convnet_gap_GlobalAveragePool_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 0);
    _convnet_gap_GlobalAveragePool_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 0);
    _Concat_1_output_0_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 64);
    _Concat_1_output_0_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 64);
    output_output_array.data = AI_PTR(g_frfconv_activations_map[0] + 0);
    output_output_array.data_start = AI_PTR(g_frfconv_activations_map[0] + 0);
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_ACTIVATIONS);
  return false;
}




/******************************************************************************/
AI_DECLARE_STATIC
ai_bool frfconv_configure_weights(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_weights_map(g_frfconv_weights_map, 1, params)) {
    /* Updating weights (byte) offsets */
    
    _Constant_2_output_0_3D_array.format |= AI_FMT_FLAG_CONST;
    _Constant_2_output_0_3D_array.data = AI_PTR(g_frfconv_weights_map[0] + 0);
    _Constant_2_output_0_3D_array.data_start = AI_PTR(g_frfconv_weights_map[0] + 0);
    _Constant_3_output_0_3D_array.format |= AI_FMT_FLAG_CONST;
    _Constant_3_output_0_3D_array.data = AI_PTR(g_frfconv_weights_map[0] + 4);
    _Constant_3_output_0_3D_array.data_start = AI_PTR(g_frfconv_weights_map[0] + 4);
    _Constant_4_output_0_3D_array.format |= AI_FMT_FLAG_CONST;
    _Constant_4_output_0_3D_array.data = AI_PTR(g_frfconv_weights_map[0] + 8);
    _Constant_4_output_0_3D_array.data_start = AI_PTR(g_frfconv_weights_map[0] + 8);
    _Constant_5_output_0_3D_array.format |= AI_FMT_FLAG_CONST;
    _Constant_5_output_0_3D_array.data = AI_PTR(g_frfconv_weights_map[0] + 12);
    _Constant_5_output_0_3D_array.data_start = AI_PTR(g_frfconv_weights_map[0] + 12);
    _Sub_1_output_0_const_3D_array.format |= AI_FMT_FLAG_CONST;
    _Sub_1_output_0_const_3D_array.data = AI_PTR(g_frfconv_weights_map[0] + 16);
    _Sub_1_output_0_const_3D_array.data_start = AI_PTR(g_frfconv_weights_map[0] + 16);
    _ReduceMean_3_output_0_Mul_scale_array.format |= AI_FMT_FLAG_CONST;
    _ReduceMean_3_output_0_Mul_scale_array.data = AI_PTR(g_frfconv_weights_map[0] + 20);
    _ReduceMean_3_output_0_Mul_scale_array.data_start = AI_PTR(g_frfconv_weights_map[0] + 20);
    _ReduceMean_3_output_0_Mul_bias_array.format |= AI_FMT_FLAG_CONST;
    _ReduceMean_3_output_0_Mul_bias_array.data = AI_PTR(g_frfconv_weights_map[0] + 24);
    _ReduceMean_3_output_0_Mul_bias_array.data_start = AI_PTR(g_frfconv_weights_map[0] + 24);
    _ReduceMean_2_output_0_Mul_scale_array.format |= AI_FMT_FLAG_CONST;
    _ReduceMean_2_output_0_Mul_scale_array.data = AI_PTR(g_frfconv_weights_map[0] + 28);
    _ReduceMean_2_output_0_Mul_scale_array.data_start = AI_PTR(g_frfconv_weights_map[0] + 28);
    _convnet_conv1_conv_conv_0_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _convnet_conv1_conv_conv_0_Conv_output_0_weights_array.data = AI_PTR(g_frfconv_weights_map[0] + 32);
    _convnet_conv1_conv_conv_0_Conv_output_0_weights_array.data_start = AI_PTR(g_frfconv_weights_map[0] + 32);
    _convnet_conv1_conv_conv_0_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _convnet_conv1_conv_conv_0_Conv_output_0_bias_array.data = AI_PTR(g_frfconv_weights_map[0] + 2080);
    _convnet_conv1_conv_conv_0_Conv_output_0_bias_array.data_start = AI_PTR(g_frfconv_weights_map[0] + 2080);
    _convnet_conv2_1_dwconv_dwconv_0_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _convnet_conv2_1_dwconv_dwconv_0_Conv_output_0_weights_array.data = AI_PTR(g_frfconv_weights_map[0] + 2112);
    _convnet_conv2_1_dwconv_dwconv_0_Conv_output_0_weights_array.data_start = AI_PTR(g_frfconv_weights_map[0] + 2112);
    _convnet_conv2_1_dwconv_dwconv_0_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _convnet_conv2_1_dwconv_dwconv_0_Conv_output_0_bias_array.data = AI_PTR(g_frfconv_weights_map[0] + 10272);
    _convnet_conv2_1_dwconv_dwconv_0_Conv_output_0_bias_array.data_start = AI_PTR(g_frfconv_weights_map[0] + 10272);
    _convnet_conv2_1_pwconv_pwconv_0_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _convnet_conv2_1_pwconv_pwconv_0_Conv_output_0_weights_array.data = AI_PTR(g_frfconv_weights_map[0] + 10304);
    _convnet_conv2_1_pwconv_pwconv_0_Conv_output_0_weights_array.data_start = AI_PTR(g_frfconv_weights_map[0] + 10304);
    _convnet_conv2_1_pwconv_pwconv_0_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _convnet_conv2_1_pwconv_pwconv_0_Conv_output_0_bias_array.data = AI_PTR(g_frfconv_weights_map[0] + 10560);
    _convnet_conv2_1_pwconv_pwconv_0_Conv_output_0_bias_array.data_start = AI_PTR(g_frfconv_weights_map[0] + 10560);
    _convnet_conv2_2_dwconv_dwconv_0_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _convnet_conv2_2_dwconv_dwconv_0_Conv_output_0_weights_array.data = AI_PTR(g_frfconv_weights_map[0] + 10592);
    _convnet_conv2_2_dwconv_dwconv_0_Conv_output_0_weights_array.data_start = AI_PTR(g_frfconv_weights_map[0] + 10592);
    _convnet_conv2_2_dwconv_dwconv_0_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _convnet_conv2_2_dwconv_dwconv_0_Conv_output_0_bias_array.data = AI_PTR(g_frfconv_weights_map[0] + 18752);
    _convnet_conv2_2_dwconv_dwconv_0_Conv_output_0_bias_array.data_start = AI_PTR(g_frfconv_weights_map[0] + 18752);
    _convnet_conv2_2_pwconv_pwconv_0_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _convnet_conv2_2_pwconv_pwconv_0_Conv_output_0_weights_array.data = AI_PTR(g_frfconv_weights_map[0] + 18784);
    _convnet_conv2_2_pwconv_pwconv_0_Conv_output_0_weights_array.data_start = AI_PTR(g_frfconv_weights_map[0] + 18784);
    _convnet_conv2_2_pwconv_pwconv_0_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _convnet_conv2_2_pwconv_pwconv_0_Conv_output_0_bias_array.data = AI_PTR(g_frfconv_weights_map[0] + 19040);
    _convnet_conv2_2_pwconv_pwconv_0_Conv_output_0_bias_array.data_start = AI_PTR(g_frfconv_weights_map[0] + 19040);
    _convnet_conv2_3_dwconv_dwconv_0_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _convnet_conv2_3_dwconv_dwconv_0_Conv_output_0_weights_array.data = AI_PTR(g_frfconv_weights_map[0] + 19072);
    _convnet_conv2_3_dwconv_dwconv_0_Conv_output_0_weights_array.data_start = AI_PTR(g_frfconv_weights_map[0] + 19072);
    _convnet_conv2_3_dwconv_dwconv_0_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _convnet_conv2_3_dwconv_dwconv_0_Conv_output_0_bias_array.data = AI_PTR(g_frfconv_weights_map[0] + 27232);
    _convnet_conv2_3_dwconv_dwconv_0_Conv_output_0_bias_array.data_start = AI_PTR(g_frfconv_weights_map[0] + 27232);
    _convnet_conv2_3_pwconv_pwconv_0_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _convnet_conv2_3_pwconv_pwconv_0_Conv_output_0_weights_array.data = AI_PTR(g_frfconv_weights_map[0] + 27264);
    _convnet_conv2_3_pwconv_pwconv_0_Conv_output_0_weights_array.data_start = AI_PTR(g_frfconv_weights_map[0] + 27264);
    _convnet_conv2_3_pwconv_pwconv_0_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _convnet_conv2_3_pwconv_pwconv_0_Conv_output_0_bias_array.data = AI_PTR(g_frfconv_weights_map[0] + 27520);
    _convnet_conv2_3_pwconv_pwconv_0_Conv_output_0_bias_array.data_start = AI_PTR(g_frfconv_weights_map[0] + 27520);
    _convnet_conv2_conv_conv_0_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _convnet_conv2_conv_conv_0_Conv_output_0_weights_array.data = AI_PTR(g_frfconv_weights_map[0] + 27552);
    _convnet_conv2_conv_conv_0_Conv_output_0_weights_array.data_start = AI_PTR(g_frfconv_weights_map[0] + 27552);
    _convnet_conv2_conv_conv_0_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _convnet_conv2_conv_conv_0_Conv_output_0_bias_array.data = AI_PTR(g_frfconv_weights_map[0] + 28320);
    _convnet_conv2_conv_conv_0_Conv_output_0_bias_array.data_start = AI_PTR(g_frfconv_weights_map[0] + 28320);
    _convnet_conv2_conv_conv_3_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _convnet_conv2_conv_conv_3_Conv_output_0_weights_array.data = AI_PTR(g_frfconv_weights_map[0] + 28352);
    _convnet_conv2_conv_conv_3_Conv_output_0_weights_array.data_start = AI_PTR(g_frfconv_weights_map[0] + 28352);
    _convnet_conv2_conv_conv_3_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _convnet_conv2_conv_conv_3_Conv_output_0_bias_array.data = AI_PTR(g_frfconv_weights_map[0] + 28608);
    _convnet_conv2_conv_conv_3_Conv_output_0_bias_array.data_start = AI_PTR(g_frfconv_weights_map[0] + 28608);
    _convnet_conv3_0_dwconv_dwconv_0_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _convnet_conv3_0_dwconv_dwconv_0_Conv_output_0_weights_array.data = AI_PTR(g_frfconv_weights_map[0] + 28640);
    _convnet_conv3_0_dwconv_dwconv_0_Conv_output_0_weights_array.data_start = AI_PTR(g_frfconv_weights_map[0] + 28640);
    _convnet_conv3_0_dwconv_dwconv_0_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _convnet_conv3_0_dwconv_dwconv_0_Conv_output_0_bias_array.data = AI_PTR(g_frfconv_weights_map[0] + 29632);
    _convnet_conv3_0_dwconv_dwconv_0_Conv_output_0_bias_array.data_start = AI_PTR(g_frfconv_weights_map[0] + 29632);
    _convnet_conv3_0_pwconv_pwconv_0_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _convnet_conv3_0_pwconv_pwconv_0_Conv_output_0_weights_array.data = AI_PTR(g_frfconv_weights_map[0] + 29664);
    _convnet_conv3_0_pwconv_pwconv_0_Conv_output_0_weights_array.data_start = AI_PTR(g_frfconv_weights_map[0] + 29664);
    _convnet_conv3_0_pwconv_pwconv_0_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _convnet_conv3_0_pwconv_pwconv_0_Conv_output_0_bias_array.data = AI_PTR(g_frfconv_weights_map[0] + 29920);
    _convnet_conv3_0_pwconv_pwconv_0_Conv_output_0_bias_array.data_start = AI_PTR(g_frfconv_weights_map[0] + 29920);
    _convnet_conv3_1_dwconv_dwconv_0_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _convnet_conv3_1_dwconv_dwconv_0_Conv_output_0_weights_array.data = AI_PTR(g_frfconv_weights_map[0] + 29952);
    _convnet_conv3_1_dwconv_dwconv_0_Conv_output_0_weights_array.data_start = AI_PTR(g_frfconv_weights_map[0] + 29952);
    _convnet_conv3_1_dwconv_dwconv_0_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _convnet_conv3_1_dwconv_dwconv_0_Conv_output_0_bias_array.data = AI_PTR(g_frfconv_weights_map[0] + 30944);
    _convnet_conv3_1_dwconv_dwconv_0_Conv_output_0_bias_array.data_start = AI_PTR(g_frfconv_weights_map[0] + 30944);
    _convnet_conv3_1_pwconv_pwconv_0_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _convnet_conv3_1_pwconv_pwconv_0_Conv_output_0_weights_array.data = AI_PTR(g_frfconv_weights_map[0] + 30976);
    _convnet_conv3_1_pwconv_pwconv_0_Conv_output_0_weights_array.data_start = AI_PTR(g_frfconv_weights_map[0] + 30976);
    _convnet_conv3_1_pwconv_pwconv_0_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _convnet_conv3_1_pwconv_pwconv_0_Conv_output_0_bias_array.data = AI_PTR(g_frfconv_weights_map[0] + 31232);
    _convnet_conv3_1_pwconv_pwconv_0_Conv_output_0_bias_array.data_start = AI_PTR(g_frfconv_weights_map[0] + 31232);
    _convnet_conv3_2_dwconv_dwconv_0_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _convnet_conv3_2_dwconv_dwconv_0_Conv_output_0_weights_array.data = AI_PTR(g_frfconv_weights_map[0] + 31264);
    _convnet_conv3_2_dwconv_dwconv_0_Conv_output_0_weights_array.data_start = AI_PTR(g_frfconv_weights_map[0] + 31264);
    _convnet_conv3_2_dwconv_dwconv_0_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _convnet_conv3_2_dwconv_dwconv_0_Conv_output_0_bias_array.data = AI_PTR(g_frfconv_weights_map[0] + 32256);
    _convnet_conv3_2_dwconv_dwconv_0_Conv_output_0_bias_array.data_start = AI_PTR(g_frfconv_weights_map[0] + 32256);
    _convnet_conv3_2_pwconv_pwconv_0_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _convnet_conv3_2_pwconv_pwconv_0_Conv_output_0_weights_array.data = AI_PTR(g_frfconv_weights_map[0] + 32288);
    _convnet_conv3_2_pwconv_pwconv_0_Conv_output_0_weights_array.data_start = AI_PTR(g_frfconv_weights_map[0] + 32288);
    _convnet_conv3_2_pwconv_pwconv_0_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _convnet_conv3_2_pwconv_pwconv_0_Conv_output_0_bias_array.data = AI_PTR(g_frfconv_weights_map[0] + 32544);
    _convnet_conv3_2_pwconv_pwconv_0_Conv_output_0_bias_array.data_start = AI_PTR(g_frfconv_weights_map[0] + 32544);
    _convnet_conv4_conv4_0_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _convnet_conv4_conv4_0_Conv_output_0_weights_array.data = AI_PTR(g_frfconv_weights_map[0] + 32576);
    _convnet_conv4_conv4_0_Conv_output_0_weights_array.data_start = AI_PTR(g_frfconv_weights_map[0] + 32576);
    _convnet_conv4_conv4_0_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _convnet_conv4_conv4_0_Conv_output_0_bias_array.data = AI_PTR(g_frfconv_weights_map[0] + 34880);
    _convnet_conv4_conv4_0_Conv_output_0_bias_array.data_start = AI_PTR(g_frfconv_weights_map[0] + 34880);
    output_weights_array.format |= AI_FMT_FLAG_CONST;
    output_weights_array.data = AI_PTR(g_frfconv_weights_map[0] + 34976);
    output_weights_array.data_start = AI_PTR(g_frfconv_weights_map[0] + 34912);
    output_bias_array.format |= AI_FMT_FLAG_CONST;
    output_bias_array.data = AI_PTR(g_frfconv_weights_map[0] + 35024);
    output_bias_array.data_start = AI_PTR(g_frfconv_weights_map[0] + 35024);
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_WEIGHTS);
  return false;
}


/**  PUBLIC APIs SECTION  *****************************************************/



AI_DEPRECATED
AI_API_ENTRY
ai_bool ai_frfconv_get_info(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_FRFCONV_MODEL_NAME,
      .model_signature   = AI_FRFCONV_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 1905462,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .params            = AI_STRUCT_INIT,
      .activations       = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x6b7e4b74,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}



AI_API_ENTRY
ai_bool ai_frfconv_get_report(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_FRFCONV_MODEL_NAME,
      .model_signature   = AI_FRFCONV_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 1905462,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .map_signature     = AI_MAGIC_SIGNATURE,
      .map_weights       = AI_STRUCT_INIT,
      .map_activations   = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x6b7e4b74,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}


AI_API_ENTRY
ai_error ai_frfconv_get_error(ai_handle network)
{
  return ai_platform_network_get_error(network);
}


AI_API_ENTRY
ai_error ai_frfconv_create(
  ai_handle* network, const ai_buffer* network_config)
{
  return ai_platform_network_create(
    network, network_config, 
    AI_CONTEXT_OBJ(&AI_NET_OBJ_INSTANCE),
    AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR, AI_TOOLS_API_VERSION_MICRO);
}


AI_API_ENTRY
ai_error ai_frfconv_create_and_init(
  ai_handle* network, const ai_handle activations[], const ai_handle weights[])
{
  ai_error err;
  ai_network_params params;

  err = ai_frfconv_create(network, AI_FRFCONV_DATA_CONFIG);
  if (err.type != AI_ERROR_NONE) {
    return err;
  }
  
  if (ai_frfconv_data_params_get(&params) != true) {
    err = ai_frfconv_get_error(*network);
    return err;
  }
#if defined(AI_FRFCONV_DATA_ACTIVATIONS_COUNT)
  /* set the addresses of the activations buffers */
  for (ai_u16 idx=0; activations && idx<params.map_activations.size; idx++) {
    AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_activations, idx, activations[idx]);
  }
#endif
#if defined(AI_FRFCONV_DATA_WEIGHTS_COUNT)
  /* set the addresses of the weight buffers */
  for (ai_u16 idx=0; weights && idx<params.map_weights.size; idx++) {
    AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_weights, idx, weights[idx]);
  }
#endif
  if (ai_frfconv_init(*network, &params) != true) {
    err = ai_frfconv_get_error(*network);
  }
  return err;
}


AI_API_ENTRY
ai_buffer* ai_frfconv_inputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    AI_NETWORK_OBJ(network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_inputs_get(network, n_buffer);
}


AI_API_ENTRY
ai_buffer* ai_frfconv_outputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    AI_NETWORK_OBJ(network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_outputs_get(network, n_buffer);
}


AI_API_ENTRY
ai_handle ai_frfconv_destroy(ai_handle network)
{
  return ai_platform_network_destroy(network);
}


AI_API_ENTRY
ai_bool ai_frfconv_init(
  ai_handle network, const ai_network_params* params)
{
  ai_network* net_ctx = AI_NETWORK_OBJ(ai_platform_network_init(network, params));
  ai_bool ok = true;

  if (!net_ctx) return false;
  ok &= frfconv_configure_weights(net_ctx, params);
  ok &= frfconv_configure_activations(net_ctx, params);

  ok &= ai_platform_network_post_init(network);

  return ok;
}


AI_API_ENTRY
ai_i32 ai_frfconv_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output)
{
  return ai_platform_network_process(network, input, output);
}


AI_API_ENTRY
ai_i32 ai_frfconv_forward(ai_handle network, const ai_buffer* input)
{
  return ai_platform_network_process(network, input, NULL);
}



#undef AI_FRFCONV_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME

