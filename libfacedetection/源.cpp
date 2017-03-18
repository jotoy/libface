#include <opencv.hpp>
#include "facedetect-dll.h"
#pragma comment(lib,"libfacedetect.lib")
#define DETECT_BUFFER_SIZE 0x20000
using namespace cv;
String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
int flag = 0;
CascadeClassifier eyes_cascade;   //定义人眼分类器  
void detectAndDisplay(Mat frame)
{

	/*std::vector<Rect> faces;

	for (int i = 0; i < faces.size(); i++) {*/
		CvFont font;
		cvInitFont(&font, CV_FONT_HERSHEY_COMPLEX, 1.0, 1.0, 0, 2, 8);
		Mat gray;
		Mat faceROI;// = frame(Rect(x, y, w, h));
		std::vector<Rect> eyes;
		cvtColor(frame, gray, CV_BGR2GRAY);
		equalizeHist(gray, gray);
		int * pResults = NULL;
		int x, y;
		unsigned char * pBuffer = (unsigned char *)malloc(DETECT_BUFFER_SIZE);
		
		pResults = facedetect_multiview_reinforce(pBuffer, gray.data, gray.cols, gray.rows, (int)gray.step,
			1.2f, 2, 48);
		//results = detect(src.data, src.cols, src.rows, src.step, 1.2f, 2, 10, 0);
		printf("%d faces detected.\n", (pResults ? *pResults : 0));//重复运行
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
			//Point left(x, y);
			//Point right(x + w, y + h);
			//rectangle(frame, left, right, Scalar(230, 255, 0), 4);
			rectangle(frame, Rect(x, y, w, h), Scalar(0, 255, 0), 2);
			/*	if (doLandmark)
				{
					for (int j = 0; j < 68; j++)
						circle(result_frontal_surveillance, Point((int)p[6 + 2 * j], (int)p[6 + 2 * j + 1]), 1, Scalar(0, 255, 0));
				}*/
			faceROI = gray(Rect(x, y, w, h/2));
			//-- 在脸中检测眼睛
				eyes_cascade.detectMultiScale(faceROI, eyes, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));

				for (size_t j = 0; j < eyes.size(); j++)
				{
					Point eye_center(x + eyes[j].x + eyes[j].width / 2, y + eyes[j].y + eyes[j].height / 2);
					int radius = cvRound((eyes[j].width + eyes[j].height)*0.25);
					circle(frame, eye_center, radius, Scalar(255, 0, 0), 3, 8, 0);
					printf("OK_%d\n",j);
					//putText(frame, "TEST", cvPoint(0, 25), &font, CV_RGB(255, 0, 0));
					string text = "A.W.A.K.E";
					Point pt(50, 100);
					Scalar color = CV_RGB(0, 0, 255);
					//putText(frame, text, pt, CV_FONT_HERSHEY_SCRIPT_SIMPLEX, 2.5f, color);
					putText(frame, text, Point(int(frame.cols*0.3), int(frame.rows*0.9)),
						CV_FONT_HERSHEY_DUPLEX, frame.cols / 300, cvScalar(255, 0, 0, 0), 3);
					flag = 0;

				}
				if (!eyes.size())
				{
					flag+=1;
					if (flag>30)
					{
						string text = "S.L.E.E.P";
						Point pt(50, 100);
						Scalar color = CV_RGB(255, 0, 0);
						//putText(frame, text, pt, CV_FONT_HERSHEY_SCRIPT_SIMPLEX, 2.5f, color);
						putText(frame, text, Point(int(frame.cols*0.3), int(frame.rows*0.9)),
							CV_FONT_HERSHEY_DUPLEX, frame.cols / 300, cvScalar(0, 0, 255, 0), 3);//b,g,r
					}
					else
					{
						string text = "A.W.A.K.E";
						Point pt(50, 100);
						Scalar color = CV_RGB(0, 0, 255);
						//putText(frame, text, pt, CV_FONT_HERSHEY_SCRIPT_SIMPLEX, 2.5f, color);
						putText(frame, text, Point(int(frame.cols*0.3), int(frame.rows*0.9)),
							CV_FONT_HERSHEY_DUPLEX, frame.cols / 300, cvScalar(255, 0, 0, 0), 3);
					}
					
				}
		}
		

		
		
		
		imshow("ss", frame);
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