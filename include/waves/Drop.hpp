/******************************************************************************/
/* Copyright 2015 MAC0431-PROJECT                                             */
/*                                                                            */
/* Licensed under the Apache License, Version 2.0 (the "License");            */
/* you may not use this file except in compliance with the License.           */
/* You may obtain a copy of the License at                                    */
/*                                                                            */
/*     http://www.apache.org/licenses/LICENSE-2.0                             */
/*                                                                            */
/* Unless required by applicable law or agreed to in writing, software        */
/* distributed under the License is distributed on an "AS IS" BASIS,          */
/* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.   */
/* See the License for the specific language governing permissions and        */
/* limitations under the License.                                             */
/******************************************************************************/

#include <array>
#include <cstdlib>
#include <fstream>
#include <iostream>

#ifndef WAVES_WAVES_DROP_
#define WAVES_WAVES_DROP_

//math library
#include <cmath>

// Standard headers
#include <vector>

// Waves headers
#include "waves/Point.hpp"

namespace waves {

class Drop {
 public:
  Drop(int time)
      : time_(time) {
  }

  int time() const { 
    return time_; 
  }

  double height_function(double ro, double speed) {

    double factor_one = (ro - speed*time());
    double exp_one = (-1)*std::pow((ro-speed*time()),2);
    double exp_two = (-1)*(time()/10);
    double factor_two = std::exp(exp_one);
    double factor_three = std::exp(exp_two);

    height_ = factor_one*factor_two*factor_three; 

    return height_;
  }

 private: 
  int time_;
  double distance_;
  double height_;
  std::vector<Point> affected_points_;
};

}  // namespace waves

#endif // WAVES_WAVES_DROP_
