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

#ifndef WAVES_WAVES_CIRCLE_BUILDER_
#define WAVES_WAVES_CIRCLE_BUILDER_

// Standard headers
#include <map>
#include <vector>

// Waves headers
#include "waves/Point.hpp"

namespace waves {

class CircleBuilder {
 public:
  // Concrete methods
  std::vector<Point> createCircle(Point origin, double radius);

 private:
  // Instance variables
  int nRoot_ = 0;
  std::map<Point, double> distanceTable_;

  // Concrete methods
  void unfoldPoints(std::vector<Point>& points);
  void removeExcess(std::vector<Point>& points);
  void addInvertedPoints(std::vector<Point>& points);
  void addOffset(std::vector<Point>& points, Point offset);
  void addOpposedVerticalPoints(std::vector<Point>& points);
  void addOpposedHorizontalPoints(std::vector<Point>& points);
  void createInitialPoints(std::vector<Point>& points, double radius);
  double distance(Point point);
};

}  // namespace waves

#endif  // WAVES_WAVES_CIRCLE_BUILDER_
