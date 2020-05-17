#include "../include/main.hpp"


//#define TESTING
//#define TIME_TEST
//#define CANNY_TEST


void greeting (void);

#ifdef CANNY_TEST
cv::Mat csrc, cdst, cresult;
int clowt = 0;
const int clowmax = 1000;
int ratioCanny = 1;
const string cthrwin = "Canny_TESTING";


static void cannyDetector (int, void *);
static void cannyDetector (int, void *)
{
    cv::Mat result;

    cv::Canny(csrc, cdst, clowt, clowt * ratioCanny);
    result = cv::Scalar::all(0);
    csrc.copyTo(result, cdst);
    cv::imshow(cthrwin, result);
}
#endif // CANNY_TEST

using namespace std;

int main(int argc, char *argv[])
{
    greeting();
    #ifdef TESTING
    int testResult;

    testResult = testCoor(180, 140, 43, -4, 25.0, 300.0);
    if (testResult == 0)  cout << "Test finished with\
                                       status: "
				    << testResult << endl;

    return (testResult);
    #endif // TESTING

    size_t i;

    int kernelSize = KERNEL_SIZE;
    int scale = SCALE;
    int delta = DELTA;
    int dDepth = CV_16S;
    const string imageName = argv[1];
    const string srcWindowName = "orig";
    const string resultWindowName = "Stars";
    const string blurredWindowName = "Blurred_stars";
    const string grayscaledWindowName = "Grayscaled_stars";
    const string boundedWindowName = "Bounded_stars";

    const string cannyOutWindow = "Canny";
    const string cannyThresholdWindow = "Canny_threshold";
    const string cannyContoursWindow = "Canny_contours";

    //const string temp1WindowName = "temp1_stars";
    //const string temp2WindowName = "temp2_stars";
    cv::Mat srcImage, blurredImage, grayscaledImage;
    cv::Mat resultImage, resultImage1, resultImage2, resultImage3;
    cv::Mat grad;

    /// Drawing vars
    double thresh = 100, maxThreshold = 255;
    const string thresholdWindowName = "Threshold";
    const string thresholdContours = "Threshold_contours";
    cv::Mat thresholdOut;
    cv::Mat thresholdSobelOut;
    cv::Mat thresholdLaplaceOut;
    cv::Mat thresholdCannyOut;
    cv::Size matrixSize;
    vector <vector<cv::Point>> contours, sobelContours, laplaceContours, cannyContours;
    vector <cv::Vec4i> hierarchy, hierarchySobel, hierarchyLaplace, hierarchyCanny;

    /// Output files
    string coor_output_fn = std::string(argv[2]) + "/coor.csv";
    ofstream coor_output;

    /// Read image file
    srcImage = cv::imread(imageName, cv::IMREAD_COLOR);
    if(srcImage.empty())
    {
        cout << "An error occurred while open image file <" <<\
        imageName << ">: " << strerror(errno) << endl;
        return (-1);
    }

    /// Convert image to gray scaled color
    cv::cvtColor(srcImage, grayscaledImage,\
		         cv::COLOR_BGR2GRAY);

    /// Blur image to decrease noise
    cv::GaussianBlur(grayscaledImage, blurredImage, cv::Size(3,3),\
		     0, 0, cv::BORDER_DEFAULT);



    /// Threshold function transforms image to bi-color image
    /// (only white and black, without shades). It helps us to
    /// determine the clear-cut bounds of the objects on image

#ifdef TIME_TEST
    unsigned int j, cyclesNum = 50;
    double elapsedtime;
    timespec startTime, endTime;
    string time_output_fn = std::string(argv[2]) + "/time.csv";
    ofstream time_output;

    time_output.open(time_output_fn, ios::out | ios::trunc);
    time_output << "Threshold,Sobel,Laplace,Canny" << endl;
#endif // TIME_TEST
    size_t contoursNum;
    cv::RNG rng;

#ifdef TIME_TEST
    for (j = 0; j < cyclesNum; j++)
    {
        /// Start timer
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &startTime);
#endif // TIME_TEST
    cv::threshold(blurredImage, thresholdOut, thresh, maxThreshold,\
                  cv::THRESH_BINARY);
    cv::findContours(thresholdOut, contours, hierarchy,\
		     cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE,\
		     cv::Point(0, 0));

    contoursNum = contours.size();
    vector <vector <cv::Point>> approxCont_Raw(contoursNum);
    vector <cv::Point2f> center(contoursNum);
    vector <float> radius(contoursNum);

    cv::Mat thresholdContours_zeroed = cv::Mat::zeros(thresholdOut.size(), CV_8UC3);
    for (i = 0; i < contoursNum; i++)
    {
        cv::Scalar color = cv::Scalar(rng.uniform(0, 255),\
                                      rng.uniform(0, 255),\
				                      rng.uniform(0, 255));

        /// Approximate contours
        cv::approxPolyDP(cv::Mat(contours[i]), approxCont_Raw[i], 3, true);
        /*/// Draw star contours
        cv::drawContours(thresholdContours_zeroed, approxCont_Raw, i,\
			             color, 1, cv::LINE_8, vector<cv::Vec4i>(),\
			             0, cv::Point());*/

        /// Find minimal enclosing circles for approximated contours
        cv::minEnclosingCircle((cv::Mat) approxCont_Raw[i],\
			     center[i], radius[i]);
        /// Draw minimal enclosing circles
        cv::circle(thresholdContours_zeroed, center[i], radius[i], color,\
		   2, cv::LINE_8, 0);
    }

#ifdef TIME_TEST
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &endTime);
        elapsedtime = (endTime.tv_sec - startTime.tv_sec) +\
                      ((endTime.tv_nsec - startTime.tv_nsec) / 1e9);
        cout << "Threshold: overall time - " << elapsedtime << " seconds" << endl;
        time_output << elapsedtime << ",";
