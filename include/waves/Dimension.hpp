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

#ifndef WAVES_WAVES_DIMENSION_
#define WAVES_WAVES_DIMENSION_

// Standard headers
#include <iostream>

namespace waves {

class Dimension {
 public:
  // Constructors
  explicit Dimension(unsigned int width = 0, unsigned int length = 0);

  // Concrete methods
  unsigned int width() const;
  unsigned int length() const;

  // Friend functions
  friend std::istream &operator>>(std::istream &input, Dimension &dim);

 private:
  // Instance variables
  unsigned int width_, length_;
};

}  // namespace waves

#endif  // WAVES_WAVES_DIMENSION_
