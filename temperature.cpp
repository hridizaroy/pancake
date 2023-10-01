#include "temperature.h"

cv::Mat changeTemperature(const cv::Mat& src, int temperatureAmount, float& meanR, float& meanB)
{
	meanB = 0;
	meanR = 0;
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
			meanB += src.at<cv::Vec3b>(row, col)[0] - temperatureAmount;
			result.at<cv::Vec3b>(row, col)[1] = std::clamp(static_cast<int>(src.at<cv::Vec3b>(row, col)[1]), minClamp, maxClamp);
			result.at<cv::Vec3b>(row, col)[2] = std::clamp(static_cast<int>(src.at<cv::Vec3b>(row, col)[2]) + temperatureAmount, minClamp, maxClamp);
			meanR += src.at<cv::Vec3b>(row, col)[2] + temperatureAmount;
		}
	}

	meanR /= src.rows * src.cols;
	meanB /= src.rows * src.cols;
	return result;
}

int characterizeTemperature(float meanR, float meanB, cv::Mat src1)
{
	float meanR1 = cv::mean(src1)[2];
	float meanB1 = cv::mean(src1)[0];

	((meanR1 - meanR) + (meanB - meanB1)) / 2.0;


	return ((meanR1 - meanR) + (meanB - meanB1)) / -5.1;
}