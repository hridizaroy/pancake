#pragma once

#include <opencv2/opencv.hpp>

/**
* Changes the brightness of the input image by the specified amount
* @param src Source image for changing brightness of
* @param brightnessAmount amount to change brightness by
* @return modified image with brightness changed
*/
cv::Mat changeBrightness(const cv::Mat& src, double brightnessAmount);