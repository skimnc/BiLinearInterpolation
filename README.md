# BiLinearInterpolation
BiLinearInterpolation class written for a rectangular image. Uses Eigen.

## Requirements
* C++11 compiler since the "using" keyword is used in place of a typedef; also smart pointers are used
* Eigen installed and linked to: <http://eigen.tuxfamily.org/>

## Usage
The constructor for the BiLinearInterpolation class requires:

* An Eigen::Array of type <tt>real_t</tt> (which is specified in the config folder)
* Two Eigen::Vector2 of type <tt>real_t</tt> specifying the bounds of the 2D domain (min/max)

After construction, an instantiation of the class can be called as a functor.

## References
* Coded just like on Wikpedia <https://en.wikipedia.org/wiki/Bilinear_interpolation>; only change is the order of which coordinate is interpolated first.