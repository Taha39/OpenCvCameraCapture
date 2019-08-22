// CamCaptureOpenCV.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include "pch.h"
#include <iostream>
#include "opencv2/opencv.hpp"
#include "D:\Taha\study\vs2017\TestProject\CamResolutionDShow\CamResolutionDShow.h"
using namespace cv;

int main(int argc, char** argv)
{
	int w{ 0 };
	int h{ 0 };
	auto cam_details = enum_devices();
	auto itr = cam_details.begin();
	for (; itr != cam_details.end(); itr++) {
		setcolor(GREEN);
		std::cout << "\n Cam Name: " << itr->first << " Resolution supportd: \n";
		auto resolution = itr->second;
		for (int i = 0; i < resolution.size(); i++) {
			setcolor(BLUE);
			std::cout << "\t \t " << resolution[i].first << " x " << resolution[i].second << std::endl;
		}
		w = resolution[3].first;
		h = resolution[3].second;
	}

	std::cout << w << std::endl;
	std::cout << h << std::endl;
	std::cout << "Press any key to start capture camera..." << std::endl;
	getchar();
	VideoCapture cap;
	// open the default camera, use something different from 0 otherwise;
	// Check VideoCapture documentation.
	if (!cap.open(0))
		return 0;
	
	cap.set(cv::CAP_PROP_FRAME_WIDTH, w);
	cap.set(cv::CAP_PROP_FRAME_HEIGHT, h);
	
	FILE* fp;
	fopen_s(&fp, "test.rgb", "wb");
	for (;;)
	{
		Mat frame;
		cap >> frame;
		if (frame.empty()) break; // end of video stream
		
		cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);

		int size = frame.total() * frame.elemSize();
		fwrite(frame.data, 1, size, fp);
		
		//if (waitKey(10) == 27) break; // stop capturing by pressing ESC 
	}
	fclose(fp);
	// the camera will be closed automatically upon exit
	
	return 0;
}