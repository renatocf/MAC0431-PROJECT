//****************************************************************************//
// Copyright 2015 MAC0431-PROJECT                                             //
//                                                                            //
// Licensed under the Apache License, Version 2.0 (the "License");            //
// you may not use this file except in compliance with the License.           //
// You may obtain a copy of the License at                                    //
//                                                                            //
//     http://www.apache.org/licenses/LICENSE-2.0                             //
//                                                                            //
// Unless required by applicable law or agreed to in writing, software        //
// distributed under the License is distributed on an "AS IS" BASIS,          //
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.   //
// See the License for the specific language governing permissions and        //
// limitations under the License.                                             //
//****************************************************************************//

// C headers
#include <unistd.h>

// Standard headers
#include <map>
#include <cstdio>
#include <string>
#include <vector>

// Waves headers
#include "waves/Lake.hpp"
#include "waves/WaveMaker.hpp"

namespace waves {

/*----------------------------------------------------------------------------*/
/*                                CONSTRUCTORS                                */
/*----------------------------------------------------------------------------*/

Lake::Lake(const Dimension &lake_dimension,
           const WaveProperties &wave_properties,
           unsigned int seed)
    : Lake(lake_dimension, lake_dimension, wave_properties, seed) {
}

/*----------------------------------------------------------------------------*/

Lake::Lake(const Dimension &lake_dimension,
           const Dimension &matrix_dimension,
           const WaveProperties &wave_properties,
           unsigned int seed)
    : width_(lake_dimension.width()), length_(lake_dimension.length()),
      sum_height_(lake_dimension.width(), lake_dimension.length()),
      variance_(lake_dimension.width(), lake_dimension.length()),
      height_(lake_dimension.width(), lake_dimension.length()),
      wave_properties_(wave_properties), rng_(seed),
      row_distribution_(0, width_), column_distribution_(0, length_),
      probability_distribution_(0.0, 1.0) {
}

/*----------------------------------------------------------------------------*/
/*                              CONCRETE METHODS                              */
/*----------------------------------------------------------------------------*/

void Lake::rainFor(unsigned int time,
                   unsigned int steps,
                   float drop_probability) {
  float timeunit = 1.0*time/steps;

  // Reserve space to avoid multiple allocations
  drops_.reserve(steps);

  // #pragma omp parallel for schedule(static)
  for (unsigned int t = 0; t < steps; t++)
    if (shouldDrop(drop_probability))
      drops_.push_back(createDrop(t * timeunit));

  // timestep: [0..total_time-1]
  for (unsigned int t = 0; t < steps-1; t++)
    for (unsigned int id = 0; id < drops_.size(); id++)
      ripple(drops_[id], t, timeunit);

  // timestep: total_time
  for (unsigned int id = 0; id < drops_.size(); id++)
    rippleSnapshot(drops_[id], (steps-1), timeunit);
}

/*----------------------------------------------------------------------------*/

void Lake::printPPM(const std::string &file_name) const {
  auto file = std::fopen(file_name.c_str(), "w");
  std::fprintf(file, "P3\n%ld %ld\n255\n", height_.cols(), height_.rows());

  float delta
    = (max_height_ > -max_depth_) ? max_height_/255 : -max_depth_/255;

  for (unsigned int i = 0; i < height_.rows(); i++) {
    for (unsigned int j = 0; j < height_.cols(); j++) {
      float h = height_(i, j);
      int height_color = static_cast<int>(h/delta + 0.5);

      if (h < 0)
        std::fprintf(file, "%d 0 0\n", -height_color);
      else if (h > 0)
        std::fprintf(file, "0 0 %d\n", height_color);
      else
        std::fputs("0 0 0\n", file);
    }
  }

  std::fclose(file);
}

/*----------------------------------------------------------------------------*/

Dimension Lake::dimension() const {
  return Dimension(length_, width_);
}

/*----------------------------------------------------------------------------*/

WaveProperties Lake::wave_properties() const {
  return wave_properties_;
}

/*----------------------------------------------------------------------------*/

void Lake::printStatisticsTable(const std::string &file_name,
                                unsigned int steps) const {
  auto file = std::fopen(file_name.c_str(), "w");

  for (unsigned int i = 0; i < height_.rows(); i++) {
    for (unsigned int j = 0; j < height_.cols(); j++) {
      std::fprintf(file, "%d\t" "%d\t" "%12.7f\t" "%12.7f\n",
                   i, j, sum_height_(i, j)/steps, std::sqrt(variance_(i, j)));
    }
  }

  std::fclose(file);
}

/*----------------------------------------------------------------------------*/

void Lake::ripple(const Drop &drop, unsigned int step, float timeunit) {
  auto point_map
    = affected_points(drop, radius(drop, step*timeunit), step*timeunit);

  for (const auto &association : point_map) {
    const auto &height = association.first;
    const auto &points = association.second;
    #pragma omp parallel for schedule(static)
    for (unsigned int k = 0; k < points->size(); k++) {
      int i = (*points)[k].first + drop.position().first;
      int j = (*points)[k].second + drop.position().second;
      if (i >= 0 && j >= 0
      &&  i < static_cast<int>(width_) && j < static_cast<int>(length_)) {
        updateVariance(i, j, height_(i, j), step);
        updateSum(i, j, height_(i, j), step);
      }
    }
  }
}
/*----------------------------------------------------------------------------*/

void Lake::rippleSnapshot(const Drop &drop, unsigned int step, float timeunit) {
  auto point_map
    = affected_points(drop, radius(drop, step*timeunit), step*timeunit);

  for (const auto &association : point_map) {
    const auto &height = association.first;
    const auto &points = association.second;
    #pragma omp parallel for schedule(static)
    for (unsigned int k = 0; k < points->size(); k++) {
      int i = (*points)[k].first + drop.position().first;
      int j = (*points)[k].second + drop.position().second;
      if (i >= 0 && j >= 0
      &&  i < static_cast<int>(width_) && j < static_cast<int>(length_)) {
        updateHeight(i, j, height, step);
        updateVariance(i, j, height_(i, j), step);
        updateSum(i, j, height_(i, j), step);
      }
    }
  }
}

/*----------------------------------------------------------------------------*/

float Lake::height(const Drop &drop,
                   unsigned int radius,
                   unsigned int timestep) const {
  unsigned int time_elapsed = timestep - drop.time();
  float distance = radius - wave_properties_.speed() * time_elapsed;
  return distance / std::exp(distance*distance + time_elapsed/10);
}

/*----------------------------------------------------------------------------*/

inline float Lake::radius(const Drop &drop, unsigned int timestep) const {
  return wave_properties_.speed() * (timestep - drop.time());
}

/*----------------------------------------------------------------------------*/

inline std::map<float, std::vector<Point>*>
Lake::affected_points(const Drop& drop,
                      unsigned int radius,
                      unsigned int timestep) {
  return wave_maker_.makeWave(drop, radius, timestep, this);
}

/*----------------------------------------------------------------------------*/

void Lake::updateSum(unsigned int i, unsigned int j,
                      float height, unsigned int step) {
  sum_height_(i, j) += height_(i, j);
}

/*----------------------------------------------------------------------------*/

void Lake::updateHeight(unsigned int i, unsigned int j,
                        float height, unsigned int step) {
  height_(i, j) += height;
  if (height < max_depth_) max_depth_ = height;
  else if (height > max_height_) max_height_ = height;
}

/*----------------------------------------------------------------------------*/

void Lake::updateVariance(unsigned int i, unsigned int j,
                          float height, unsigned int step) {
  float mean = sum_height_(i, j)*1.0/step;

  if (step == 1)
    variance_(i, j) = 0;
  else
    variance_(i, j) = variance_(i, j) * (step-2)/(step-1)
                    + (height-mean) * (height-mean)/step;
}

/*----------------------------------------------------------------------------*/

inline Point Lake::drawPosition() const {
  return Point(row_distribution_(rng_), column_distribution_(rng_));
}

/*----------------------------------------------------------------------------*/

inline Drop Lake::createDrop(unsigned int time) const {
  return Drop(time, drawPosition());
}

/*----------------------------------------------------------------------------*/

inline bool Lake::shouldDrop(float drop_probability) const {
  return probability_distribution_(rng_) < drop_probability;
}

/*----------------------------------------------------------------------------*/

}  // namespace waves
