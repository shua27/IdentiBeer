#include <opencv2/opencv.hpp>
#include <stdio.h>

int main(int argc, char **argv)
{
    bool retVal(false);

    if (argc == 2)
    {
        cv::Mat image(cv::imread(argv[1], 1));

        if (image.data)
        {
            cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);
            cv::imshow("Display Image", image);

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