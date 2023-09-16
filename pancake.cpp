// pancake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include "filenameFunctions.cpp"

using namespace std;

int main() {
    
    // create an image
    cv::Mat src = cv::imread(getFileName(), cv::IMREAD_GRAYSCALE);
    src.convertTo(src, CV_32FC1, 1.0 / 255.0);

    cv::Mat dst;
    dst.create(src.rows, src.cols, CV_32FC1);

    cv::Mat lut;
    int temp;
    lut.create(256, 256, CV_8UC1);

    // create a window
    cv::namedWindow("Controls", cv::WINDOW_NORMAL);

    // create trackbars for color change
    int lift = 0, gamma = 0, gain = 0;
    double liftFactor, gammaFactor, gainFactor;

    cv::createTrackbar("Lift", "Controls", &lift, 100, NULL, NULL);
    cv::createTrackbar("Gamma", "Controls", &gamma, 100, NULL, NULL);
    cv::createTrackbar("Gain", "Controls", &gain, 100, NULL, NULL);


    while (true) {

        // Transform into scaled uniform factors
        liftFactor = -1 * abs(((lift / 50.0) * 0.99) + -0.99);
        liftFactor = (lift < 50) ? liftFactor : (-1.0 * liftFactor / (1 + liftFactor));

        gammaFactor = ((-0.02 * gamma) + 2) * 0.99 + 0.01;
        gammaFactor = (gamma < 50) ? 1.0 / (1.0 - (gammaFactor - 1.0)) : gammaFactor;

        gainFactor = (gain / 50.0) * 0.99 + 0.01;
        gainFactor = (gain < 50) ? gainFactor : (1.0 / (1.0 - (gainFactor - 1.0)));


        for (size_t r = 0; r < src.rows; r++) {
            for (size_t c = 0; c < src.cols; c++) {
                dst.at<float>(r, c) = (pow(src.at<float>(r, c), gammaFactor) + liftFactor) * (gainFactor / (1.0 + liftFactor));
            }
        }

        lut = 0;
        for (size_t i = 0; i < 256; i++) {

            temp = ((pow((i / 255.0), gammaFactor) + liftFactor) * (gainFactor / (1.0 + liftFactor))) * 255.0 + 0.5;
            if (temp > 255) temp = 255;
            if (temp < 0) temp = 0;

            lut.at<uint8_t>(255 - temp, i) = 255;

        }

        // display the image
        cv::imshow("Image", src);
        cv::imshow("Corrected Image", dst);
        cv::imshow("Look Up Table (LUT)", lut);


        // wait for a key press
        if (cv::waitKey(30) == 27) {
            break;
        }
    }

    // destroy the window
    cv::destroyAllWindows();

    return 0;
}