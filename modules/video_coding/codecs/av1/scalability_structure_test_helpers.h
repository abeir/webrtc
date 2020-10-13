/*
 *  Copyright (c) 2020 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */
#ifndef MODULES_VIDEO_CODING_CODECS_AV1_SCALABILITY_STRUCTURE_TEST_HELPERS_H_
#define MODULES_VIDEO_CODING_CODECS_AV1_SCALABILITY_STRUCTURE_TEST_HELPERS_H_

#include <stdint.h>

#include <vector>

#include "api/transport/rtp/dependency_descriptor.h"
#include "api/video/video_bitrate_allocation.h"
#include "common_video/generic_frame_descriptor/generic_frame_info.h"
#include "modules/video_coding/chain_diff_calculator.h"
#include "modules/video_coding/codecs/av1/scalable_video_controller.h"
#include "modules/video_coding/frame_dependencies_calculator.h"

namespace webrtc {

// Creates bitrate allocation with non-zero bitrate for given number of temporal
// layers for each spatial layer.
VideoBitrateAllocation EnableTemporalLayers(int s0, int s1 = 0, int s2 = 0);

class ScalabilityStructureWrapper {
 public:
  explicit ScalabilityStructureWrapper(ScalableVideoController& structure)
      : structure_controller_(structure) {}

  std::vector<GenericFrameInfo> GenerateFrames(int num_tempral_units,
                                               bool restart);

  std::vector<GenericFrameInfo> GenerateFrames(int num_temporal_units) {
    return GenerateFrames(num_temporal_units, /*restart=*/false);
  }

 private:
  ScalableVideoController& structure_controller_;
  std::bitset<8> buffer_contains_frame_ = 0;
  FrameDependenciesCalculator frame_deps_calculator_;
  ChainDiffCalculator chain_diff_calculator_;
  int64_t frame_id_ = 0;
};

}  // namespace webrtc

#endif  // MODULES_VIDEO_CODING_CODECS_AV1_SCALABILITY_STRUCTURE_TEST_HELPERS_H_