#include "temperature.h"

cv::Mat changeTemperature(const cv::Mat& src, int temperatureAmount)
{
	int rows = src.rows;
	int cols = src.cols;

	cv::Mat result;
	result.create(rows, cols, CV_8UC3);

	int minClamp = 0;
	int maxClamp = 255;

	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			result.at<cv::Vec3b>(row, col)[0] = std::clamp(static_cast<int>(src.at<cv::Vec3b>(row, col)[0]) - temperatureAmount, minClamp, maxClamp);
			result.at<cv::Vec3b>(row, col)[1] = std::clamp(static_cast<int>(src.at<cv::Vec3b>(row, col)[1]), minClamp, maxClamp);
			result.at<cv::Vec3b>(row, col)[2] = std::clamp(static_cast<int>(src.at<cv::Vec3b>(row, col)[2]) + temperatureAmount, minClamp, maxClamp);
		}
	}

	return result;
}
