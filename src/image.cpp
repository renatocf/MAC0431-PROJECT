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

// Standard headers
//include <array>
//#include <cstdlib>
//#include <fstream>
//#include <cstdlib>
#include <iostream>
#include <vector>

void colorIntensity(double hmax, double pmax, double h)
{
	int delta;
	if(hmax>-1*pmax)
	{
		delta = hmax/255;
	}
	else
	{
		delta = -1.0*pmax/255;
	}
	if(h<0)
	{
		std::cout << h/delta << " 0 0" << std::endl;
	}
	else
	{
		std::cout << "0 0 " << h/delta << std::endl;
	}
}

void generateImage(int width, int height, double hmax, double pmax, std::vector<std::vector<double> >& lake)
{
	int i, j;
	std::cout << "P3" << std::endl;
	std::cout << width << " " << height << std::endl;

	for(i = 0; i<lake.size(); i++)
	{
		for(j = 0; j<lake[i].size(); j++)
		{
			colorIntensity(hmax, pmax, lake[i][j]);
		}
	}
}