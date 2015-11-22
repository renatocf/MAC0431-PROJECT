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

// Standard headers
#include <vector>

// Waves headers
#include "waves/Lake.hpp"

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
      height_(matrix_dimension.width(), matrix_dimension.length()),
      wave_properties_(wave_properties), rng_(seed),
      row_distribution_(0, length_), column_distribution_(0, width_),
      probability_distribution_(0.0, 1.0) {
}

/*----------------------------------------------------------------------------*/
/*                              CONCRETE METHODS                              */
/*----------------------------------------------------------------------------*/

void Lake::rainFor(unsigned int time,
                   unsigned int steps,
                   float drop_probability) {
  // Reserve space to avoid multiple allocations
  drops_.reserve(steps);

  #pragma omp parallel for schedule(static)
  for (unsigned int t = 0; t < steps; t++)
    if (shouldDrop(drop_probability))
      drops_.push_back(createDrop(time/t));

  // timestep: [0..total_time-1]
  for (unsigned int t = 0; t < steps-1; t++)
    for (unsigned int id = 0; id < drops_.size(); id++)
      ripple(drops_[id], time/t);

  // timestep: total_time
  for (unsigned int id = 0; id < drops_.size(); id++)
    rippleSnapshot(drops_[id], time/steps);
}

/*----------------------------------------------------------------------------*/

void Lake::printPGM(std::ostream &os) const {
  os << "P3" << std::endl;
  os << height_.cols() << " " << height_.rows() << std::endl;

  float delta
    = (max_height_ > -max_depth_) ? max_height_/255 : -max_depth_/255;

  for (unsigned int j = 0; j < height_.cols(); j++) {
    for (unsigned int i = 0; i < height_.rows(); i++) {
      int h = height_(i, j);
      os << "(" << i << "," << j << "): " << std::endl;
      if (h < 0)
        os << h/delta << " 0 0" << std::endl;
      else
        os << "0 0 " << h/delta << std::endl;
    }
  }
}

/*----------------------------------------------------------------------------*/

void Lake::printStatisticsTable(std::ostream &/* os */) const {
  // TODO(erikaAkab): Print table with statistics for (x,y) lake positions
  //                  Print *mean* and *standard deviation* (sqrt of variance).
  //                  Use precition %12.7f
}

/*----------------------------------------------------------------------------*/

void Lake::ripple(const Drop &drop, unsigned int timestep) {
  auto r = radius(drop, timestep);
  auto h = height(drop, r, timestep);
  auto points = affected_points(drop, r, timestep);

  #pragma omp parallel for schedule(static)
  for (unsigned int k = 0; k < points.size(); k++) {
    // TODO(dhinihan): Calculate distance of each point to drop
    updateMean(points[k].first, points[k].second, h);
    updateVariance(points[k].first, points[k].second, h);
  }
}

/*----------------------------------------------------------------------------*/

void Lake::rippleSnapshot(const Drop &drop, unsigned int timestep) {
  auto r = radius(drop, timestep);
  auto h = height(drop, r, timestep);
  auto points = affected_points(drop, r, timestep);

  #pragma omp parallel for schedule(static)
  for (unsigned int k = 0; k < points.size(); k++) {
    // TODO(dhinihan): Calculate distance of each point to drop
    updateMean(points[k].first, points[k].second, h);
    updateHeight(points[k].first, points[k].second, h);
    updateVariance(points[k].first, points[k].second, h);
  }
}

/*----------------------------------------------------------------------------*/

float Lake::height(const Drop &drop, unsigned int radius, unsigned int timestep) const {
  float distance = radius - wave_properties_.speed() * (timestep - drop.time());
  return distance / std::exp(distance*distance + drop.time()/10);
}

/*----------------------------------------------------------------------------*/

inline float Lake::radius(const Drop &drop, unsigned int timestep) const {
  return wave_properties_.speed() * (timestep - drop.time());
}

/*----------------------------------------------------------------------------*/

inline std::vector<Point>
Lake::affected_points(const Drop &/* drop */, unsigned int /* radius */, unsigned int /*timestep*/) const {
  // TODO(dhinihan): Given a drop, return all points affected by that drop
  //                 with a wave whose center is in radius.

  return std::vector<Point>{};
}

/*----------------------------------------------------------------------------*/

void Lake::updateMean(unsigned int /* i */, unsigned int /* j */,
                      float /* height */) {
  // TODO(karinaawoki): Update mean for position (i,j) incrementally.
  //                    Calculate mean of heights for all iterations.
  //                    Tip: http://math.stackexchange.com/questions/106700/
}

/*----------------------------------------------------------------------------*/

void Lake::updateHeight(unsigned int /* i */, unsigned int /* j */,
                        float /* height */) {
  // TODO(karinaawoki): Update height for position (i,j).
  //                    Calculate sum of heigths mean for a given iteration.
}

/*----------------------------------------------------------------------------*/

void Lake::updateVariance(unsigned int /* i */, unsigned int /* j */,
                          float /* height */) {
  // TODO(karinaawoki): Update variance for position (i,j) incrementally.
  //                    Calculate variance of heights for all iterations.
  //                    Tip: http://math.stackexchange.com/questions/102978/
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
