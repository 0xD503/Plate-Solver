/*
 *  Created: 02.03.20
 *
 */

#include "../include/Star_Detection.hpp"


using namespace std;
using namespace cv;

void encloseWithCircles (vector <vector <Point>> contoursPolygon_vec, vector <Point2f> centers, vector <float> radiuses,
                         size_t num, Mat starContours_mat, Scalar color, int thickness, int lineType, int shift)
{
    size_t i;

    for (i = 0; i < num; i++)
    {
        minEnclosingCircle(Mat(contoursPolygon_vec[i]), centers[i], radiuses[i]);
        circle(starContours_mat, centers[i], radiuses[i], color, thickness, lineType, shift);
    }
}

void encloseWithRectangles (vector <Rect> boundedRects, vector <vector <Point>> contoursPolygon_vec, size_t num,
                            Mat starContours_mat, Scalar color, int thickness, int lineType, int shift)
{
    size_t i;

    for (i = 0; i < num; i++)
    {
        boundedRects[i] = boundingRect(Mat(contoursPolygon_vec[i]));
        rectangle(starContours_mat, boundedRects[i].tl(), boundedRects[i].br(), color, thickness, lineType, shift);
    }
}

/*void findContours (vector <Poin> contour, vector <Point> contourPolygon,)
{
    inline approxPolyDP(, , , );
}*/


/*void detectStars ()
{

}*/
