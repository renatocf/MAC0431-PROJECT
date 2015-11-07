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

#include <iostream>
#include <math.h>
#include <algorithm>

// Libraries
#include "CircleBuilder.hpp"
using namespace waves;
using namespace std;

#define RADIUSI 100

vector<Point> CircleBuilder::createCircle(Point origin, double radius){
  vector<Point> points;
  createInitialPoints(points, radius);
  unfoldPoints(points);
  addOffset(points, origin);
  removeExcess(points);
  return points;
}

void CircleBuilder::createInitialPoints(vector<Point>& points, double radius){
  double minCoordinate = radius*sqrt(2)/2;
  int iMin = floor(minCoordinate);
  int jMax = ceil(minCoordinate);
  for(int i = iMin; i <= radius+1; i++)
    for(int j = 0; j <= min(i, jMax); j++)
      if(abs(distance(Point(i,j)) - radius) <= 0.5)
        points.emplace_back(i,j);
}

void CircleBuilder::unfoldPoints(vector<Point>& points){
  addInvertedPoints(points);
  addOpposedVerticalPoints(points);
  addOpposedHorizontalPoints(points);
}

void CircleBuilder::addInvertedPoints(vector<Point>& points){
  unsigned int actual_size = points.size();
  for(unsigned int i = 0; i < actual_size; i++)
    if(points[i].first != points[i].second)
      points.emplace_back(points[i].second, points[i].first);
}

void CircleBuilder::addOpposedVerticalPoints(vector<Point>& points){
  unsigned int actual_size = points.size();
  for(unsigned int i = 0; i < actual_size; i++)
    if(points[i].first != 0)
      points.emplace_back(-points[i].first, points[i].second);
}

void CircleBuilder::addOpposedHorizontalPoints(vector<Point>& points){
  unsigned int actual_size = points.size();
  for(unsigned int i = 0; i < actual_size; i++)
    if(points[i].second != 0)
      points.emplace_back(points[i].first, -points[i].second);
}

void CircleBuilder::addOffset(vector<Point>& points, Point offset){
  for(unsigned int i = 0; i < points.size(); i++){
    points[i].first += offset.first;
    points[i].second += offset.second;
  }
}

void CircleBuilder::removeExcess(vector<Point>& points){
  for (auto it  = points.begin(); 
            it != points.end();){
   
    if(it->first < 0 || it->second < 0) 
      it = points.erase(it);
    else 
      ++it;
  }
}

double CircleBuilder::distance(Point point){
  auto a = point.first;
  auto b = point.second;
  nRoot_++;
  return sqrt(a*a + b*b); 
  
  /*auto it = distanceTable_.find(point);
  if (it != distanceTable_.end())
    return (*it).second;
  
  auto a = point.first;
  auto b = point.second;
  auto distance = sqrt(a*a + b*b);
  distanceTable_[point] = distance;
  nRoot_++;
  return distance;
  */
}