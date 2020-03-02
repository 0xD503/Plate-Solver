/*
 *  Created: 02.03.20
 *
 */

#include "../include/Star_Detection.hpp"


using namespace std;
using namespace cv;

/*void findContours (vector <Poin> contour, vector <Point> contourPolygon,)
{
    inline approxPolyDP(, , , );
}*/
/*vector <vector <Point>> vec_Contours_Polygon(contours.size());
    vector <Rect> boundedRects(contours.size());
    vector <Point2f> center(contours.size());
    vector <float> radius(contours.size());

    for (i = 0; i < contours.size(); i++)
    {
        approxPolyDP(Mat(contours[i]), vec_Contours_Polygon[i], 3, true);
        boundedRect[i] = boundingRect(Mat(vec_Contours_Polygon[i]));
        minEnclosingCircle((Mat) vec_Contours_Polygon[i], center[i], radius[i]);
    }

    Mat starContours = Mat::zeros(thresholdOut.size(), CV_8UC3);
    RNG rng;
    for (i = 0; i < contours.size(); i++)
    {
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        drawContours(starContours, vec_Contours_Polygon, i, color, 1, 8, vector<Vec4i>(), 0, Point());
        rectangle(starContours, boundedRect[i].tl(), boundedRect[i].br(), color, 2, 8, 0);
        circle(starContours, center[i], radius[i], color, 2, 8, 0);
    }*/

void encloseWithRectangles (vector <Rect> boundedRects, vector <vector <Point>> contoursPolygon_vec, size_t num,
                            Mat starContour, Scalar color, int thickness, int lineType, int shift)
{

    for (size_t i = 0; i < num; i++)
    {
        boundedRects[i] = boundingRect(Mat(contoursPolygon_vec[i]));
        rectangle(starContour, boundedRects[i].tl(), boundedRects[i].br(), color, thickness, lineType, shift);
    }
}


void detectStars ()
{

}
