/*
 * @file main.cpp
 * @brief A sample file used for testing what opencv can do. Binary output is
 * /bin/DisplayImage
 * @usage ./DisplayImage testImage.png
 */

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
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

bool cropCap(std::string imagePath)
{
    /// Read the image
    auto srcImage(cv::imread(imagePath, 1));

    if (srcImage.data)
    {
        cv::Mat srcGray;

        /// Convert it to gray
        cv::cvtColor(srcImage, srcGray, cv::COLOR_BGR2GRAY);

        /// Reduce the noise so we avoid false circle detection
        cv::GaussianBlur(srcGray, srcGray, cv::Size(9, 9), 2, 2);

        std::vector<cv::Vec3f> circles;

        /// Apply the Hough Transform to find the circles
        cv::HoughCircles(srcGray, circles, cv::HOUGH_GRADIENT, 1,
                         srcGray.rows / 8, 200, 100, srcImage.size[0] / 3, 0);

        if (circles.size() == 1)
        {
            /// Draw the circles detected
            cv::Point center(cvRound(circles[0][0]), cvRound(circles[0][1]));
            auto radius(cvRound(circles[0][2]));

            // Draw the mask: white circle on black background
            cv::Mat1b mask(srcImage.size(), uchar(0));
            cv::circle(mask, center, radius, cv::Scalar(255), cv::FILLED);

            // Compute the bounding box
            auto bbox(cv::Rect(center.x - radius, center.y - radius, radius * 2,
                               radius * 2));

            // Create a black image
            cv::Mat3b croppedImage(srcImage.size(), cv::Vec3b(0, 0, 0));

            // Copy only the image under the white circle to black image
            srcImage.copyTo(croppedImage, mask);

            // Crop according to the roi
            croppedImage = croppedImage(bbox);

            cv::namedWindow("Hough Circle Transform Demo", cv::WINDOW_AUTOSIZE);
            cv::imshow("Hough Circle Transform Demo", croppedImage);

            cv::waitKey(0);
        }
        else
        {
            std::cerr
                << "Unexpected number of circles detected: NumberOfCircles= "
                << circles.size() << '\n';
        }
    }
    else
    {
        std::cout << "Invalid image " << imagePath << '\n';
    }

    return 0;
}

int main(int argc, char **argv)
{
    bool retVal(false);

    if (argc == 2)
    {
        auto imagePath(argv[1]);
        retVal = cropCap(imagePath);
    }
    else
    {
        std::cout << "usage: DisplayImage.out <Image_Path>\n";
    };

    return retVal;
}
