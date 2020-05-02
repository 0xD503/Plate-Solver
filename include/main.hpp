#ifndef MAIN_HPP_INCLUDED
#define MAIN_HPP_INCLUDED

#include <iostream>
#include <cstdint>
#include <ctime>
#include <cerrno>

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

#include "coor.hpp"
#include "Star.hpp"
#include "Star_Detection.hpp"

#ifdef __DEBUG
#include "Unit_Tests.hpp"
#endif  // __DEBUG


/// General defines
#define ASCII_ESCAPE_KEY 0x1B
#define ASCII_SPACE_KEY 0x20

#define KERNEL_SIZE 3
#define SCALE 1
#define DELTA 0



#endif // MAIN_HPP_INCLUDED
