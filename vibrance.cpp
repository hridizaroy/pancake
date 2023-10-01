#include "vibrance.h"

cv::Mat changeVibrance(cv::Mat src, float s, float& mean) {
	cv::Mat dst, temp, tempMean;
	dst.create(src.rows, src.cols, CV_32FC3);
	tempMean.create(src.rows, src.cols, CV_32FC1);

	float t;

	src.convertTo(src, CV_32FC1);
	cv::cvtColor(src, temp, cv::COLOR_BGR2HSV);

	for (int r = 0; r < src.rows; r++) {
		for (int c = 0; c < src.cols; c++) {
			dst.at<cv::Vec3f>(r, c)[0] = temp.at<cv::Vec3f>(r, c)[0];

			t = temp.at<cv::Vec3f>(r, c)[1] + s;
			tempMean.at<float>(r, c) = t;
			if (t < 0) t = 0;
			dst.at<cv::Vec3f>(r, c)[1] = t;

			dst.at<cv::Vec3f>(r, c)[2] = temp.at<cv::Vec3f>(r, c)[2];
		}
	}
	mean = cv::mean(tempMean)[0];
	cv::cvtColor(dst, dst, cv::COLOR_HSV2BGR);
	dst.convertTo(dst, CV_8UC3);

	return dst;

}

int characterizeVibrance(float mean, cv::Mat src1)
{

	src1.convertTo(src1, CV_32FC1);
	cv::cvtColor(src1, src1, cv::COLOR_BGR2HSV);

	float mean1 = cv::mean(src1)[1];


	return 100*(mean - mean1);
}