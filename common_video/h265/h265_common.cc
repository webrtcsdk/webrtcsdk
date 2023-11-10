/*
 *  Copyright (c) 2023 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#include "common_video/h265/h265_common.h"
#include "common_video/h264/h264_common.h"

namespace webrtc {
namespace H265 {

const uint8_t kNaluTypeMask = 0x7E;

std::vector<NaluIndex> FindNaluIndices(const uint8_t* buffer,
                                        size_t buffer_size) {
  std::vector<NaluIndex> sequences;
  if (buffer_size < kNaluShortStartSequenceSize) {
    return sequences;
  }

  const size_t end = buffer_size - kNaluShortStartSequenceSize;
  for (size_t i = 0; i < end;) {
    if (buffer[i + 2] > 1) {
      i += 3;
    } else if (buffer[i + 2] == 0x01 && buffer[i + 1] == 0x00 && buffer[i] == 0x00) {
      // We found a start sequence, now check if it was a 3 of 4 byte one.
      NaluIndex index = {i, i + 3, 0};
      if (index.start_offset > 0 && buffer[index.start_offset - 1] == 0)
        --index.start_offset;

      // Update length of previous entry.
      auto it = sequences.rbegin();
      if (it != sequences.rend())
        it->payload_size = index.start_offset - it->payload_start_offset;

      sequences.push_back(index);

      i += 3;
    } else {
      ++i;
    }
  }

  // Update length of last entry, if any.
  auto it = sequences.rbegin();
  if (it != sequences.rend())
    it->payload_size = buffer_size - it->payload_start_offset;

  return sequences;
}

NaluType ParseNaluType(uint8_t data) {
  return static_cast<NaluType>((data & kNaluTypeMask) >> 1);
}

std::vector<uint8_t> ParseRbsp(const uint8_t* data, size_t length) {
  return H264::ParseRbsp(data, length);
}

void WriteRbsp(const uint8_t* bytes, size_t length, rtc::Buffer* destination) {
  H264::WriteRbsp(bytes, length, destination);
}

uint32_t Log2(uint32_t value) {
  uint32_t result = 0;
  // If value is not a power of two an additional bit is required
  // to account for the ceil() of log2() below.
  if ((value & (value - 1)) != 0) {
    ++result;
  }
  while (value > 0) {
    value >>= 1;
    ++result;
  }

  return result;
}

}  // namespace H265
}  // namespace webrtc
