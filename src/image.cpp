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
#include <fstream> 
#include <vector>

using namespace std;



string colorIntensity(double hmax, double pmax, double h)
{
	int delta;
	string image;
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
		image = h/delta + " 0 0" + endl;
	}
	else
	{
		image = "0 0 " + h/delta + endl;
	}
	return image;
}

string generateImage(int width, int height, double hmax, double pmax, Lake lake)
{
	int i, j;
	string image;
	image = "P3" + endl;
	image = width + " " + height + endl;

	for(i = 0; i<lake.size(); i++)
	{
		for(j = 0; j<lake(i).size(); j++)
		{
			image += colorIntensity(hmax, pmax, lake(i,j);
		}
	}
	return image;
}

void generateImageFile(int width, int height, double hmax, double pmax, Lake lake)
{
	ofstream out; 
	out.open("lake");
	out<<generateImage(width, height, hmax, pmax, lake);
	out.close();
}