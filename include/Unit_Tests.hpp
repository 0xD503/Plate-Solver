#ifndef __UNIT_TESTS_H_INCLUDED__
#define __UNIT_TESTS_H_INCLUDED__

#include <iostream>
#include <cstdint>
#include <cerrno>

#include "coor.hpp"
#include "Star.hpp"
#include "Star_Detection.hpp"


using namespace std;

int testCoor (unsigned int x_1, unsigned int y_1, int xr_1, int yr_1,
              double r_1, double phi_1);


#endif // __UNIT_TESTS_H_INCLUDED__
