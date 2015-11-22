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
#include "waves/CircleBuilder.hpp"
#include "waves/WaveMaker.hpp"
#include "waves/Drop.hpp"


namespace waves{

  /*----------------------------------------------------------------------------*/
  /*                                CONSTRUCTORS                                */
  /*----------------------------------------------------------------------------*/

  WaveMaker::WaveMaker(float error) : error_(error){}

  /*----------------------------------------------------------------------------*/
  /*                              CONCRETE METHODS                              */
  /*----------------------------------------------------------------------------*/

  std::map<Point, float> WaveMaker::makeWave(Drop& drop, unsigned int radius){
    std::map<Point, float> map;
    std::vector<std::vector<Point>> points;
    CircleBuilder builder;
    float actualRadius = radius;
    float actualHeigth = drop.height(actualRadius);
    
    points.push_back(builder.createCircle(actualRadius));
    actualRadius++;
    actualHeigth = drop.height(actualRadius);
    std::cout << "height: " << actualHeigth << std::endl;
    
    while(actualHeigth*actualHeigth >= error_*error_){
      points.push_back(builder.createCircle(actualRadius));
      actualRadius++;
      actualHeigth = drop.height(actualRadius);
      std::cout << "height: " << actualHeigth << std::endl;
    }

    actualRadius = radius - 1;
    actualHeigth = drop.height(actualRadius);
    std::cout << "height: " << actualHeigth << std::endl;
    while(actualHeigth*actualHeigth >= error_*error_){
      points.push_back(builder.createCircle(actualRadius));
      actualRadius--;
      actualHeigth = drop.height(actualRadius);
      std::cout << "height: " << actualHeigth << std::endl;
    }


    for (auto pointVector : points){
      std::cout << "------" << std::endl; 
      for (auto point : pointVector){
        std::cout << point.first << ", " << point.second << std::endl;  
      }
    }

    return map;
  }

}



