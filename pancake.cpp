// pancake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#include "filenameFunctions.h"

#include "gain.h"
#include "vibrance.h"
#include "brightness.h"
#include "temperature.h"

using namespace std;

int main() {
    
    // open an image
    cv::Mat src = cv::imread(getFileName(), cv::IMREAD_COLOR);
    if (src.empty()) { 
        cerr << "Image not opened. Exiting";
        exit(1);
    }
    cv::Mat dst;
    dst.create(src.rows, src.cols, CV_32FC1);

    // create a window
    cv::namedWindow("Controls", cv::WINDOW_NORMAL);

    // create trackbars for color change
    int gain = 0, brightness = 0, vibrance = 0, temperature = 0;
    cv::createTrackbar("Gain", "Controls", &gain, 100, NULL, NULL);
    cv::setTrackbarMin("Gain", "Controls", -100);
    cv::createTrackbar("Brightness", "Controls", &brightness, 100, NULL, NULL);
    cv::createTrackbar("Color", "Controls", &vibrance, 100, NULL, NULL);
    cv::createTrackbar("Temperature", "Controls", &temperature, 100, NULL, NULL);

    while (true) {

        dst = src;
        dst = changeBrightness(dst, (brightness / 50.0) - 1.0);
        //dst = changeGain(dst, gain);
        //dst = changeVibrance(dst, vibrance);
        //dst = changeTemperature(dst, temperature);
   
        // display the image
        cv::imshow("Original Image", src);
        cv::imshow("Altered Image", dst);


        // wait for a key press
        if (cv::waitKey(30) == 27) {
            break;
        }
    }

    // destroy the window
    cv::destroyAllWindows();

    return 0;
}