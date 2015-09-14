//==================================================================================================
//  BiLinearInterpolation.cpp
//
//  Created by Zachary Clawson on 7/19/2015
//  Copyright (c) 2015 Zachary Clawson. All rights reserved.
//==================================================================================================

// Local:

#include "BiLinearInterpolation.hpp"

//------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------//

/**  BiLinearInterpolation::interpolate()
  *  - interpolates on the square with lower left corner (x1,y1) = x_SW_phys and
  *    upper right corner (x2,y2) = x_SW_phs + (hx,hy)
  */

class BiLinearInterpolationPrivate {
public:
	//- c-tor ------------------------------------------------------------------------------------//
	BiLinearInterpolationPrivate(
		const ArrayXreal_t & values,
		const Vector2real_t bounds_min,
		const Vector2real_t bounds_max
	) : values_(values),
		bounds_min_(bounds_min),
		bounds_max_(bounds_max),
		grid_size_( (Eigen::Vector2i){values.rows(), values.cols()} )
	{
		grid_spacing_[0] = (bounds_max_[0] - bounds_min_[0]) / (grid_size_[0] - 1);
		grid_spacing_[1] = (bounds_max_[1] - bounds_min_[1]) / (grid_size_[1] - 1);
	}

	//- functions --------------------------------------------------------------------------------//
    bool in_domain_physical(
		const Vector2real_t & pos
    ) const;

    real_t interpolate_two_numbers(
    	const real_t val1,
    	const real_t val2,
    	const real_t lambda
    ) const;

	//- variables --------------------------------------------------------------------------------//;
    const ArrayXreal_t & values_;

    const Vector2real_t bounds_min_;
    const Vector2real_t bounds_max_;

    Vector2real_t grid_spacing_;
    const Eigen::Vector2i grid_size_;

	//- constants --------------------------------------------------------------------------------//
    const real_t value_infinite_ = std::numeric_limits<real_t>::max();
};

//------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------//

BiLinearInterpolation::BiLinearInterpolation(
	const ArrayXreal_t & values,
	const Vector2real_t bounds_min,
	const Vector2real_t bounds_max
) {
	p.reset( new BiLinearInterpolationPrivate(values, bounds_min, bounds_max) );
}

BiLinearInterpolation::~BiLinearInterpolation() { }

//------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------//

real_t
BiLinearInterpolation::operator()(const Vector2real_t & x) const {
    if ( ! p->in_domain_physical(x) ) return p->value_infinite_;

    Eigen::Vector2i x_SW;
    Vector2real_t x_SW_phys;
    real_t eta, xi;

    // Calculate the lower-left corner index of the cell that x lives in:
    for (unsigned short int i = 0; i < 2; ++i) {
    	x_SW[i] = std::min((int)std::floor( (x[i] - p->bounds_min_[i]) / p->grid_spacing_[i] ), p->grid_size_[i]-2);
    	x_SW_phys[i] = p->bounds_min_[i] + x_SW[i] * p->grid_spacing_[i];
    }

    eta = (x[0] - x_SW_phys[0]) / p->grid_spacing_[0];
    xi  = (x[1] - x_SW_phys[1]) / p->grid_spacing_[1];

    // Make sure in [0,1]:
    if (eta < 0) eta = 0;
    if (eta > 1) eta = 1;
    if (xi < 0)  xi  = 0;
    if (xi > 1)  xi  = 1;

    // Interpolate along y=y1 and y=y2 axes
    real_t val_x_y1 = (1-eta) * p->values_(x_SW[0], x_SW[1])   + eta * p->values_(x_SW[0]+1, x_SW[1]);
    real_t val_x_y2 = (1-eta) * p->values_(x_SW[0], x_SW[1]+1) + eta * p->values_(x_SW[0]+1, x_SW[1]+1);

    return p->interpolate_two_numbers(val_x_y1, val_x_y2, xi);
//    return common::lin_interp(val_x_y1, val_x_y2, xi);
//    return (1-xi) * val_x_y1 + xi * val_x_y2;
}


//------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------//

//----------------------------------- Private functions ------------------------------------------//

bool BiLinearInterpolationPrivate::in_domain_physical(
	const Vector2real_t & pos
) const {
    return pos[0] >= bounds_min_[0] && pos[0] <= bounds_max_[0] &&
           pos[1] >= bounds_min_[1] && pos[1] <= bounds_max_[1];
}

real_t
BiLinearInterpolationPrivate::interpolate_two_numbers(
	const real_t val1,
	const real_t val2,
	const real_t lambda
) const {
	if (lambda < 0 || lambda > 1)
		throw std::runtime_error("Interpolation requested for lambda \\not\\in [0,1].");

//	testing::test_function();

	return (1-lambda) * val1 + lambda * val2;
}

//------------------------------------------------------------------------------------------------//

