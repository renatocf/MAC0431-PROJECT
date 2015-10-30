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
#include <cstdlib>
#include <iostream>

template<std::size_t N>
using Dimension = std::array<unsigned int, N>;

template<std::size_t N>
std::istream &operator>>(std::istream &input, Dimension<N> &dim) {
  if (dim.empty()) return input;

  char lpar, rpar, comma;
  if (dim.size() != 1) input >> lpar;

  input >> dim[0];
  for (unsigned int i = 1; i < dim.size(); i++) {
    input >> dim[i];
    input >> comma;
  }

  if (dim.size() != 1) input >> rpar;

  return input;
}

int main(int argc, char **argv) {
  if (argc != 3) {
    std::cerr << "USAGE: " << argv[0] << " param_file num_procs" << std::endl;
    return EXIT_FAILURE;
  }

  Dimension<2> lake_dimensions;
  Dimension<2> matrix_dimensions;
  unsigned int time;
  double speed;
  unsigned int num_iterations;
  double drop_probability;
  unsigned int seed;

  std::cin >> lake_dimensions;
  std::cin >> matrix_dimensions;
  std::cin >> time;
  std::cin >> speed;
  std::cin >> num_iterations;
  std::cin >> drop_probability;
  std::cin >> seed;

  return EXIT_SUCCESS;
}
