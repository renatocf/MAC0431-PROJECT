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
#include "waves/Dimension.hpp"

namespace waves {

/*----------------------------------------------------------------------------*/
/*                                CONSTRUCTORS                                */
/*----------------------------------------------------------------------------*/

Dimension::Dimension(unsigned int width, unsigned int height)
    : width_(width), height_(height) {
}

/*----------------------------------------------------------------------------*/
/*                              CONCRETE METHODS                              */
/*----------------------------------------------------------------------------*/

unsigned int Dimension::width() const {
  return width_;
}

/*----------------------------------------------------------------------------*/

unsigned int Dimension::height() const {
  return height_;
}

/*----------------------------------------------------------------------------*/
/*                              FRIEND FUNTIONS                               */
/*----------------------------------------------------------------------------*/

std::istream &operator>>(std::istream &input, Dimension& dim) {
  char lpar, rpar, comma;

  input >> lpar;
  input >> dim.width_;
  input >> comma;
  input >> dim.height_;
  input >> rpar;

  return input;
}

/*----------------------------------------------------------------------------*/

}  // namespace waves
