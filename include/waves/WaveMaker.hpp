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

#ifndef WAVES_WAVE_MAKER_
#define WAVES_WAVE_MAKER_

// Standard headers
#include <map>
#include <vector>

// Waves headers
#include "waves/Point.hpp"
#include "waves/Drop.hpp"
#include "waves/CircleBuilder.hpp"

namespace waves {

// Forward declaration
class Lake;

class WaveMaker {
 public:
  // Concrete methods
  std::map<float, std::vector<Point>> makeWave(const Drop& drop,
                                               unsigned int radius,
                                               unsigned int timestep,
                                               Lake* lake);

 private:
  // Instance variables
  std::map<unsigned int, std::vector<Point>> circle_cache_;
  CircleBuilder builder_;
  float square_error_;

  // Concrete methods
  std::vector<Point> getCircle(unsigned int radius);
  std::vector<Point> makeCircle(unsigned int radius,
                                const Drop& drop,
                                Dimension& sizes);
};

}  // namespace waves

#endif  // WAVES_WAVE_MAKER_
