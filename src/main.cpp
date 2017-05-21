/*
 * @file main.cpp
 * @brief A sample file used for testing what opencv can do. Binary output is
 * /bin/DisplayImage
 * @usage ./DisplayImage testImage.png
 */

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <stdio.h>
#include <vector>

bool displayImage(std::string imagePath)
{
    bool retVal(false);
    // Type of image is cv::Mat which is short for matrix
    cv::Mat image(cv::imread(imagePath, 1));

    if (image.data != nullptr)
    {
        // Displays the image
        cv::namedWindow("Display Image", cv::WINDOW_FULLSCREEN);
        cv::imshow("Display Image", image);

        // Print the image as a matrix
        std::cout << "Image = " << image << "\n";

        // Print the image size
        std::cout << "Image size = " << image.size << "\n";

        cv::waitKey(0);
        retVal = true;
    }
    else
    {
        std::cout << "No image data \n";
    }

    return retVal;
}

bool detectCircles(std::string imagePath)
{

    using namespace cv;

    Mat srcImage, srcGray;

    /// Read the image
    srcImage = imread(imagePath, 1);

    if (!srcImage.data)
    {
        return -1;
    }

    /// Convert it to gray
    cvtColor(srcImage, srcGray, CV_BGR2GRAY);

    /// Reduce the noise so we avoid false circle detection
    // GaussianBlur(srcGray, srcGray, Size(9, 9), 2, 2);

    std::vector<Vec3f> circles;

    /// Apply the Hough Transform to find the circles
    HoughCircles(srcGray, circles, CV_HOUGH_GRADIENT, 1, srcGray.rows / 8, 200,
                 100, srcImage.size[0] / 3, 0);

    /// Draw the circles detected
    for (size_t i = 0; i < circles.size(); i++)
    {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        // circle center
        circle(srcImage, center, 3, Scalar(0, 255, 0), -1, 8, 0);
        // circle outline
        circle(srcImage, center, radius, Scalar(0, 0, 255), 3, 8, 0);
    }

    /// Show your results
    namedWindow("Hough Circle Transform Demo", CV_WINDOW_AUTOSIZE);
    imshow("Hough Circle Transform Demo", srcImage);

    waitKey(0);
    return 0;
}

int main(int argc, char **argv)
{
    bool retVal(false);

    if (argc == 2)
    {
        auto imagePath(argv[1]);
        retVal = detectCircles(imagePath);
    }
    else
    {
        std::cout << "usage: DisplayImage.out <Image_Path>\n";
    };

    return retVal;
}
