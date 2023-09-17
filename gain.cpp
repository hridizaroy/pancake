#include <iostream>
#include <string>

#include <opencv2/opencv.hpp>

#pragma once

cv::Mat changeGain(const cv::Mat& src, float g) {
	cv::Mat dst;
	dst.create(src.rows, src.cols, CV_8UC3);

	for (int r = 0; r < src.rows; r++) {
		for (int c = 0; c < src.cols; c++) {
			dst.at<cv::Vec3b>(r, c)[0] = std::clamp(static_cast<int>(src.at<cv::Vec3b>(r, c)[0] * g), 0, 255);
			dst.at<cv::Vec3b>(r, c)[1] = std::clamp(static_cast<int>(src.at<cv::Vec3b>(r, c)[1] * g), 0, 255);
			dst.at<cv::Vec3b>(r, c)[2] = std::clamp(static_cast<int>(src.at<cv::Vec3b>(r, c)[2] * g), 0, 255);
		}
	}

	return dst;

}