#endif // TIME_TEST



    /// Apply Sobel operator to gray-scaled image
    cv::Mat sobelResult;
    cv::Mat grad_x, grad_y;
    cv::Mat grad_x_abs, grad_y_abs;

#ifdef TIME_TEST
        /// Start time
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &startTime);
#endif // TIME_TEST

    /// Find horizontal gradient
    cv::Sobel(blurredImage, grad_x, dDepth, 1, 0, kernelSize,	\
	  scale, delta, cv::BORDER_DEFAULT);
    /// Find vertical gradient
    cv::Sobel(blurredImage, grad_y, dDepth, 0, 1, kernelSize,	\
	  scale, delta, cv::BORDER_DEFAULT);

    cv::convertScaleAbs(grad_x, grad_x_abs);
    cv::convertScaleAbs(grad_y, grad_y_abs);

    cv::addWeighted(grad_x_abs, 0.5, grad_y_abs, 0.5, 0,	\
		sobelResult);
/*    addWeighted(grad_x_abs, 0.5, grad_y_abs, 0.5, 10,	\
		resultImage1);
//    addWeighted(grad_x_abs, 0.5, grad_y_abs, 0.5, 20,	\
		resultImage2);
//    addWeighted(grad_x_abs, 0.5, grad_y_abs, 0.5, 100,	\
		resultImage3);*/

    /// Draw for Sobel image
    cv::threshold(sobelResult, thresholdSobelOut, thresh, maxThreshold,\
                  cv::THRESH_BINARY);
    cv::findContours(thresholdSobelOut, sobelContours, hierarchySobel,\
                     cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE,\
                     cv::Point(0, 0));

    contoursNum = sobelContours.size();
    vector <vector <cv::Point>> approxCont_Sobel(contoursNum);
    vector <cv::Point2f> sobelCenter(contoursNum);
    vector <float> sobelRadius(contoursNum);
    cv::Mat contoursSobelImage_zeroed = cv::Mat::zeros(thresholdSobelOut.size(), CV_8UC3);
    //cv::Mat contoursSobelImage = grayscaledImage;

    for (i = 0; i < contoursNum; i++)
    {
        cv::Scalar color = cv::Scalar(rng.uniform(0, 255),\
                                      rng.uniform(0, 255),\
                                      rng.uniform(0, 255));

        /// Approximate contours
        cv::approxPolyDP(cv::Mat(sobelContours[i]), approxCont_Sobel[i], 3, true);
        /*cv::drawContours(contoursSobelImage_zeroed, approxCont_Sobel, i,\
                         color, 1, cv::LINE_8, vector <cv::Vec4i>(),\
                         0, cv::Point());*/

        /// Find minimal enclosing circles for approximated contours
        cv::minEnclosingCircle((cv::Mat) approxCont_Sobel[i], sobelCenter[i], sobelRadius[i]);
        /// Draw min encl circle
        cv::circle(contoursSobelImage_zeroed, sobelCenter[i], sobelRadius[i], color,\
                   2, cv::LINE_8, 0);
    }

