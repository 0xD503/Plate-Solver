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
        minEnclosingCircle((Mat) vec_Contours_Polygon[i], center[i], radius[i]);
    }

    Mat starContours = Mat::zeros(thresholdOut.size(), CV_8UC3);
    RNG rng;
    for (i = 0; i < contours.size(); i++)
    {
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        drawContours(starContours, vec_Contours_Polygon, i, color, 1, 8, vector<Vec4i>(), 0, Point());
        circle(starContours, center[i], radius[i], color, 2, 8, 0);
    }*/

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


void detectStars ()
{

}
