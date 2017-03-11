#include <opencv.hpp>
#include "facedetect-dll.h"
#pragma comment(lib,"libfacedetect.lib")
#define DETECT_BUFFER_SIZE 0x20000
using namespace cv;
void detectAndDisplay(Mat frame)
{
	Mat gray;
	cvtColor(frame, gray, CV_BGR2GRAY);
	int * pResults = NULL;
	unsigned char * pBuffer = (unsigned char *)malloc(DETECT_BUFFER_SIZE);
	/*pResults = facedetect_frontal_surveillance((unsigned char*)(gray.ptr(0)), gray.cols, gray.rows, gray.step,
		1.2f, 5, 24);*/
	pResults = facedetect_frontal_surveillance(pBuffer, (unsigned char*)(gray.ptr(0)), gray.cols, gray.rows, (int)gray.step,
		1.2f, 2, 48, 0, 1);
	printf("%d faces detected.\n", (pResults ? *pResults : 0));//÷ÿ∏¥‘À––
															   //print the detection results
	for (int i = 0; i < (pResults ? *pResults : 0); i++)
	{

		short * p = ((short*)(pResults + 1)) + 6 * i;
		int x = p[0];
		int y = p[1];
		int w = p[2];
		int h = p[3];
		int neighbors = p[4];

		printf("face_rect=[%d, %d, %d, %d], neighbors=%d\n", x, y, w, h, neighbors);
		Point left(x, y);
		Point right(x + w, y + h);
		rectangle(frame, left, right, Scalar(230, 255, 0), 4);

	}
	imshow("ss", frame);
}

int main(void)
{
	VideoCapture cap(1);
	Mat frame;
	
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