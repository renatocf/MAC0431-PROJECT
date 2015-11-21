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

#ifndef WAVES_WAVES_LAKE_
#define WAVES_WAVES_LAKE_

// Standard headers
#include <atomic>

// External headers
#include "Eigen/Core"
#include "prng_engine.hpp"

// Waves headers
#include "waves/Drop.hpp"
#include "waves/Dimension.hpp"
#include "waves/WaveProperties.hpp"

namespace waves {

class Lake {
 public:
  // Alias
  using Matrix = Eigen::Matrix<std::atomic_int, Eigen::Dynamic, Eigen::Dynamic>;

  // Constructors
  explicit Lake(const Dimension &lake_dimension,
                const WaveProperties &wave_properties,
                unsigned int seed = 42);

  explicit Lake(const Dimension &lake_dimension,
                const Dimension &matrix_dimension,
                const WaveProperties &wave_properties,
                unsigned int seed = 42);

  // Concrete methods
  void rainFor(unsigned int time, float drop_probability);
  void printPGM(std::ostream &os) const;

 private:
  // Instance variables
  unsigned int width_, length_;
  Matrix matrix_;
  WaveProperties wave_properties_;
  mutable unsigned int seed_;
  mutable sitmo::prng_engine rng_;

  mutable std::uniform_int_distribution<unsigned int> row_generator_;
  mutable std::uniform_int_distribution<unsigned int> column_generator_;
  mutable std::uniform_real_distribution<float> probability_generator_;

  float max_depth_ = 0, max_height_ = 0;

  // Concrete methods
  void ripple(const Drop &drop, unsigned int total_time);

  float height(const Drop &drop, float r) const;
  Point drawPosition() const;
  bool shouldDrop(float drop_probability) const;
  Drop drop(unsigned int time) const;
};

}  // namespace waves

#endif  // WAVES_WAVES_LAKE_
