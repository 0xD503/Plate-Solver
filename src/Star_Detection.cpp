/*
 *  Created: 02.03.20
 *
 */

#include "../include/Star_Detection.hpp"


using namespace std;
using namespace cv;

void encloseWithRectangles (vector <Rect> boundedRects, vector <vector <Point>> contoursPolygon_vec, size_t num,
                            Mat starContour, Scalar color, int thickness, int lineType, int shift)
{

    for (size_t i = 0; i < num; i++)
    {
        boundedRects[i] = boundingRect(Mat(contoursPolygon_vec[i]));
        rectangle(starContour, boundedRects[i].tl(), boundedRects[i].br(), color, thickness, lineType, shift);
    }
}

/*void findContours (vector <Poin> contour, vector <Point> contourPolygon,)
{
    inline approxPolyDP(, , , );
}*/


/*void detectStars ()
{

}*/
