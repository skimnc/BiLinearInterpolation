//==================================================================================================
//  BiLinearInterpolation.hpp
//
//  Created by Zachary Clawson on 7/19/2015
//  Copyright (c) 2015 Zachary Clawson. All rights reserved.
//==================================================================================================

#ifndef __BiLinearInterpolation_hpp
#define __BiLinearInterpolation_hpp

#include <Eigen/Dense>
#include "config/GlobalTypes.hpp"

//------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------//

/** BiLinearInterpolation
 *  * This implementation follows the way it is written on Wikipedia with the execption that we
 *    reverse the meaning of eta and xi (i.e. on Wikipedia eta <- 1-eta and xi <- 1-xi
 */

class BiLinearInterpolationPrivate;

class BiLinearInterpolation {
public:
	BiLinearInterpolation(
        const ArrayXreal_t & values,
        const Vector2real_t bounds_min,
        const Vector2real_t bounds_max
    );

	~BiLinearInterpolation();
    
    real_t operator()(const Vector2real_t & x) const;
    
private:
    std::unique_ptr<BiLinearInterpolationPrivate> p;
};


//------------------------------------------------------------------------------------------------//



//------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------//

#endif /* BILINEARINTERPOLATION */
