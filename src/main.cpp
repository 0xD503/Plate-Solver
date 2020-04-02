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

    double thresh = 100, maxThreshold = 255;
    const std::string thresholdWindowName = "Threshold";
    const std::string contoursWindowName = "Contours";
    std::vector <std::vector<cv::Point>> contours;
    std::vector <cv::Vec4i> hierarchy;
    cv::Mat thresholdOut, contoursOut;
    cv::Size matrixSize;


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

    /// Blur image to decrease noise
    cv::GaussianBlur(srcImage, blurredImage, cv::Size(3,3),\
		     0, 0, cv::BORDER_DEFAULT);

//    namedWindow(blurredWindowName, WINDOW_FREERATIO);
//    //namedWindow(blurredWindowName, WINDOW_AUTOSIZE);
//    imshow(blurredWindowName, blurredImage);
//    waitKey();

    /// Convert image to grayscaled color
    cv::cvtColor(blurredImage, grayscaledImage,\
		 cv::COLOR_BGR2GRAY);

//    namedWindow(grayscaledWindowName, WINDOW_FREERATIO);
//    //namedWindow(blurredWindowName, WINDOW_AUTOSIZE);
//    imshow(blurredWindowName, blurredImage);
//    waitKey();

    /// Treshold function transforms image to bi-color image
    /// (only white and black, without shades). It helps us to
    /// determine the clear-cut bounds of the objects on image
    cv::threshold(grayscaledImage, thresholdOut, thresh,\
	      maxThreshold, cv::THRESH_BINARY);
    cv::findContours(thresholdOut, contours, hierarchy,
		     cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE,
		     cv::Point(0, 0));

    cv::namedWindow(thresholdWindowName, cv::WINDOW_FREERATIO);
    cv::imshow(thresholdWindowName, thresholdOut);
    cv::waitKey();
//    namedWindow(contoursWindowName, WINDOW_FREERATIO);
//    imshow(contoursWindowName, contoursOut);
//    waitKey();
    std::vector <std::vector<cv::Point>> ContPolygon_vec(contours.size());
    std::vector <cv::Rect> boundedRect(contours.size());
    std::vector <cv::Point2f> center(contours.size());
    std::vector <float> radius(contours.size());

    for (i = 0; i < contours.size(); i++)
    {
      cv::approxPolyDP(cv::Mat(contours[i]),\
		       ContPolygon_vec[i], 3, true);
      boundedRect[i] = cv::boundingRect(cv::Mat(ContPolygon_vec[i]));
      cv::minEnclosingCircle((cv::Mat) ContPolygon_vec[i],\
			     center[i], radius[i]);
    }

    cv::Mat starContours = cv::Mat::zeros(thresholdOut.size(),	\
					  CV_8UC3);
    cv::RNG rng;
    for (i = 0; i < contours.size(); i++)
    {
        cv::Scalar color = cv::Scalar(rng.uniform(0, 255),\
	 		              rng.uniform(0, 255),\
				      rng.uniform(0, 255));
        cv::drawContours(starContours, ContPolygon_vec, i,\
			 color, 1, 8, std::vector<cv::Vec4i>(),\
			 0, cv::Point());
        //rectangle(starContours, boundedRect[i].tl(),	\
		  boundedRect[i].br(), color,\
		  2, 8, 0);
        cv::circle(starContours, center[i], radius[i], color,\
		   2, 8, 0);
    }

    cv::namedWindow(boundedWindowName, cv::WINDOW_FREERATIO);
    cv::imshow(boundedWindowName, starContours);
    cv::waitKey();


    ///
//  Mat grad_x, grad_y;

//    Sobel(grayscaledImage, grad_x, dDepth, 1, 0, kernelSize,	\
	  scale, delta, BORDER_DEFAULT);
//    Sobel(grayscaledImage, grad_y, dDepth, 0, 1, kernelSize,	\
	  scale, delta, BORDER_DEFAULT);

//    Mat grad_x_abs, grad_y_abs;

//    convertScaleAbs(grad_x, grad_x_abs);
//    convertScaleAbs(grad_y, grad_y_abs);

//    namedWindow(temp3WindowName, WINDOW_FREERATIO);
//    imshow(temp3WindowName, grad_x_abs);
//    waitKey();
//    namedWindow(temp4WindowName, WINDOW_FREERATIO);
//    imshow(temp4WindowName, grad_y_abs);
//    waitKey();


//    addWeighted(grad_x_abs, 0.5, grad_y_abs, 0.5, 0,	\
		resultImage);
//    addWeighted(grad_x_abs, 0.5, grad_y_abs, 0.5, 10,	\
		resultImage1);
//    addWeighted(grad_x_abs, 0.5, grad_y_abs, 0.5, 20,	\
		resultImage2);
//    addWeighted(grad_x_abs, 0.5, grad_y_abs, 0.5, 100,	\
		resultImage3);

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

    cv::waitKey();


    return (0);
}
