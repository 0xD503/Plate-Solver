#include <iostream>

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"


#define KERNEL_SIZE 3
#define SCALE 1
#define DELTA 0


using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    size_t i;

    int kernelSize = KERNEL_SIZE;
    int scale = SCALE;
    int delta = DELTA;
    int dDepth = CV_16S;
    //const String imageName = "/home/d_503/Programming/CodeBlocks/Plate_Solver/me.jpg";
    const String imageName = "/home/d_503/Programming/CodeBlocks/Plate_Solver/img/stars_1.jpg";
    const String srcWindowName = "orig";
    const String resultWindowName = "Stars";
    const String blurredWindowName = "Blurred stars";
    const String grayscaledWindowName = "Grayscaled stars";
    const String temp1WindowName = "temp1 stars";
    const String temp2WindowName = "temp2 stars";
    const String temp3WindowName = "temp3 stars";
    const String temp4WindowName = "temp4 stars";
    Mat srcImage, blurredImage, grayscaledImage;
    Mat resultImage, resultImage1, resultImage2, resultImage3;
    Mat grad;

    double thresh = 100, maxThreshold = 255;
    const String thresholdWindowName = "Threshold";
    const String contoursWindowName = "Contours";
    vector <vector<Point>> contours;
    vector <Vec4i> hierarchy;
    Mat thresholdOut, contoursOut;


    srcImage = imread(imageName, IMREAD_COLOR);
    if(srcImage.empty())
    {
        cout << "ouch" << endl;
        return -1;
    }

    namedWindow(srcWindowName, WINDOW_FREERATIO);
    imshow(srcWindowName, srcImage);
    waitKey();

    GaussianBlur(srcImage, blurredImage, Size(3,3), 0, 0, BORDER_DEFAULT);

    /*namedWindow(blurredWindowName, WINDOW_FREERATIO);
    //namedWindow(blurredWindowName, WINDOW_AUTOSIZE);
    imshow(blurredWindowName, blurredImage);
    waitKey();*/

    cvtColor(blurredImage, grayscaledImage, COLOR_BGR2GRAY);

    /// FFFFFF
    threshold(grayscaledImage, thresholdOut, thresh, maxThreshold, THRESH_BINARY);
    findContours(thresholdOut, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

    namedWindow(thresholdWindowName, WINDOW_FREERATIO);
    imshow(thresholdWindowName, thresholdOut);
    waitKey();
    /*namedWindow(contoursWindowName, WINDOW_FREERATIO);
    imshow(contoursWindowName, contoursOut);
    waitKey();*/
    vector <vector<Point>> vec_Contours_Polygon;
    vector <Rect> boundingRect(contours.size());
    vector <Point2f> center(contours.size());
    vector <float> radius(contours.size());

    /*or (i = 0; i < contours.size(); i++)
    {
        cout << "hey" << endl;
        approxPolyDP(Mat(contours[i]), vec_Contours_Polygon[i], 3, true);
        cout << "hohohohohoh" << endl;
    }*/

    ///
    Mat grad_x, grad_y;

    Sobel(grayscaledImage, grad_x, dDepth, 1, 0, kernelSize, scale, delta, BORDER_DEFAULT);
    Sobel(grayscaledImage, grad_y, dDepth, 0, 1, kernelSize, scale, delta, BORDER_DEFAULT);

    Mat grad_x_abs, grad_y_abs;

    convertScaleAbs(grad_x, grad_x_abs);
    convertScaleAbs(grad_y, grad_y_abs);

    namedWindow(temp3WindowName, WINDOW_FREERATIO);
    imshow(temp3WindowName, grad_x_abs);
    waitKey();
    namedWindow(temp4WindowName, WINDOW_FREERATIO);
    imshow(temp4WindowName, grad_y_abs);
    waitKey();

    addWeighted(grad_x_abs, 0.5, grad_y_abs, 0.5, 0, resultImage);
    /*addWeighted(grad_x_abs, 0.5, grad_y_abs, 0.5, 10, resultImage1);
    addWeighted(grad_x_abs, 0.5, grad_y_abs, 0.5, 20, resultImage2);
    addWeighted(grad_x_abs, 0.5, grad_y_abs, 0.5, 100, resultImage3);*/

    namedWindow(resultWindowName, WINDOW_FREERATIO);
    imshow(resultWindowName, resultImage);
    waitKey();

    /*namedWindow(temp1WindowName, WINDOW_FREERATIO);
    imshow(temp1WindowName, resultImage1);
    waitKey();

    namedWindow(temp2WindowName, WINDOW_FREERATIO);
    imshow(temp2WindowName, resultImage2);
    waitKey();

    namedWindow(temp3WindowName, WINDOW_FREERATIO);
    imshow(temp3WindowName, resultImage3);
    waitKey();*/

    waitKey();


    return 0;
}



