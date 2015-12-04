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
#include <map>
#include <vector>

// External headers
#include "Eigen/Core"
#include "prng_engine.hpp"

// Waves headers
#include "waves/Drop.hpp"
#include "waves/Dimension.hpp"
#include "waves/WaveProperties.hpp"
#include "waves/WaveMaker.hpp"

namespace waves {

class Lake {
 public:
  // Alias
  using Matrix = Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic>;

  // Static methods
  // static void animationExample();

  // Constructors
  explicit Lake(const Dimension &lake_dimension,
                const WaveProperties &wave_properties,
                unsigned int seed = 42);

  explicit Lake(const Dimension &lake_dimension,
                const Dimension &matrix_dimension,
                const WaveProperties &wave_properties,
                unsigned int seed = 42);

  // Concrete methods
  void rainFor(unsigned int time, unsigned int steps, float drop_probability);

  void printPPM(std::ostream &os) const;
  void printStatisticsTable(std::ostream &os) const;

  float height(const Drop &drop,
               unsigned int radius,
               unsigned int timestep) const;

  Dimension dimension() const;
  WaveProperties wave_properties() const;

 private:
  // Instance variables
  unsigned int width_, length_;
  Matrix height_, mean_, variance_;
  WaveProperties wave_properties_;
  std::vector<Drop> drops_;
  WaveMaker wave_maker_;

  mutable sitmo::prng_engine rng_;
  mutable std::uniform_int_distribution<unsigned int> row_distribution_;
  mutable std::uniform_int_distribution<unsigned int> column_distribution_;
  mutable std::uniform_real_distribution<float> probability_distribution_;

  float max_depth_ = 0, max_height_ = 0;

  // Concrete methods
  void ripple(const Drop &drop, unsigned int timestep);
  void rippleSnapshot(const Drop &drop, unsigned int timestep);

  float radius(const Drop &drop, unsigned int timestep) const;

  std::map<float, std::vector<Point>*>
  affected_points(const Drop &drop, unsigned int radius, unsigned int timestep);

  void updateMean(unsigned int i, unsigned int j, float height, unsigned int iteraction);
  void updateHeight(unsigned int i, unsigned int j, float height, unsigned int iteraction);
  void updateVariance(unsigned int i, unsigned int j, float height, unsigned int iteraction);

  Point drawPosition() const;

  Drop createDrop(unsigned int time) const;
  bool shouldDrop(float drop_probability) const;
};

}  // namespace waves

#endif  // WAVES_WAVES_LAKE_
