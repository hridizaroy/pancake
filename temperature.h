#pragma once

#include <opencv2/opencv.hpp>

/**
* Changes the temperature of the input image by the specified amount
* @param src Source image for changing temperature of
* @param temperatureAmount amount added to red channel and subtracted from blue channel
* @return modified image with temperature changed
*/
cv::Mat changeTemperature(const cv::Mat& src, int temperatureAmount, float& meanR, float& meanB);

int characterizeTemperature(float meanR, float meanB, cv::Mat src1);