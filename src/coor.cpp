#include "../include/coor.hpp"
#include <cmath>
//#include <bits/stdc++.h>


using namespace std;

namespace coor  {

double radToDeg (double rad)
{
    return (rad * 180.0 / M_PI);
}

double degToRad (double deg)
{
    return (deg * M_PI / 180.0);
}

ReducedCartCoor *calculateReducedCoor (CartCoor *coor,\
				       int width, int height)
{
    ReducedCartCoor *reducedCoor = new ReducedCartCoor;

    reducedCoor->x_Reduced = coor->x - (width / 2);
    reducedCoor->y_Reduced = (coor->y - (height / 2)) * (-1);

    return (reducedCoor);
}

PolarCoor *calculatePolarCoor (ReducedCartCoor *reducedCoor)
{
    PolarCoor *polarCoor = new PolarCoor;

    double sum = (pow(static_cast<double>(reducedCoor->x_Reduced), 2.0) +\
                  pow(static_cast<double>(reducedCoor->y_Reduced), 2.0));
    polarCoor->r = sqrt(sum);
    polarCoor->phi = atan2(static_cast<double>(reducedCoor->y_Reduced),\
			   static_cast<double>(reducedCoor->x_Reduced));

    return (polarCoor);
}


PolarCoor *calculateCoor (CartCoor *coor, int width, int height)
{
    return (calculatePolarCoor(calculateReducedCoor(coor, width,\
						    height)));
}

}
