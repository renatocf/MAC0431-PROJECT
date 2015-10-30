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

#ifndef WAVES_WAVES_DROP_
#define WAVES_WAVES_DROP_

// Standard headers
#include <vector>

// Waves headers
#include "waves/Point.hpp"

namespace waves {

class Drop {
 public:
  Drop(unsigned int time)
      : time_(time) {
  }

  unsigned int time() const { 
  	return time_;	
  }

 private: 
  unsigned int time_;
  double distance_;
  double height_;
  std::vector<Point> affected_points_;
};

}  // namespace waves

#endif // WAVES_WAVES_DROP_
