//==================================================================================================
//  GlobalTypes.hpp
//
//  Created by Zachary Clawson on 7/19/2015
//  Copyright (c) 2015 Zachary Clawson. All rights reserved.
//==================================================================================================

#ifndef Anytime_Astar_GlobalTypes_hpp
#define Anytime_Astar_GlobalTypes_hpp

#include <Eigen/Dense>

// Double:
using real_t = double;
//using real_t = float;

// Double vector:
//namespace Eigen{

using Vector2real_t   = Eigen::Matrix<real_t, 2, 1>;
using ArrayXreal_t    = Eigen::Array<real_t, Eigen::Dynamic, Eigen::Dynamic>;
using MatrixXreal_t   = Eigen::Matrix<real_t, Eigen::Dynamic, Eigen::Dynamic>;
    
//}

#endif
