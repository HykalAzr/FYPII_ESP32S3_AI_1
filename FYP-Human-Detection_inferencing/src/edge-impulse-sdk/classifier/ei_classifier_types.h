/*
 * Copyright (c) 2022 EdgeImpulse Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an "AS
 * IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language
 * governing permissions and limitations under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _EDGE_IMPULSE_RUN_CLASSIFIER_TYPES_H_
#define _EDGE_IMPULSE_RUN_CLASSIFIER_TYPES_H_

#include <stdint.h>
// needed for standalone C example
#include "model-parameters/model_metadata.h"

#ifndef EI_CLASSIFIER_MAX_OBJECT_DETECTION_COUNT
#define EI_CLASSIFIER_MAX_OBJECT_DETECTION_COUNT 10
#endif

typedef struct {
    const char *label;
    float value;
} ei_impulse_result_classification_t;

typedef struct {
    float mean_value;
    float max_value;
} ei_impulse_visual_ad_result_t;

typedef struct {
    const char *label;
    uint32_t x;
    uint32_t y;
    uint32_t width;
    uint32_t height;
    float value;
} ei_impulse_result_bounding_box_t;

typedef struct {
    int sampling;
    int dsp;
    int classification;
    int anomaly;
    int64_t dsp_us;
    int64_t classification_us;
    int64_t anomaly_us;
} ei_impulse_result_timing_t;

typedef struct {
    ei_impulse_result_bounding_box_t *bounding_boxes;
    uint32_t bounding_boxes_count;
#if EI_CLASSIFIER_LABEL_COUNT == 0
    // EI_CLASSIFIER_LABEL_COUNT can be 0 for anomaly only models
    // to prevent compiler warnings/errors, we need to have at least one element
    ei_impulse_result_classification_t classification[1];
#else
    ei_impulse_result_classification_t classification[EI_CLASSIFIER_LABEL_COUNT];
#endif
    float anomaly;
    ei_impulse_result_timing_t timing;
    bool copy_output;
#if EI_CLASSIFIER_HAS_VISUAL_ANOMALY
    ei_impulse_result_bounding_box_t *visual_ad_grid_cells;
    uint32_t visual_ad_count;
    ei_impulse_visual_ad_result_t visual_ad_result;
#endif // EI_CLASSIFIER_HAS_VISUAL_ANOMALY
} ei_impulse_result_t;

#endif // _EDGE_IMPULSE_RUN_CLASSIFIER_TYPES_H_
