#include "Star.hpp"


using namespace std;

/// Objects counter initialization
unsigned int Star::Counter {};

/// Default constructor
Star::Star() : cartesCoor({}), reducedCartesCoor({}), polarCoor({})
{
    Counter++;
}

/// Initialize using Cartesian coordinate
Star::Star(CartesianCoor coor) : cartesCoor(coor), reducedCartesCoor({}), polarCoor({})
{
    Counter++;
}

/// Default destructor
Star::~Star()
{
    //dtor
}

/// Assignment operator
Star& Star::operator=(const Star& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
