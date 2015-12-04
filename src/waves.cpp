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
#include <unistd.h>

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
#include "waves/WaveProperties.hpp"
#include "waves/WaveMaker.hpp"

int main(int argc, char **argv) {
  if (argc != 2 && argc != 3) {
    std::cerr << "USAGE: " << argv[0] << " param_file num_procs" << std::endl;
    return EXIT_FAILURE;
  }

  std::string input_file(argv[1]);
  int num_threads
    = (argc == 3 && atoi(argv[2]) <= 0) ? atoi(argv[2]) : omp_get_num_threads();

  // OpenMP initialization
  omp_set_num_threads(num_threads);

  waves::Dimension lake_dimensions;
  waves::Dimension matrix_dimensions;
  unsigned int time;
  float speed;
  float height_error;
  unsigned int steps;
  float drop_porcentage;
  unsigned int seed;

  std::ifstream input(input_file);

  input >> lake_dimensions;
  input >> matrix_dimensions;
  input >> time;
  input >> speed;
  input >> height_error;
  input >> steps;
  input >> drop_porcentage;
  input >> seed;

  waves::WaveProperties wave_properties(speed, height_error);

  waves::Lake lake(lake_dimensions, matrix_dimensions, wave_properties, seed);
  lake.rainFor(time, steps, drop_porcentage/100);

  std::ofstream lake_output("/tmp/lake.ppm");
  lake.printPPM(lake_output);

  std::ofstream table_output("/tmp/table.tsv");
  lake.printStatisticsTable(table_output, steps);

  return EXIT_SUCCESS;
}