#ifdef TIME_TEST
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &endTime);
        elapsedtime = (endTime.tv_sec - startTime.tv_sec) +\
                      ((endTime.tv_nsec - startTime.tv_nsec) / 1e9);
        cout << "Sobel operator: overall time - " << elapsedtime << " seconds" << endl;
        time_output << elapsedtime << ",";
#endif // TIME_TEST



    /// Apply Laplace operator
    cv::Mat laplaceResult, laplaceResult_abs;

#ifdef TIME_TEST
        /// Start time
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &startTime);
#endif // TIME_TEST

    cv::Laplacian(blurredImage, laplaceResult, dDepth, kernelSize, scale, delta, cv::BORDER_DEFAULT);
    cv::convertScaleAbs(laplaceResult, laplaceResult_abs, 1, 0);

    /// Draw Laplace boundaries
    cv::threshold(laplaceResult_abs, thresholdLaplaceOut, thresh, maxThreshold,\
                  cv::THRESH_BINARY);
    cv::findContours(thresholdLaplaceOut, laplaceContours, hierarchyLaplace,\
                     cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE,\
                     cv::Point());

    contoursNum = laplaceContours.size();
    vector <vector <cv::Point>> approxCont_Laplace(contoursNum);
    vector <cv::Point2f> laplaceCenter(contoursNum);
    vector <float> laplaceRadius(contoursNum);
    cv::Mat contoursLaplaceImage_zeroed = cv::Mat::zeros(thresholdLaplaceOut.size(), CV_8UC3);
    //cv::Mat contoursLaplaceImage = grayscaledImage;

    for (i = 0; i < contoursNum; i++)
    {
        cv::Scalar color = cv::Scalar(rng.uniform(0, 255),
                                      rng.uniform(0, 255),
                                      rng.uniform(0, 255));

        cv::approxPolyDP(cv::Mat(laplaceContours[i]), approxCont_Laplace[i], 3, true);
        /*//cv::drawContours(contoursLaplaceImage_zeroed, approxCont_Laplace, i,\
          //               color, 1, cv::LINE_8, vector <cv::Vec4i>(),\
            //             0, cv::Point());*/

        cv::minEnclosingCircle((cv::Mat) approxCont_Laplace[i], laplaceCenter[i], laplaceRadius[i]);
        cv::circle(contoursLaplaceImage_zeroed, laplaceCenter[i], laplaceRadius[i], color,\
                   2, cv::LINE_8, 0);
    }

#ifdef TIME_TEST
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &endTime);
        elapsedtime = (endTime.tv_sec - startTime.tv_sec) +\
                   ((endTime.tv_nsec - startTime.tv_nsec) / 1e9);
        cout << "Laplace operator: overall time - " << elapsedtime << " seconds" << endl;
        time_output << elapsedtime << ",";
#endif // TIME_TEST



    /// Apply Canny edge detector
    cv::Mat cannyResult;

#ifdef TIME_TEST
        /// Start time
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &startTime);
#endif // TIME_TEST

#ifdef CANNY_TEST
    cdst.create(srcImage.size(), srcImage.type());
    blurredImage.copyTo(csrc);
    cv::namedWindow(cthrwin, cv::WINDOW_FREERATIO);
    cv::createTrackbar("Min Threshold:", cthrwin, &clowt, clowmax, cannyDetector);
    cv::createTrackbar("Ratio:", cthrwin, &ratioCanny, 10, cannyDetector);
