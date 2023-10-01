#include "brightness.h"

cv::Mat changeBrightness(const cv::Mat& src, float brightnessAmount, float& mean)
{	
	cv::Mat result;
	src.convertTo(result, CV_32FC1);
	cv::cvtColor(result, result, cv::COLOR_BGR2HSV);

	for (int r = 0; r < src.rows; r++) {
		for (int c = 0; c < src.cols; c++) {
			result.at<cv::Vec3f>(r, c)[0] = result.at<cv::Vec3f>(r, c)[0];
			result.at<cv::Vec3f>(r, c)[1] = result.at<cv::Vec3f>(r, c)[1];
			result.at<cv::Vec3f>(r, c)[2] = result.at<cv::Vec3f>(r, c)[2] + brightnessAmount;
		}
	}

	mean = cv::mean(result)[2];

	cv::cvtColor(result, result, cv::COLOR_HSV2BGR);
	result.convertTo(result, CV_8UC3);


	return result;
}

int characterizeBrightness(float mean, cv::Mat src1)
{

	src1.convertTo(src1, CV_32FC1);
	cv::cvtColor(src1, src1, cv::COLOR_BGR2HSV);


	float mean1 = cv::mean(src1)[2];

	return (mean - mean1);
}