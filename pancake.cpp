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
    
    float nullMean, meanBrightness, meanVibrance, meanR, meanB;

    // open an image
    cv::Mat src = cv::imread(getFileName(), cv::IMREAD_COLOR);
    if (src.empty()) { 
        cerr << "Image not opened. Exiting";
        exit(1);
    }
    cv::Mat dst;
    dst.create(src.rows, src.cols, CV_8UC3);

    // create a window
    cv::namedWindow("Controls", cv::WINDOW_NORMAL);

    // create trackbars for color change
    int brightness = 0, vibrance = 0, temperature = 0;

    cv::createTrackbar("Brightness", "Controls", &brightness, 100, NULL, NULL);
    cv::setTrackbarMin("Brightness", "Controls", -100);

    cv::createTrackbar("Color", "Controls", &vibrance, 100, NULL, NULL);
    cv::setTrackbarMin("Color", "Controls", -100);

    cv::createTrackbar("Temperature", "Controls", &temperature, 100, NULL, NULL);
    cv::setTrackbarMin("Temperature", "Controls", -100);

    while (true) {

        dst = src;

        //
        dst = changeBrightness(dst, brightness, meanBrightness);
        dst = changeVibrance(dst, vibrance / 100.0, meanVibrance);
        dst = changeTemperature(dst, temperature * 2.55, meanR, meanB);
        //

        // display the image
        cv::imshow("Original Image", src);
        cv::imshow("Altered Image", dst);

        // wait for a key press
        if (cv::waitKey(30) == ' ') {
            break;
        }
    }

    // destroy the window
    cv::destroyAllWindows();

    /// SECOND PHASE /////////////////////////////////////


    // open an image
    cv::Mat src1 = cv::imread(getFileName(), cv::IMREAD_COLOR);
    if (src1.empty()) {
        cerr << "Image not opened. Exiting";
        exit(1);
    }
    cv::Mat dst1;
    dst1.create(src1.rows, src1.cols, CV_8UC3);

    int equivBrightness = characterizeBrightness(meanBrightness, src1);
    int equivVibrance = characterizeVibrance(meanVibrance, src1);
    int equivTemperature = characterizeTemperature(meanR, meanB, src1);

    cout << "Equivalent Brightness: " << equivBrightness << endl;
    cout << "Equivalent Color: " << equivVibrance << endl;
    cout << "Equivalent Temperature: " << equivTemperature << endl;

    //
    float nullMean1;
    dst1 = src1;
    dst1 = changeBrightness(dst1, equivBrightness, nullMean);
    dst1 = changeVibrance(dst1, equivVibrance / 100.0, nullMean);
    dst1 = changeTemperature(dst1, equivTemperature * 2.55, nullMean, nullMean1);
    //

    cv::imshow("Original Image 0", src);
    cv::imshow("Altered Image 0", dst);

    cv::imshow("Original Image 1", src1);
    cv::imshow("Altered Image 1 with Preset", dst1);


    cv::waitKey(0);
    return 0;

    
}