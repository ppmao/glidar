/*
 * Copyright (c) 2014, John O. Woods, Ph.D.
 *   West Virginia University Applied Space Exploration Lab
 *   West Virginia Robotic Technology Center
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those
 * of the authors and should not be interpreted as representing official policies,
 * either expressed or implied, of the FreeBSD Project.
 */

#ifndef SERVICE_POSE_LOGGER_H
# define SERVICE_POSE_LOGGER_H

#include <Eigen/Dense>
#include <Eigen/Core>
#include <fstream>

// Need timestamp typedefs
#include "service.h"

class PoseLogger {
public:
  PoseLogger(const std::string& filename)
    : out(filename.c_str(), std::ios_base::out),
      pose_format(Eigen::FullPrecision, Eigen::DontAlignCols, ",", ",", "", "", "", "")
  { }

  ~PoseLogger() {
    out.close();
  }

  void log(const timestamp_t& timestamp, const Eigen::Matrix4f& pose, float score = std::numeric_limits<float>::infinity()) {
    out << timestamp << '\t' << pose.format(pose_format) << '\t' << score << '\n';
  }

  void close() {
    out.close();
  }

protected:
  std::ofstream out;
  Eigen::IOFormat pose_format;
};

#endif // SERVICE_POSE_LOGGER_H
