#pragma once

#include <opencv2/opencv.hpp>

/**
* Changes the vibrance of the input image by the specified amount
* @param src Source image for changing vibrance of
* @param s vibrance amount added to image
* @return modified image with vibrance changed
*/
cv::Mat changeVibrance(cv::Mat src, float s, float& mean);

int characterizeVibrance(float mean, cv::Mat src1);