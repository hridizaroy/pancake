#pragma once

#include <opencv2/opencv.hpp>

/**
* Changes the gain of the input image by the specified amount
* @param src Source image for changing gain of
* @param g gain amount that image pixels are multiplied by
* @return modified image with gain changed
*/
cv::Mat changeGain(const cv::Mat& src, float g);