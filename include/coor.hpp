#ifndef __COOR_HPP_INCLUDED__
#define __COOR_HPP_INCLUDED__

#include <cstdint>


struct CartesianCoor    {
    uint16_t x, y;
};
typedef CartesianCoor CartesianCoor;

struct ReducedCartesianCoor    {
    uint16_t x_Reduced, y_Reduced;
};
typedef ReducedCartesianCoor ReducedCartesianCoor;

struct PolarCoor    {
    double r;
    double phi;
};
typedef PolarCoor PolarCoor;


#endif // __COOR_HPP_INCLUDED__
