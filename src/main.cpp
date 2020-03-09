#include "../include/main.hpp"


using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    #ifdef TESTING
    int testResult;

    testResult = testCoor(180, 140, 43, -4, 25.0, 300.0);
    if (testResult == 0)    cout << "Test finished with status \"SUCCESS\"" << endl;

    //system("WAIT");
    //system("pause");
    #endif // TESTING

    size_t i;

    int kernelSize = KERNEL_SIZE;
    int scale = SCALE;
    int delta = DELTA;
    int dDepth = CV_16S;
    const string imageName = argv[1];
    const String srcWindowName = "orig";
    const String resultWindowName = "Stars";
    const String blurredWindowName = "Blurred stars";
    const String grayscaledWindowName = "Grayscaled stars";
    const String boundedWindowName = "Bounded stars";
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
    Size matrixSize;


    srcImage = imread(imageName, IMREAD_COLOR);
    if(srcImage.empty())
    {
        cout << "An error occured while open image file: " << strerror(errno) << endl;
        return -1;
    }

    /// Get matrix size
    matrixSize = srcImage.size();

    namedWindow(srcWindowName, WINDOW_FREERATIO);
    imshow(srcWindowName, srcImage);
    waitKey();

    GaussianBlur(srcImage, blurredImage, Size(3,3), 0, 0, BORDER_DEFAULT);

//    namedWindow(blurredWindowName, WINDOW_FREERATIO);
//    //namedWindow(blurredWindowName, WINDOW_AUTOSIZE);
//    imshow(blurredWindowName, blurredImage);
//    waitKey();

    cvtColor(blurredImage, grayscaledImage, COLOR_BGR2GRAY);

    /// FFFFFF
    threshold(grayscaledImage, thresholdOut, thresh, maxThreshold, THRESH_BINARY);
    findContours(thresholdOut, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

    namedWindow(thresholdWindowName, WINDOW_FREERATIO);
    imshow(thresholdWindowName, thresholdOut);
    waitKey();
//    namedWindow(contoursWindowName, WINDOW_FREERATIO);
//    imshow(contoursWindowName, contoursOut);
//    waitKey();
    vector <vector<Point>> vec_Contours_Polygon(contours.size());
    vector <Rect> boundedRect(contours.size());
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
        //rectangle(starContours, boundedRect[i].tl(), boundedRect[i].br(), color, 2, 8, 0);
        circle(starContours, center[i], radius[i], color, 2, 8, 0);
    }

    namedWindow(boundedWindowName, WINDOW_FREERATIO);
    imshow(boundedWindowName, starContours);
    waitKey();

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

//    addWeighted(grad_x_abs, 0.5, grad_y_abs, 0.5, 0, resultImage);
//    addWeighted(grad_x_abs, 0.5, grad_y_abs, 0.5, 10, resultImage1);
//    addWeighted(grad_x_abs, 0.5, grad_y_abs, 0.5, 20, resultImage2);
//    addWeighted(grad_x_abs, 0.5, grad_y_abs, 0.5, 100, resultImage3);
//
//    namedWindow(resultWindowName, WINDOW_FREERATIO);
//    imshow(resultWindowName, resultImage);
//    waitKey();

//    namedWindow(temp1WindowName, WINDOW_FREERATIO);
//    imshow(temp1WindowName, resultImage1);
//    waitKey();
//
//    namedWindow(temp2WindowName, WINDOW_FREERATIO);
//    imshow(temp2WindowName, resultImage2);
//    waitKey();
//
//    namedWindow(temp3WindowName, WINDOW_FREERATIO);
//    imshow(temp3WindowName, resultImage3);
//    waitKey();

    waitKey();


    return 0;
}
