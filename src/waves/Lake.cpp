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

// Waves headers
#include "waves/Lake.hpp"

namespace waves {

/*----------------------------------------------------------------------------*/
/*                                CONSTRUCTORS                                */
/*----------------------------------------------------------------------------*/

Lake::Lake(const Dimension &lake_dimension)
    : Lake(lake_dimension, lake_dimension) {
}

/*----------------------------------------------------------------------------*/

Lake::Lake(const Dimension &lake_dimension,
     const Dimension &matrix_dimension)
    : width_(lake_dimension.width()),
      height_(lake_dimension.height()),
      matrix_(matrix_dimension.width(), matrix_dimension.height()) {
}

/*----------------------------------------------------------------------------*/
/*                              CONCRETE METHODS                              */
/*----------------------------------------------------------------------------*/

void Lake::printPGM(std::ostream &os, unsigned int width,
                                      unsigned int height,
                                      double hmax, double pmax) const {
  os << "P3" << std::endl;
  os << width << " " << height << std::endl;

  double delta = (hmax > -pmax) ? hmax/255 : -pmax/255;
  for (unsigned int j = 0; j < matrix_.cols(); j++) {
    for (unsigned int i = 0; i < matrix_.rows(); i++) {
      int h = matrix_(i, j);
      os << "(" << i << "," << j << "): " << std::endl;
      if (h < 0)
        os << h/delta << " 0 0" << std::endl;
      else
        os << "0 0 " << h/delta << std::endl;
    }
  }
}

/*----------------------------------------------------------------------------*/

}  // namespace waves
