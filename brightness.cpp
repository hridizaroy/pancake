#include "brightness.h"

cv::Mat changeBrightness(const cv::Mat& src, double brightnessAmount)
{
	cv::Mat result;
	src.convertTo(result, -1, 1, brightnessAmount);

	return result;
}