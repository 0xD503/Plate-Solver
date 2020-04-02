/*
 *  Created: 02.03.20
 *
 */

#include "../include/Star_Detection.hpp"


using namespace std;

void encloseWithCircles (vector <vector <cv::Point>> contoursPolygon_vec,\
			 vector <cv::Point2f> centers,\
			 vector <float> radiuses,\
                         size_t num, cv::Mat starContours_mat,\
			 cv::Scalar color, int thickness,\
			 int lineType, int shift)
{
    size_t i;

    for (i = 0; i < num; i++)
    {
        cv::minEnclosingCircle(cv::Mat(contoursPolygon_vec[i]),\
			       centers[i], radiuses[i]);
        cv::circle(starContours_mat, centers[i], radiuses[i],\
		   color, thickness, lineType, shift);
    }
}

void encloseWithRectangles (vector <cv::Rect> boundedRects,\
			    vector <vector <cv::Point>> contoursPolygon_vec,\
			    size_t num,
                            cv::Mat starContours_mat,\
			    cv::Scalar color, int thickness,\
			    int lineType, int shift)
{
    size_t i;

    for (i = 0; i < num; i++)
    {
        boundedRects[i] = cv::boundingRect(cv::Mat(contoursPolygon_vec[i]));
        cv::rectangle(starContours_mat, boundedRects[i].tl(),\
		      boundedRects[i].br(), color, thickness,\
		      lineType, shift);
    }
}

/*void findContours (vector <Poin> contour, vector <Point> contourPolygon,)
{
    inline approxPolyDP(, , , );
}*/


/*void detectStars ()
{

}*/
