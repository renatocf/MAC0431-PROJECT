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
#include <memory>
#include <sstream>

// External headers
#include "gmock/gmock.h"

// Waves templates
#include "waves/Dimension.tcc"

class ADimension : public testing::Test {
 public:
  std::stringstream stream;

  ADimension() : stream("(1,2)") {
  }
};

TEST_F(ADimension, ShouldReadFromStream) {
  waves::Dimension<2> dimension2;
  stream >> dimension2;

  ASSERT_EQ(dimension2[0], 1u);
  ASSERT_EQ(dimension2[1], 2u);
}
