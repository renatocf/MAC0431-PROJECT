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
#include <array>
#include <iostream>

namespace waves {

template<std::size_t N>
using Dimension = std::array<unsigned int, N>;

}  // namespace waves

template<std::size_t N>
std::istream &operator>>(std::istream &input, waves::Dimension<N> &dim) {
  if (dim.empty()) return input;

  char lpar, rpar, comma;
  if (dim.size() != 1) input >> lpar;

  input >> dim[0];
  for (unsigned int i = 1; i < dim.size(); i++) {
    input >> comma;
    input >> dim[i];
  }

  if (dim.size() != 1) input >> rpar;

  return input;
}
