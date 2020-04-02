#ifndef __COOR_HPP_INCLUDED__
#define __COOR_HPP_INCLUDED__

#include <cstdint>


//#define PI  3.1415

namespace coor  {

struct CartCoor    {
    unsigned int x, y;
};
typedef CartCoor CartCoor;

struct ReducedCartCoor    {
    int x_Reduced, y_Reduced;
};
typedef ReducedCartCoor ReducedCartCoor;

struct PolarCoor    {
    double r;
    double phi;
};
typedef PolarCoor PolarCoor;


double radToDeg (double rad);
double degToRad (double deg);

ReducedCartCoor *calculateReducedCoor (CartCoor *coor,\
					    int width, int height);
PolarCoor *calculatePolarCoor (ReducedCartCoor *reducedCoor);

PolarCoor *calculateCoor (CartCoor *coor, int width,\
			  int height);

}


#endif // __COOR_HPP_INCLUDED__