#endif // CANNY_TEST
    int t1 = 178, t2 = 534;
    cv::Canny(blurredImage, cannyResult, t1, t2, kernelSize);

    /// Draw Canny boundaries
    cv::threshold(cannyResult, thresholdCannyOut, thresh, maxThreshold,\
                  cv::THRESH_BINARY);
    cv::findContours(thresholdCannyOut, cannyContours, hierarchyCanny,\
                     cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE,\
                     cv::Point());

    contoursNum = cannyContours.size();
    vector <vector <cv::Point>> approxCont_Canny(contoursNum);
    vector <cv::Point2f> cannyCenter(contoursNum);
    vector <float> cannyRadius(contoursNum);
    cv::Mat contoursCannyImage_zeroed = cv::Mat::zeros(thresholdCannyOut.size(), CV_8UC3);
    //cv::Mat contoursCannyImage = grayscaledImage;

    coor_output.open(coor_output_fn, ios::out | ios::trunc);
    for (i = 0; i < contoursNum; i++)
    {
        cv::Scalar color = cv::Scalar(rng.uniform(0, 255),
                                      rng.uniform(50, 255),
                                      rng.uniform(0, 0));

        cv::approxPolyDP(cv::Mat(cannyContours[i]), approxCont_Canny[i], 3, true);

        cv::minEnclosingCircle((cv::Mat) approxCont_Canny[i], cannyCenter[i], cannyRadius[i]);
        cv::circle(contoursCannyImage_zeroed, cannyCenter[i], cannyRadius[i], color,
                   2, cv::LINE_8, 0);
        /// Write coors in file
        coor_output << cannyCenter[i] << endl;
    }
    coor_output.close();

#ifdef TIME_TEST
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &endTime);
        elapsedtime = (endTime.tv_sec - startTime.tv_sec) +\
                   ((endTime.tv_nsec - startTime.tv_nsec) / 1e9);
        cout << "Canny edge detector: overall time - " << elapsedtime << " seconds" << endl;
        time_output << elapsedtime << endl;
    }

    time_output.close();
#endif // TIME_TEST


    /// Show images
    cv::namedWindow(srcWindowName, cv::WINDOW_FREERATIO);
    //cv::namedWindow(grayscaledWindowName, cv::WINDOW_FREERATIO);
    //cv::namedWindow(blurredWindowName, cv::WINDOW_FREERATIO);
    cv::imshow(srcWindowName, srcImage);
    //cv::imshow(grayscaledWindowName, grayscaledImage);
    //cv::imshow(blurredWindowName, blurredImage);
    /*while ((cv::waitKey() & 0xFF) != ASCII_SPACE_KEY);
    /// Show images
    cv::namedWindow(thresholdWindowName, cv::WINDOW_FREERATIO);
    cv::namedWindow(boundedWindowName, cv::WINDOW_FREERATIO);
    cv::imshow(thresholdWindowName, thresholdOut);
    cv::imshow(boundedWindowName, thresholdContours_zeroed);*/
    while ((cv::waitKey() & 0xFF) != ASCII_SPACE_KEY);
    /// Show image
    cv::namedWindow("Sobel", cv::WINDOW_FREERATIO);
    cv::namedWindow("Sobel_threshold", cv::WINDOW_FREERATIO);
    cv::namedWindow("Sobel_contours", cv::WINDOW_FREERATIO);
    cv::imshow("Sobel", sobelResult);
    cv::imshow("Sobel_threshold", thresholdSobelOut);
    cv::imshow("Sobel_contours", contoursSobelImage_zeroed);
    while ((cv::waitKey() & 0xFF) != ASCII_SPACE_KEY);
    /// Show image
    cv::namedWindow("Laplacian", cv::WINDOW_FREERATIO);
    cv::namedWindow("Laplace_threshold", cv::WINDOW_FREERATIO);
    cv::namedWindow("Laplace_contours", cv::WINDOW_FREERATIO);
    cv::imshow("Laplacian", laplaceResult_abs);
    cv::imshow("Laplace_threshold", thresholdLaplaceOut);
    cv::imshow("Laplace_contours", contoursLaplaceImage_zeroed);
    while ((cv::waitKey() & 0xFF) != ASCII_SPACE_KEY);
    /// Show images
    cv::namedWindow(cannyOutWindow, cv::WINDOW_FREERATIO);
    cv::namedWindow(cannyThresholdWindow, cv::WINDOW_FREERATIO);
    cv::namedWindow(cannyContoursWindow, cv::WINDOW_FREERATIO);
    cv::imshow(cannyOutWindow, cannyResult);
    cv::imshow(cannyThresholdWindow, thresholdCannyOut);
    cv::imshow(cannyContoursWindow, contoursCannyImage_zeroed);
    while ((cv::waitKey() & 0xFF) != ASCII_SPACE_KEY);


    /// Wait for ESC key
    while ((cv::waitKey() & 0xFF) != ASCII_ESCAPE_KEY);
    cv::destroyAllWindows();


    return (0);
}


void greeting (void)
{
    cout << "argv[1] - path to image" << endl;
    cout << "argv[2] - path to results folder (coors, time)" << endl;
}
