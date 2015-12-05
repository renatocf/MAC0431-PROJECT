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
#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>

// Waves headers
#include "waves/CircleBuilder.hpp"

namespace waves {

/*----------------------------------------------------------------------------*/
/*                              CONCRETE METHODS                              */
/*----------------------------------------------------------------------------*/

std::vector<Point> CircleBuilder::createCircle(float radius) {
  std::vector<Point> points;
  createInitialPoints(points, radius);
  unfoldPoints(points);
  // addOffset(points, origin);
  // removeExcess(points);
  return points;
}

/*----------------------------------------------------------------------------*/

void CircleBuilder::createInitialPoints(std::vector<Point> &points,
                                        float radius) {
  float minCoordinate = radius*sqrt(2)/2;
  int iMin = floor(minCoordinate);
  int jMax = ceil(minCoordinate);
  for (int i = iMin; i <= radius+1; i++)
    for (int j = 0; j <= std::min(i, jMax); j++)
      if (std::abs(distance(Point(i, j)) - radius) <= 0.5)
        points.emplace_back(i, j);
}

/*----------------------------------------------------------------------------*/

void CircleBuilder::unfoldPoints(std::vector<Point> &points) {
  addInvertedPoints(points);
  addOpposedVerticalPoints(points);
  addOpposedHorizontalPoints(points);
}

/*----------------------------------------------------------------------------*/

void CircleBuilder::addInvertedPoints(std::vector<Point> &points) {
  unsigned int actual_size = points.size();
  for (unsigned int i = 0; i < actual_size; i++)
    if (points[i].first != points[i].second)
      points.emplace_back(points[i].second, points[i].first);
}

/*----------------------------------------------------------------------------*/

void CircleBuilder::addOpposedVerticalPoints(std::vector<Point> &points) {
  unsigned int actual_size = points.size();
  for (unsigned int i = 0; i < actual_size; i++)
    if (points[i].first != 0)
      points.emplace_back(-points[i].first, points[i].second);
}

/*----------------------------------------------------------------------------*/

void CircleBuilder::addOpposedHorizontalPoints(std::vector<Point> &points) {
  unsigned int actual_size = points.size();
  for (unsigned int i = 0; i < actual_size; i++)
    if (points[i].second != 0)
      points.emplace_back(points[i].first, -points[i].second);
}

/*----------------------------------------------------------------------------*/

float CircleBuilder::distance(Point point) {
  auto a = point.first;
  auto b = point.second;
  return sqrt(a*a + b*b);
}

/*----------------------------------------------------------------------------*/

}  // namespace waves
