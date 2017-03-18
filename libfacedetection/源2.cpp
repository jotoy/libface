//#include <opencv.hpp>
//#include "facedetect-dll.h"
//#pragma comment(lib,"libfacedetect.lib")
//#define DETECT_BUFFER_SIZE 0x20000
//using namespace cv;
//String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
//CascadeClassifier eyes_cascade;   //定义人眼分类器  
//void detectAndDisplay(Mat frame)
//{
//	Mat gray;
//	cvtColor(frame, gray, CV_BGR2GRAY);
//	int * pResults = NULL;
//	unsigned char * pBuffer = (unsigned char *)malloc(DETECT_BUFFER_SIZE);
//	/*pResults = facedetect_frontal_surveillance((unsigned char*)(gray.ptr(0)), gray.cols, gray.rows, gray.step,
//		1.2f, 5, 24);*/
//	pResults = facedetect_frontal_surveillance(pBuffer, (unsigned char*)(gray.ptr(0)), gray.cols, gray.rows, (int)gray.step,
//		1.2f, 2, 48, 0, 1);
//	printf("%d faces detected.\n", (pResults ? *pResults : 0));//重复运行
//															   //print the detection results
//	for (int i = 0; i < (pResults ? *pResults : 0); i++)
//	{
//
//		short * p = ((short*)(pResults + 1)) + 6 * i;
//		int x = p[0];
//		int y = p[1];
//		int w = p[2];
//		int h = p[3];
//		int neighbors = p[4];
//
//		printf("face_rect=[%d, %d, %d, %d], neighbors=%d\n", x, y, w, h, neighbors);
//		Point left(x, y);
//		Point right(x + w, y + h);
//		rectangle(frame, left, right, Scalar(230, 255, 0), 4);
//
//		Mat faceROI = frame(Rect(x, y, w, h));
//		std::vector<Rect> eyes;
//
//		//-- 在脸中检测眼睛
//		/*eyes_cascade.detectMultiScale(faceROI, eyes, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));
//
//		for (size_t j = 0; j < eyes.size(); j++)
//		{
//			Point eye_center(x + eyes[j].x + eyes[j].width / 2, y + eyes[j].y + eyes[j].height / 2);
//			int radius = cvRound((eyes[j].width + eyes[j].height)*0.25);
//			circle(frame, eye_center, radius, Scalar(255, 0, 0), 3, 8, 0);
//		}*/
//		/*for (;;)
//		{
//
//
//		}*/
//	}
//	imshow("ss", frame);
//}
//
//int main(void)
//{
//	VideoCapture cap(0);
//	//VideoCapture cap(1);
//	Mat frame;
//	//if (!eyes_cascade.load(eyes_cascade_name)) { printf("--(!)Error loading\n"); return -1; };
//	while (1)
//	{
//		//load an image and convert it to gray (single-channel)
//		//Mat gray = imread("lena.png");//it is necessary that must have CV_LOAD_IMAGE_GRAYSCALE
//		//cvtColor(gray, gray, CV_BGR2GRAY);//CV_LOAD_IMAGE_GRAYSCALE IS SAME AS CV_BGR2GRAY
//		cap >> frame;
//		if (!frame.empty())
//		{
//			detectAndDisplay(frame);
//		}
//		int c = waitKey(10);
//		if ((char)c == 'c') { break; }
//	}
//
//}