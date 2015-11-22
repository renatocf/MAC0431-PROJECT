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

#ifndef HPP_WAVES_WAVEMAKER_DEFINED
#define HPP_WAVES_WAVEMAKER_DEFINED

// Standard headers
#include <map>

// Waves headers
#include "waves/Point.hpp"
#include "waves/Drop.hpp"

namespace waves 
{
class WaveMaker
{

 public:
  // Constructors
  explicit WaveMaker(float error);
  // Concrete methods
  std::map<Point, float> makeWave(Drop& drop, unsigned int radius);
 private:
  // Instance variables
  float error_;
};
}

#endif
