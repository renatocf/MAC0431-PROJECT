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
#include <vector>

// Waves headers
#include "waves/Lake.hpp"
#include "waves/WaveMaker.hpp"

namespace waves {

/*----------------------------------------------------------------------------*/
/*                               STATIC METHODS                               */
/*----------------------------------------------------------------------------*/

void Lake::animationExample() {
  waves::WaveMaker maker;
  for (int timestep = 10; timestep < 100; timestep++) {
    float speed = 1.5;
    float error = 0.001;
    unsigned int radius = (timestep - 10) * speed;

    waves::Drop drop(10, waves::Point(30, 17));

    waves::WaveProperties props(speed, error);
    waves::Lake lake(waves::Dimension(100, 100), props, 37);

    auto map = maker.makeWave(drop, radius, timestep, &lake);

    char matrix[100][100];

    for (int i = 0; i < 100; i ++)
      for (int j = 0; j < 100; j ++)
        matrix[i][j] = ' ';

    char valor = '1';

    for (auto assoc : map) {
      for (auto point : assoc.second) {
        matrix[point.first][point.second] = valor;
      }
      valor++;
    }

    for (int i = 0; i < 100; i ++) {
      for (int j = 0; j < 100; j ++)
        std::cout << matrix[i][j];
      std::cout << std::endl;
    }
    usleep(100000);
  }
}

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
  float timeunit = time/steps;

  // Reserve space to avoid multiple allocations
  drops_.reserve(steps);

  #pragma omp parallel for schedule(static)
  for (unsigned int t = 0; t < steps; t++)
    if (shouldDrop(drop_probability))
      drops_.push_back(createDrop(t * timeunit));

  // timestep: [0..total_time-1]
  for (unsigned int t = 0; t < steps-1; t++)
    for (unsigned int id = 0; id < drops_.size(); id++)
      ripple(drops_[id], t * timeunit);

  // timestep: total_time
  for (unsigned int id = 0; id < drops_.size(); id++)
    rippleSnapshot(drops_[id], timeunit);
}

/*----------------------------------------------------------------------------*/

void Lake::printPPM(std::ostream &os) const {
  os << "P3" << height_.cols() << " " << height_.rows() << " 255" << std::endl;

  float delta
    = (max_height_ > -max_depth_) ? max_height_/255 : -max_depth_/255;

  for (unsigned int j = 0; j < height_.cols(); j++) {
    for (unsigned int i = 0; i < height_.rows(); i++) {
      float h = height_(i, j);
      int height_color = static_cast<int>(h/delta + 0.5);

      if (h < 0)
        os << height_color << " 0 0" << "\t";
      else
        os << "0 0 " << height_color << "\t";
    }
    os << std::endl;
  }
}

/*----------------------------------------------------------------------------*/

Dimension Lake::dimension() const {
  return Dimension(width_, length_);
}

/*----------------------------------------------------------------------------*/

WaveProperties Lake::wave_properties() const {
  return wave_properties_;
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
  auto point_map = affected_points(drop, r, timestep);

  for (auto association : point_map) {
    const auto& height = association.first;
    const auto& point = association.second;
    #pragma omp parallel for schedule(static)
    for (unsigned int k = 0; k < association.second.size(); k++) {
      updateMean(point[k].first, point[k].second, height);
      updateVariance(point[k].first, point[k].second, height);
    }
  }
}

/*----------------------------------------------------------------------------*/

void Lake::rippleSnapshot(const Drop &drop, unsigned int timestep) {
  auto r = radius(drop, timestep);
  auto point_map = affected_points(drop, r, timestep);

  for (auto association : point_map) {
    const auto& height = association.first;
    const auto& point = association.second;
    #pragma omp parallel for schedule(static)
    for (unsigned int k = 0; k < association.second.size(); k++) {
      updateMean(point[k].first, point[k].second, height);
      updateHeight(point[k].first, point[k].second, height);
      updateVariance(point[k].first, point[k].second, height);
    }
  }
}

/*----------------------------------------------------------------------------*/

float Lake::height(const Drop &drop,
                   unsigned int radius,
                   unsigned int timestep) const {
  float distance
    = radius - wave_properties_.speed() * (timestep - drop.time());
  return distance / std::exp(distance*distance + drop.time()/10);
}

/*----------------------------------------------------------------------------*/

inline float Lake::radius(const Drop &drop, unsigned int timestep) const {
  return wave_properties_.speed() * (timestep - drop.time());
}

/*----------------------------------------------------------------------------*/

inline std::map<float, std::vector<Point>>
Lake::affected_points(const Drop& drop,
                      unsigned int radius,
                      unsigned int timestep) {
  return wave_maker_.makeWave(drop, radius, timestep, this);
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
