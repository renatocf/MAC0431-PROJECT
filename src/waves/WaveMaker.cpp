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
#include <map>
#include <iostream>

// Waves headers
#include "waves/WaveMaker.hpp"
#include "waves/Drop.hpp"


namespace waves{

  /*----------------------------------------------------------------------------*/
  /*                              CONCRETE METHODS                              */
  /*----------------------------------------------------------------------------*/

  std::map<float, std::vector<Point>> WaveMaker::makeWave(Drop& drop, unsigned int radius, unsigned int timestep, Lake& lake){
    std::map<float, std::vector<Point>> map;
    unsigned int actualRadius = radius;
    Dimension sizes = lake.dimension();
    float actualHeigth = lake.height(drop, actualRadius, timestep);
    
    float square_error = lake.wave_properties().error();
    square_error *= square_error;

    do {
      map[actualHeigth] = makeCircle(actualRadius, drop, sizes);
      actualRadius++;
      actualHeigth = lake.height(drop, actualRadius, timestep);
    } while(actualHeigth*actualHeigth >= square_error);

    actualRadius = radius -1;
    actualHeigth = lake.height(drop, actualRadius, timestep);

    while(actualHeigth*actualHeigth >= square_error && actualRadius > 0){
      map[actualHeigth] = makeCircle(actualRadius, drop, sizes);
      actualRadius--;
      actualHeigth = lake.height(drop, actualRadius, timestep);
    };

    return map;
  }

  std::vector<Point> WaveMaker::getCircle(unsigned int radius){
    auto it = circle_cache_.find(radius);
    if (it != circle_cache_.end()){
      return (*it).second;
    }

    circle_cache_[radius] = builder_.createCircle(radius);
    return circle_cache_[radius];
  }

  std::vector<Point> WaveMaker::makeCircle(unsigned int radius, Drop& drop, Dimension& sizes){
    auto circle = getCircle(radius);
    builder_.addOffset(circle, drop.position());
    builder_.removeExcess(circle, sizes);
    return circle;
  }



}



