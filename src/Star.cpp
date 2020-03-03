#include "Star.hpp"


using namespace std;

unsigned int Star::Counter {};

Star::Star() : cartesCoor({0}), reducedCartesCoor({0}), polarCoor({0})
{
    this->Counter++;
}

/// Initialize using Cartesian coordinate
Star::Star(CartesianCoor coor) : cartesCoor(coor)
{
    reducedCartesCoor = {};
    polarCoor = {};
    this->Counter++;
}

/*///
Star::Star(uint16_t x, uint16_t y) : cartesCoor({x, y})
{
    this->Counter++;
}*/

Star::~Star()
{
    //dtor
}

Star& Star::operator=(const Star& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
