/*
 * @file main.cpp
 * @brief A sample file used for testing what opencv can do. Binary output is
 * /bin/DisplayImage
 * @usage ./DisplayImage testImage.png
 */

#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

#include <stdio.h>

int main(int argc, char **argv)
{
    bool retVal(false);

    if (argc == 2)
    {
        // Type of image is cv::Mat which is short for matrix
        cv::Mat image(cv::imread(argv[1], 1));

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
    }
    else
    {
        std::cout << "usage: DisplayImage.out <Image_Path>\n";
    };

    return retVal;
}