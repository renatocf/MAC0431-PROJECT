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

void Lake::rainFor(unsigned int total_time,
                   float drop_probability) {
# pragma omp parallel for schedule(dynamic, 100)
  for (unsigned int t = 0; t < total_time; t++)
    if (shouldDrop(drop_probability))
      ripple(createDrop(t), total_time);
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

void Lake::ripple(const Drop &/* drop */, unsigned int /* total_time */) {
  // Given a drop, generate its corresponding wave
  // Must set max_height_ and max_depth_
}

/*----------------------------------------------------------------------------*/

inline float Lake::height(const Drop &drop, float r) const {
  float distance = r - wave_properties_.speed() * drop.time();
  return distance / std::exp(distance*distance + drop.time()/10);
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
