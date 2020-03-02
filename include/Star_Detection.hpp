/*
 *  Created: 02.03.20
 *
 */

#ifndef __STAR_DETECTION_HPP__
#define __STAR_DETECTION_HPP__

#include <iostream>
#include <cstdint>
#include <cerrno>

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"


using namespace std;
using namespace cv;

void encloseWithRectangles (vector <Rect> boundedRects, vector <vector <Point>> contoursPolygon_vec, size_t num,
                            Mat starContour, Scalar color, int thickness, int lineType, int shift);


#endif  //  __STAR_DETECTION_H__
