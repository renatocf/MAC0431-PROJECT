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

// C headers
#include <omp.h>

// Standard headers
#include <array>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <iostream>

// Waves headers
#include "waves/Drop.hpp"
#include "waves/Lake.hpp"
#include "waves/Dimension.hpp"

double generate_probability(unsigned int *seed) {
  return static_cast<double>(rand_r(seed))/RAND_MAX;
}

std::vector<waves::Drop> generate_drops(unsigned int timestamp,
                                        double drop_probability,
                                        unsigned int *seed) {
  std::vector<waves::Drop> drops;
  for (unsigned int i = 0; i < timestamp; i++) {
    if (generate_probability(seed) < drop_probability) {
      drops.emplace_back(i);
    }
  }
  return drops;
}

int main(int argc, char **argv) {
  if (argc != 3) {
    std::cerr << "USAGE: " << argv[0] << " param_file num_procs" << std::endl;
    return EXIT_FAILURE;
  }

  std::string input_file(argv[1]);
  int num_threads
    = (atoi(argv[2])) <= 0 ? atoi(argv[2]) : omp_get_num_threads();

  // OpenMP initialization
  omp_set_num_threads(num_threads);

  waves::Dimension lake_dimensions;
  waves::Dimension matrix_dimensions;
  unsigned int time;
  double speed;
  double height_error;
  unsigned int num_iterations;
  double drop_probability;
  unsigned int seed;

  std::ifstream input(input_file);

  input >> lake_dimensions;
  input >> matrix_dimensions;
  input >> time;
  input >> speed;
  input >> height_error;
  input >> num_iterations;
  input >> drop_probability;
  input >> seed;

  auto drops = generate_drops(num_iterations, drop_probability/100, &seed);

  for (auto drop : drops) {
    std::cout << drop.time() << std::endl;
  }

  waves::Lake lake(lake_dimensions, matrix_dimensions);
  lake.printPGM(std::cout, 100, 100, 10, 10);

  return EXIT_SUCCESS;
}
