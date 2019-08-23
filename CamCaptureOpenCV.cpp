#include <iostream>
#include "opencv2/opencv.hpp"
#include "CamCaptureOpenCV.h"
using namespace cv;

namespace cam_capture {

	void startCamCapture(int cam_no, int width, int height) {
		VideoCapture cap;
		// open the default camera, use something different from 0 otherwise;
		// Check VideoCapture documentation.
		if (!cap.open(cam_no))
			return;

		cap.set(cv::CAP_PROP_FRAME_WIDTH, width);
		cap.set(cv::CAP_PROP_FRAME_HEIGHT, height);

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
		}
		fclose(fp);
		// the camera will be closed automatically upon exit
	}
}	//cam_capture