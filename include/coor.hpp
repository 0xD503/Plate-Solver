#ifndef __COOR_HPP_INCLUDED__
#define __COOR_HPP_INCLUDED__

#include <cstdint>


//#define PI  3.1415


struct CartesianCoor    {
    unsigned int x, y;
};
typedef CartesianCoor CartesianCoor;

struct ReducedCartesianCoor    {
    int x_Reduced, y_Reduced;
};
typedef ReducedCartesianCoor ReducedCartesianCoor;

struct PolarCoor    {
    double r;
    double phi;
};
typedef PolarCoor PolarCoor;


ReducedCartesianCoor *calculateReducedCoor (CartesianCoor *coor, int width, int height);
PolarCoor *calculatePolarCoor (ReducedCartesianCoor *reducedCoor);


#endif // __COOR_HPP_INCLUDED__
