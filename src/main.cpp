#include "../include/main.hpp"


int main(int argc, char *argv[])
{
    #ifdef TESTING
    int testResult;

    testResult = testCoor(180, 140, 43, -4, 25.0, 300.0);
    if (testResult == 0)  std::cout << "Test finished with\
                                       status: "
				    << testResult << std::endl;

    return (testResult);
    //system("WAIT");
    //system("pause");
    #endif // TESTING

    size_t i;

    int kernelSize = KERNEL_SIZE;
    int scale = SCALE;
    int delta = DELTA;
    int dDepth = CV_16S;
    const std::string imageName = argv[1];
    const std::string srcWindowName = "orig";
    const std::string resultWindowName = "Stars";
    const std::string blurredWindowName = "Blurred stars";
    const std::string grayscaledWindowName = "Grayscaled stars";
    const std::string boundedWindowName = "Bounded stars";
    const std::string temp1WindowName = "temp1 stars";
    const std::string temp2WindowName = "temp2 stars";
    const std::string temp3WindowName = "temp3 stars";
    const std::string temp4WindowName = "temp4 stars";
    cv::Mat srcImage, blurredImage, grayscaledImage;
    cv::Mat resultImage, resultImage1, resultImage2, resultImage3;
    cv::Mat grad;


    /// Read image file
    srcImage = cv::imread(imageName, cv::IMREAD_COLOR);
    if(srcImage.empty())
    {
        std::cout << "An error occured while open image file: "\
	          << strerror(errno) << std::endl;
        return (-1);
    }

    ///// Get matrix size
    //matrixSize = srcImage.size();

    cv::namedWindow(srcWindowName, cv::WINDOW_FREERATIO);
    cv::imshow(srcWindowName, srcImage);
    cv::waitKey();

    /// Convert image to grayscaled color
    cv::cvtColor(srcImage, grayscaledImage,\
		 cv::COLOR_BGR2GRAY);

//    namedWindow(grayscaledWindowName, WINDOW_FREERATIO);
//    //namedWindow(blurredWindowName, WINDOW_AUTOSIZE);
//    imshow(blurredWindowName, blurredImage);
//    waitKey();

    /// Blur image to decrease noise
    cv::GaussianBlur(grayscaledImage, blurredImage, cv::Size(3,3),\
		     0, 0, cv::BORDER_DEFAULT);

//    namedWindow(blurredWindowName, WINDOW_FREERATIO);
//    //namedWindow(blurredWindowName, WINDOW_AUTOSIZE);
//    imshow(blurredWindowName, blurredImage);
//    waitKey();


    /// Apply Sobel operator to gray-scaled image
    cv::Mat sobelResult;
    cv::Mat grad_x, grad_y;
    cv::Mat grad_x_abs, grad_y_abs;

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

    cv::namedWindow("Sobel", cv::WINDOW_FREERATIO);
    cv::imshow("Sobel", sobelResult);
    cv::waitKey();


    /// Apply Laplace operator
    cv::Mat laplaceResult, laplaceResult_abs;

    cv::Laplacian(blurredImage, laplaceResult, dDepth, kernelSize, scale, delta, cv::BORDER_DEFAULT);
    cv::convertScaleAbs(laplaceResult, laplaceResult_abs, 1, 0);

    cv::namedWindow("Laplacian", cv::WINDOW_FREERATIO);
    cv::imshow("Laplacian", laplaceResult_abs);
    cv::waitKey();


    /// Apply Canny edge detector
    cv::Mat cannyResult;

    cv::Canny(blurredImage, cannyResult, 100, 240, kernelSize);

    cv::namedWindow("Canny", cv::WINDOW_FREERATIO);
    cv::imshow("Canny", cannyResult);
    cv::waitKey();


    /// Drawing contours
    double thresh = 100, maxThreshold = 255;
    const std::string thresholdWindowName = "Threshold";
    const std::string contoursWindowName = "Threshold contours";
    cv::Mat thresholdOut;
    cv::Mat thresholdSobelOut;
    cv::Mat thresholdLaplaceOut;
    cv::Mat thresholdCannyOut;
    cv::Size matrixSize;
    std::vector <std::vector<cv::Point>> contours, sobelContours, laplaceContours, cannyContours;
    std::vector <cv::Vec4i> hierarchy, hierarchySobel, hierarchyLaplace, hierarchyCanny;
    //std::vector <cv::Rect> boundedRect(contours.size());
    //std::vector <cv::Point2f> center(contours.size());
    //std::vector <float> radius(contours.size());

    /// Threshold function transforms image to bi-color image
    /// (only white and black, without shades). It helps us to
    /// determine the clear-cut bounds of the objects on image
    cv::threshold(blurredImage, thresholdOut, thresh, maxThreshold,\
                  cv::THRESH_BINARY);
    cv::findContours(thresholdOut, contours, hierarchy,\
		     cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE,\
		     cv::Point(0, 0));

    cv::namedWindow(thresholdWindowName, cv::WINDOW_FREERATIO);
    cv::imshow(thresholdWindowName, thresholdOut);
    cv::waitKey();

    std::vector <std::vector <cv::Point>> ContPolygon_vec(contours.size());

    /// Approximate contours
    for (i = 0; i < contours.size(); i++)
    {
      cv::approxPolyDP(cv::Mat(contours[i]), ContPolygon_vec[i], 3, true);
      //boundedRect[i] = cv::boundingRect(cv::Mat(ContPolygon_vec[i]));
      //cv::minEnclosingCircle((cv::Mat) ContPolygon_vec[i],\
			     center[i], radius[i]);
    }

    /// Draw star contours
    cv::Mat starContours = cv::Mat::zeros(thresholdOut.size(), CV_8UC3);
    cv::RNG rng;
    for (i = 0; i < contours.size(); i++)
    {
        cv::Scalar color = cv::Scalar(rng.uniform(0, 255),\
                                      rng.uniform(0, 255),\
				                      rng.uniform(0, 255));
        cv::drawContours(starContours, ContPolygon_vec, i,\
			             color, 1, cv::LINE_8, std::vector<cv::Vec4i>(),\
			             0, cv::Point());
        ///rectangle(starContours, boundedRect[i].tl(),	\
		  boundedRect[i].br(), color,\
		  2, 8, 0);
        //cv::circle(starContours, center[i], radius[i], color,\
		   2, 8, 0);
    }
    cv::namedWindow(boundedWindowName, cv::WINDOW_FREERATIO);
    cv::imshow(boundedWindowName, starContours);
    cv::waitKey();

    /// Draw for Sobel image
    cv::threshold(sobelResult, thresholdSobelOut, thresh, maxThreshold,\
                  cv::THRESH_BINARY);
    cv::findContours(thresholdSobelOut, sobelContours, hierarchySobel,\
                     cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE,\
                     cv::Point(0, 0));

    std::vector <std::vector <cv::Point>> approxCont_Sobel(sobelContours.size());
    //cv::Mat contoursSobelImage = cv::Mat::zeros(thresholdSobelOut.size(), CV_8UC3);
    cv::Mat contoursSobelImage = srcImage;
    for (i = 0; i < sobelContours.size(); i++)
    {
        cv::approxPolyDP(cv::Mat(sobelContours[i]), approxCont_Sobel[i], 3, true);
    }
    for (i = 0; i < sobelContours.size(); i++)
    {
        cv::Scalar color = cv::Scalar(rng.uniform(0, 255),\
                                      rng.uniform(0, 255),\
                                      rng.uniform(0, 255));
        cv::drawContours(contoursSobelImage, approxCont_Sobel, i,\
                         color, 1, cv::LINE_8, std::vector <cv::Vec4i>(),\
                         0, cv::Point());
    }
    /// Show image
    cv::namedWindow("Sobel bounded", cv::WINDOW_FREERATIO);
    cv::imshow("Sobel bounded", contoursSobelImage);
    cv::waitKey();


    /// Draw Laplace boundaries
    cv::threshold(laplaceResult_abs, thresholdLaplaceOut, thresh, maxThreshold,\
                  cv::THRESH_BINARY);
    cv::findContours(thresholdLaplaceOut, laplaceContours, hierarchyLaplace,\
                     cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE,\
                     cv::Point());

    std::vector <std::vector <cv::Point>> approxCont_Laplace(laplaceContours.size());
    //cv::Mat contoursLaplaceImage = cv::Mat::zeros(thresholdLaplaceOut.size(), CV_8UC3);
    cv::Mat contoursLaplaceImage = srcImage;
    for (i = 0; i < laplaceContours.size(); i++)
    {
        cv::approxPolyDP(cv::Mat(laplaceContours[i]), approxCont_Laplace[i], 3, true);
    }
    for (i = 0; i < laplaceContours.size(); i++)
    {
        cv::Scalar color = cv::Scalar(rng.uniform(0, 255),
                                      rng.uniform(0, 255),
                                      rng.uniform(0, 255));
        cv::drawContours(contoursLaplaceImage, approxCont_Laplace, i,\
                         color, 1, cv::LINE_8, std::vector <cv::Vec4i>(),
                         0, cv::Point());
    }
    /// Show image
    cv::namedWindow("Laplace boundaries", cv::WINDOW_FREERATIO);
    cv::imshow("Laplace boundaries", contoursLaplaceImage);
    cv::waitKey();


    /// Draw Canny boundaries
    cv::threshold(cannyResult, thresholdCannyOut, thresh, maxThreshold,\
                  cv::THRESH_BINARY);
    cv::findContours(thresholdCannyOut, cannyContours, hierarchyCanny,\
                     cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE,\
                     cv::Point());

    std::vector <std::vector <cv::Point>> approxCont_Canny(cannyContours.size());
    //cv::Mat contoursCannyImage = cv::Mat::zeros(thresholdCannyOut.size(), CV_8UC3);
    cv::Mat contoursCannyImage = srcImage;
    for (i = 0; i < cannyContours.size(); i++)
    {
        cv::approxPolyDP(cv::Mat(cannyContours[i]), approxCont_Canny[i], 3, true);
    }
    for (i = 0; i < cannyContours.size(); i++)
    {
        cv::Scalar color = cv::Scalar(rng.uniform(0, 255),
                                      rng.uniform(0, 255),
                                      rng.uniform(0, 255));
        cv::drawContours(contoursCannyImage, approxCont_Canny, i,\
                         color, 1, cv::LINE_8, std::vector <cv::Vec4i>(),
                         0, cv::Point());
    }
    /// Show image
    cv::namedWindow("Canny boundaries", cv::WINDOW_FREERATIO);
    cv::imshow("Canny boundaries", contoursCannyImage);
    cv::waitKey();

    /// Wait for ESC key
    while ((cv::waitKey() & 0xFF) != ESCAPE_KEY);


    return (0);
}

/*

//    namedWindow(temp4WindowName, WINDOW_FREERATIO);
//    imshow(temp4WindowName, grad_y_abs);
//    waitKey();
//
//    namedWindow(temp2WindowName, WINDOW_FREERATIO);
//    imshow(temp2WindowName, resultImage2);
//    waitKey();
//
//    namedWindow(temp3WindowName, WINDOW_FREERATIO);
//    imshow(temp3WindowName, resultImage3);
//    waitKey();

//    namedWindow(contoursWindowName, WINDOW_FREERATIO);
//    imshow(contoursWindowName, contoursOut);
//    waitKey();
*/
