//#include <iostream>
//#include <string>
//#include <vector>
//#include "facedetect-dll.h"
//#include <opencv2/opencv.hpp>

//int main()
//{
//	std::vector<std::string> images{ "1.jpg", "2.jpg", "3.jpg", "4.jpeg", "5.jpeg", "6.jpg", "7.jpg", "8.jpg", "9.jpg", "10.jpg",
//		"11.jpeg", "12.jpg", "13.jpeg", "14.jpg", "15.jpeg", "16.jpg", "17.jpg", "18.jpg", "19.jpg", "20.jpg" };
//	std::vector<int> count_faces{1, 2, 6, 0, 1, 1, 1, 2, 1, 1,
//		1, 1, 1, 1, 1, 1, 1, 0, 8, 2};
//
//	std::string path_images{ "E:/1树莓派/Face_Test-master/testdata/" };
//
//	/*if (images.size() != count_faces.size()) {
//		fprintf(stderr, "their size that images and count_faces are mismatch\n");
//		return -1;
//	}*/
//
//	
//
//	Mat jj=imread("E:/testdata/1.jpg");
//	imshow("ss", jj);
//
//
//
//	typedef int* (*detect_face)(unsigned char * gray_image_data, int width, int height, int step,
//		float scale, int min_neighbors, int min_object_width, int max_object_width);
//
//	detect_face detect_methods[]{
//		&facedetect_frontal,
//		&facedetect_multiview,
//		&facedetect_multiview_reinforce,
//		&facedetect_frontal_surveillance
//	};
//
//	std::string detect_type[4] {"face frontal", "face multiview", "face multiview reinforce", "face surveillance"};
//
//	for (int method = 0; method < 4; method++) {
//		detect_face detect = detect_methods[method];
//		fprintf(stderr, "detect type: %s\n", detect_type[method].c_str());
//
//		for (int i = 0; i < images.size(); i++) {
//			cv::Mat src_ = cv::imread(path_images + images[i], 1);
//			if (src_.empty()) {
//				fprintf(stderr, "read image error: %s\n", images[i].c_str());
//				return -1;
//			}
//
//			cv::Mat src;
//			cv::cvtColor(src_, src, CV_BGR2GRAY);
//
//			int* results = nullptr;
//			results = detect(src.data, src.cols, src.rows, src.step, 1.2f, 2, 10, 0);
//			std::string save_result = path_images + std::to_string(method) + "_" + images[i];
//			//fprintf(stderr, "save result: %s\n", save_result.c_str());
//
//			for (int faces = 0; faces < (results ? *results : 0); faces++) {
//				short* p = ((short*)(results + 1)) + 6 * faces;
//				int x = p[0];
//				int y = p[1];
//				int w = p[2];
//				int h = p[3];
//				int neighbors = p[4];
//				int angle = p[5];
//
//				fprintf(stderr, "image_name: %s, faces_num: %d, face_rect=[%d, %d, %d, %d], neighbors=%d, angle=%d\n",
//					images[i].c_str(), *results, x, y, w, h, neighbors, angle);
//
//				cv::rectangle(src_, cv::Rect(x, y, w, h), cv::Scalar(0, 255, 0), 2);
//			}
//			//imshow("ddd", src_);
//			cv::imwrite(save_result, src_);
//		}
//	}
//
//	int width = 200;
//	int height = 200;
//	cv::Mat dst(height * 5, width * 4, CV_8UC3);
//	for (int i = 0; i < images.size(); i++) {
//		std::string input_image = path_images + "2_" + images[i];
//		cv::Mat src = cv::imread(input_image, 1);
//		if (src.empty()) {
//			fprintf(stderr, "read image error: %s\n", images[i].c_str());
//			return -1;
//		}
//
//		cv::resize(src, src, cv::Size(width, height), 0, 0, 4);
//		int x = (i * width) % (width * 4);
//		int y = (i / 4) * height;
//		cv::Mat part = dst(cv::Rect(x, y, width, height));
//		src.copyTo(part);
//	}
//	std::string output_image = path_images + "result.png";
//	cv::imwrite(output_image, dst);
//
//	fprintf(stderr, "ok\n");
//	return 0;
//}
//
//#include <opencv.hpp>
#include <opencv.hpp>
#include "facedetect-dll.h"
#pragma comment(lib,"libfacedetect.lib")
#pragma comment(lib,"libfacedetect.lib")
#define DETECT_BUFFER_SIZE 0x20000
using namespace cv;
String eyes_cascade_name = "E:/1树莓派/Face_Test-master/demo/libfacedetection/haarcascade_eye_tree_eyeglasses.xml";
int flag = 0;
CascadeClassifier eyes_cascade;   //定义人眼分类器  
void detectAndDisplay(Mat frame_per)
{
	Mat frame;
	Mat map_x;
	Mat map_y;

	/*************************	水平翻转	**************************/
	frame.create(frame_per.size(), frame_per.type());
	map_x.create(frame_per.size(), CV_32FC1);
	map_y.create(frame_per.size(), CV_32FC1);
	for (int i = 0; i < frame_per.rows; ++i)
	{
		for (int j = 0; j < frame_per.cols; ++j)
		{
			map_x.at<float>(i, j) = (float)(frame_per.cols - j);
			map_y.at<float>(i, j) = (float)i;//(src.rows - i) ;  
		}
	}
	remap(frame_per, frame, map_x, map_y, CV_INTER_LINEAR);
	/*****************************************************************/
	CvFont font;
	cvInitFont(&font, CV_FONT_HERSHEY_COMPLEX, 1.0, 1.0, 0, 2, 8);
	/*************************************************/
	Mat gray;
	Mat faceROI;// = frame(Rect(x, y, w, h));
	unsigned char * pBuffer = (unsigned char *)malloc(DETECT_BUFFER_SIZE);
	std::vector<Rect> eyes;
	cvtColor(frame, gray, CV_BGR2GRAY);
	equalizeHist(gray, gray);
	int* results = nullptr;
	int doLandmark = 1;
	results = facedetect_multiview_reinforce(pBuffer,gray.data, gray.cols, gray.rows, gray.step, 1.2f, 2, 10, 0, doLandmark);
	//std::string save_result = path_images + std::to_string(method) + "_" + images[i];
	//fprintf(stderr, "save result: %s\n", save_result.c_str());
	Mat result_frontal = frame.clone();
	for (int faces = 0; faces < (results ? *results : 0); faces++) {
		//short* p = ((short*)(results + 1)) + 6 * faces;
		short * p = ((short*)(results + 1)) + 142 * faces;
		int x = p[0];
		int y = p[1];
		int w = p[2];
		int h = p[3];
		int neighbors = p[4];
		int angle = p[5];

		fprintf(stderr, "image_name: %s, faces_num: %d, face_rect=[%d, %d, %d, %d], neighbors=%d, angle=%d\n",
			"dd", *results, x, y, w, h, neighbors, angle);

		//rectangle(result_frontal, Rect(x*0.8, y*0.8, w, h), Scalar(0, 0, 0),1,1,0);
		if (doLandmark)
		{
			for (int j = 0; j < 68; j++)
				circle(result_frontal, Point((int)p[6 + 2 * j], (int)p[6 + 2 * j + 1]), 1, cvScalar(0, 150, 255));//BGR
		}

		/****************************************
		Mat gray;
		Mat faceROI;// = frame(Rect(x, y, w, h));
		std::vector<Rect> eyes;
		cvtColor(frame, gray, CV_BGR2GRAY);
		equalizeHist(gray, gray);
		int * pResults = NULL;
		int x, y;
		unsigned char * pBuffer = (unsigned char *)malloc(DETECT_BUFFER_SIZE);

		pResults = facedetect_multiview_reinforce(pBuffer, gray.data, gray.cols, gray.rows, (int)gray.step,
		1.2f, 2, 10,0);
		//results = detect(src.data, src.cols, src.rows, src.step, 1.2f, 2, 10, 0);
		//printf("%d faces detected.\n", (pResults ? *pResults : 0));//重复运行
		//print the detection results

		for (int i = 0; i < (pResults ? *pResults : 0); i++)
		{
		short *p = NULL;
		p = ((short*)(pResults + 1)) + 6 * i;
		x = p[0];
		y = p[1];
		int w = p[2];
		int h = p[3];
		int neighbors = p[4];
		int angle = p[5];

		//printf("face_rect=[%d, %d, %d, %d], neighbors=%d, angle=%d\n", x, y, w, h, neighbors, angle);
		fprintf(stderr, "faces_num: %d, face_rect=[%d, %d, %d, %d], neighbors=%d, angle=%d\n",
		*pResults, x, y, w, h, neighbors, angle);


		/*********************************/
		//Point left(x, y);
		//Point right(x + w, y + h);
		//rectangle(frame, left, right, Scalar(230, 255, 0), 4);
		rectangle(result_frontal, Rect(x, y, w, h), Scalar(0, 0, 150), 2);

		faceROI = gray(Rect(x, y, w, h / 2));
		//-- 在脸中检测眼睛
		eyes_cascade.detectMultiScale(faceROI, eyes, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));

		for (size_t j = 0; j < eyes.size(); j++)
		{
			Point eye_center(x + eyes[j].x + eyes[j].width / 2, y + eyes[j].y + eyes[j].height / 2);
			int radius = cvRound((eyes[j].width + eyes[j].height)*0.25);
			circle(result_frontal, eye_center, radius, Scalar(0, 0, 200), 3, 8, 0);
			printf("OK_%d\n", j);
			//putText(result_frontal, "TEST", cvPoint(0, 25), &font, CV_RGB(255, 0, 0));
			string text = "A.W.A.K.E";
			Point pt(50, 100);
			Scalar color = CV_RGB(0, 0, 255);
			//putText(result_frontal, text, pt, CV_FONT_HERSHEY_SCRIPT_SIMPLEX, 2.5f, color);
			putText(result_frontal, text, Point(int(result_frontal.cols*0.1), int(result_frontal.rows*0.9)),
				CV_FONT_HERSHEY_DUPLEX, result_frontal.cols / 300, cvScalar(255, 0, 0, 0), 3);
			flag = 0;

		}
		if (!eyes.size())
		{
			flag += 1;
			if (flag>30 && flag<120)
			{
				string text = "S.L.E.E.PING";
				Point pt(50, 100);
				Scalar color = CV_RGB(255, 0, 0);
				//putText(result_frontal, text, pt, CV_FONT_HERSHEY_SCRIPT_SIMPLEX, 2.5f, color);
				putText(result_frontal, text, Point(int(result_frontal.cols*0.1), int(result_frontal.rows*0.9)),
					CV_FONT_HERSHEY_DUPLEX, result_frontal.cols / 300, cvScalar(0, 255, 0, 0), 3);//b,g,r
			}
			else if (flag >= 120)
			{
				string text = "DEEP.S.L.E.E.P";
				Point pt(50, 100);
				Scalar color = CV_RGB(255, 0, 0);
				//putText(result_frontal, text, pt, CV_FONT_HERSHEY_SCRIPT_SIMPLEX, 2.5f, color);
				putText(result_frontal, text, Point(int(result_frontal.cols*0.1), int(result_frontal.rows*0.9)),
					CV_FONT_HERSHEY_DUPLEX, result_frontal.cols / 300, cvScalar(0, 0, 255, 0), 3);
			}
			else
			{
				string text = "A.W.A.K.E";
				Point pt(50, 100);
				Scalar color = CV_RGB(0, 0, 255);
				//putText(result_frontal, text, pt, CV_FONT_HERSHEY_SCRIPT_SIMPLEX, 2.5f, color);
				putText(result_frontal, text, Point(int(result_frontal.cols*0.1), int(result_frontal.rows*0.9)),
					CV_FONT_HERSHEY_DUPLEX, result_frontal.cols / 300, cvScalar(255, 0, 0, 0), 3);

			}

		}
	}



	imshow("ss", result_frontal);
	//}

}

int main(void)
{
	VideoCapture cap(0);
	//VideoCapture cap(1);
	Mat frame;
	if (!eyes_cascade.load(eyes_cascade_name)) { printf("--(!)Error loading\n"); return -1; };
	while (1)
	{
		//load an image and convert it to gray (single-channel)
		//Mat gray = imread("lena.png");//it is necessary that must have CV_LOAD_IMAGE_GRAYSCALE
		//cvtColor(gray, gray, CV_BGR2GRAY);//CV_LOAD_IMAGE_GRAYSCALE IS SAME AS CV_BGR2GRAY
		cap >> frame;
		if (!frame.empty())
		{

			detectAndDisplay(frame);
		}
		int c = waitKey(10);
		if ((char)c == 'c') { break; }
	}

}