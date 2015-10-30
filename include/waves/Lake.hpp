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

#ifndef WAVES_WAVES_LAKE_
#define WAVES_WAVES_LAKE_

// Standard headers
#include <atomic>

// External headers
#include <Eigen/Core>

namespace waves {

using Lake = Eigen::Matrix<std::atomic_int, Eigen::Dynamic, Eigen::Dynamic>;

}  // waves

#endif // WAVES_WAVES_LAKE_
