//#include "stdafx.h"
#include <opencv2/highgui/highgui_c.h>
#include <opencv/cv.h>
#include <opencv2/core/core_c.h>
#include "CalextParam.h"
#include "math.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <dirent.h>

#define SAVE_VIDEO	(0)





//void saveVideoImage(void) {
//
//	CvCapture* cap =cvCreateFileCapture("/Users/jiangqiuchen/Desktop/human_horizon_ADAS /ego-motion-data/Record_2019-03-22_08-04-51_0.mkv");
//
//	//cvSetCaptureProperty(cap, CV_CAP_PROP_POS_FRAMES, 14806);
//
//	IplImage* src;
//
//	int frameID = 0;
//	char path[128];
//
//	while ((src = cvQueryFrame(cap)) != NULL) {
//
//		if (frameID >= 48 && frameID <= 89) {
//			//cvShowImage("win", src);
//			sprintf(path, "%s%d.png","/Users/jiangqiuchen/Desktop/human_horizon_ADAS /ego-motion-data/0.01-0.04_rectified/", frameID);
//			cvSaveImage(path, src);
//
//			//cvWaitKey(0);
//		}
//		printf("%d\n",frameID);
//		//usleep(10);
//		frameID++;
//	}
//
//	src = cvQueryFrame(cap);
//
//
//
//}

//int main(int argc,char* argv[]) {
//
//
//	ASupPoint3D stHmi3D;
//	ASupPoint2D stHmi2D;
//
//	ASupPoint3D stHmi3DVir;
//	ASupPoint2D stHmi2DVir;
//
//	AVision hmiParam;
//
//	IplImage* calibrateImage;// = cvLoadImage("E:\\VanishLine\\28.png");
//
//
//	AVision param;
//
//	AVision VirParam;
//
//	float deltaRx = 0;
//	float deltaRy = 0;
//
//	param.height = 1208;
//	param.width = 1920;
//	param.type = AE_CAM_TYPE_WIDEVIEW;
//
//	IplImage* undistorImage = cvCreateImage(cvSize(1920, 1208), 8, 3);
//
//
//	param.param.intParam.wParam.cx = 955.774;
//	param.param.intParam.wParam.cy = 656.288;
//	param.param.intParam.wParam.fx = 1844.712;
//	param.param.intParam.wParam.fy = 1840.831;
//	param.param.intParam.wParam.k1 = -3.01248e-01;
//	param.param.intParam.wParam.k2 = 1.31695e-01;
//	param.param.intParam.wParam.k3 = 0;
//	param.param.intParam.wParam.p1 = -1.877e-03;
//	param.param.intParam.wParam.p2 = -2.48e-04;
//
//	param.param.extParam.rx = 4.0+0.065;// 4.2543;//-5.14888;// 0.013;//0.9166;//-5.201;// -7.9863;//-24.3756;
//	param.param.extParam.ry = 4.1;// 4.1287;//-0.2855;// -0.764293;// -23.2627;//-21.6973;//-1.2736;//-56.5748;//-56.8538;
//	param.param.extParam.rz = -0.543;// -0.543;//-0.114;//0.5356;// 0.53202;// 1.936487;//1.1541;//-0.1474;// 3.1047;// 2.9492;// 1.8635;//0.59;//-25.7819;
//
//
//
//	param.param.extParam.tx = 0;
//	param.param.extParam.ty = 1280;
//	param.param.extParam.tz = 0;// 1740;//2.5717
//
//	VirParam.type = AE_CAM_TYPE_PLANAR;
//
//	VirParam.param.intParam.pParam.cx = param.param.intParam.wParam.cx;
//	VirParam.param.intParam.pParam.cy = param.param.intParam.wParam.cy;
//	VirParam.param.intParam.pParam.fx = param.param.intParam.wParam.fx;
//	VirParam.param.intParam.pParam.fy = param.param.intParam.wParam.fy;
//
//	VirParam.param.extParam.rx = 0;
//	VirParam.param.extParam.ry = 0;
//	VirParam.param.extParam.rz = 0;
//	VirParam.param.extParam.tx = 0;
//	VirParam.param.extParam.ty = param.param.extParam.ty;
//	VirParam.param.extParam.tz = 0;
//
//	short srcX, srcY;
//	float fsrcX, fsrcY;
//
//	float a1, a2, a3, a4;
////
////	float angleDelta[] = { 0.0f,0.006,0.0f,-0.007,0.0f,0.006,0.0f,-0.008,0.0f,-0.008 };
////
////	int deltaY = tan(0.1*3.1415926/180) * 1834;
////	deltaY = 0;
////
////
////	HANDLE hFind;
////	WIN32_FIND_DATA findData;
////	LARGE_INTEGER size;
////
////	char dir[256];
////
////	sprintf(dir,"%s*.*",argv[1]);
////
////	int wNum = atoi(argv[2]);
////	int hNum = atoi(argv[3]);
////
////	char path[256];
////	char spath[256];
////
////	int count = 0;
////
////	stHmi2DVir.fX = /*945;*/912;
////	stHmi2DVir.fY = /*925;*/ 1056;
////
////	aaCamTo3D(&stHmi3DVir, &stHmi2DVir, &param);
////
////	int coorDis[][2] = { 731,	646,
////		1062,	551,
////		1122,	537,
////		460	,646,
////		965,	554,
////		1064,	537,
////		341,	641,
////		917,	554,
////		1035,	539,
////	};
////
////	FILE* fp = fopen("D:\\aaaaa.txt", "w");
////
////	for (int b = 0; b < sizeof(coorDis) / (sizeof(int)*2); b ++) {
////
////		stHmi2DVir.fX = coorDis[b][0];
////		stHmi2DVir.fY = coorDis[b][1];
////
////		aaCamTo3D(&stHmi3DVir, &stHmi2DVir, &param);
////
////		fprintf(fp, "%f,%f\n", stHmi3DVir.fX-937.5, stHmi3DVir.fZ +1300);
////
////	}
////
////	fclose(fp);
////
////
////
////
////	stHmi3DVir.fX = -3000;
////	stHmi3DVir.fY = 731;
////	stHmi3DVir.fZ = 30000-1300;
////
////	aa3DToCam(&stHmi2D, &stHmi3DVir, &param);
////
////	aaCamTo3D(&stHmi3DVir, &stHmi2D, &param);
////
////	stHmi3DVir.fX = -0.4159;
////	stHmi3DVir.fY = 0.005132;
////	stHmi3DVir.fZ = 1;
////
////	aa3DToCam(&stHmi2D, &stHmi3DVir, &param);
////
////	printf("\n");
////
////	param.mDashboardRowInPixel = 0;
////	int videoCount = 0;
////	hFind = FindFirstFile(dir, &findData);
////	if (hFind == INVALID_HANDLE_VALUE)
////	{
////		return 0;
////	}
////	do
////	{
////		// \BA\F6\C2\D4"."\BA\CD".."\C1\BD\B8\F6\BD\E1\B9\FB
////		if (strcmp(findData.cFileName, ".") == 0 || strcmp(findData.cFileName, "..") == 0)
////			continue;
////		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)    // \CAǷ\F1\CA\C7Ŀ¼
////		{
////			//cout << findData.cFileName << "\t<dir>\n";
////		}
////		else
////		{
////			size.LowPart = findData.nFileSizeLow;
////			size.HighPart = findData.nFileSizeHigh;
////			//cout << findData.cFileName << "\t" << size.QuadPart << " bytes\n";
////			printf("%s\n", findData.cFileName);
////
////			sprintf(path, "%s%s", argv[1], findData.cFileName);
////			sprintf(spath, "%s\\result\\%s-correct.png", argv[1], findData.cFileName);
////
////			calibrateImage = cvLoadImage(path);
////
////
////			deltaY =  tan(param.param.extParam.rx*3.1415926 / 180) * param.param.intParam.wParam.fy;
//
//
//			//main undistor image code
//			for (int jj = 0; jj < undistorImage->height; jj++) {
//				for (int ii = 0; ii < undistorImage->width; ii++) {
//
//					stHmi2DVir.fX = ii;
//					stHmi2DVir.fY = jj;
//
//					if (ii == 300 && jj == 300)
//						printf("break point\n");
//
//					aaCamTo3D(&stHmi3DVir, &stHmi2DVir, &VirParam);
//
//					aa3DToCam(&stHmi2D, &stHmi3DVir, &param);
//
//
//					fsrcX = stHmi2D.fX;
//					fsrcY = stHmi2D.fY;
//
//					srcX = (short)(fsrcX);
//					srcY = (short)(fsrcY);
//
//					a1 = (1.0 - (fsrcX - srcX)) * (1.0 - (fsrcY - srcY));
//					a2 = (fsrcX - srcX) * (1.0 - (fsrcY - srcY));
//					a3 = (1.0 - (fsrcX - srcX)) * (fsrcY - srcY);
//					a4 = (fsrcX - srcX) * (fsrcY - srcY);
//
//					if (srcX > 0 && srcX < calibrateImage->width-1 && srcY > 0 && srcY < calibrateImage->height-1) {
//
//						undistorImage->imageData[jj* undistorImage->widthStep + ii * 3 + 0] = (char)(((unsigned char)calibrateImage->imageData[srcY* calibrateImage->widthStep + srcX * 3 + 0]) * a1 + ((unsigned char)calibrateImage->imageData[srcY* calibrateImage->widthStep + (srcX + 1) * 3 + 0])*a2 + ((unsigned char)calibrateImage->imageData[(srcY + 1)* calibrateImage->widthStep + srcX * 3 + 0])*a3 + ((unsigned char)calibrateImage->imageData[(srcY + 1)* calibrateImage->widthStep + (srcX + 1) * 3 + 0])*a4);
//						undistorImage->imageData[jj* undistorImage->widthStep + ii * 3 + 1] = (char)(((unsigned char)calibrateImage->imageData[srcY* calibrateImage->widthStep + srcX * 3 + 1]) * a1 + ((unsigned char)calibrateImage->imageData[srcY* calibrateImage->widthStep + (srcX + 1) * 3 + 1]) * a2 + ((unsigned char)calibrateImage->imageData[(srcY + 1)* calibrateImage->widthStep + srcX * 3 + 1]) * a3 + ((unsigned char)calibrateImage->imageData[(srcY + 1)* calibrateImage->widthStep + (srcX + 1) * 3 + 1]) * a4);
//						undistorImage->imageData[jj* undistorImage->widthStep + ii * 3 + 2] = (char)(((unsigned char)calibrateImage->imageData[srcY* calibrateImage->widthStep + srcX * 3 + 2]) * a1 + ((unsigned char)calibrateImage->imageData[srcY* calibrateImage->widthStep + (srcX + 1) * 3 + 2]) * a2 + ((unsigned char)calibrateImage->imageData[(srcY + 1)* calibrateImage->widthStep + srcX * 3 + 2]) * a3 + ((unsigned char)calibrateImage->imageData[(srcY + 1)* calibrateImage->widthStep + (srcX + 1) * 3 + 2]) * a4);
//						//undistorImage->imageData[jj* undistorImage->widthStep + ii * 3 + 0] = (char)(((unsigned char)calibrateImage->imageData[srcY* calibrateImage->widthStep + srcX * 3 + 0]));
//						//undistorImage->imageData[jj* undistorImage->widthStep + ii * 3 + 1] = (char)(((unsigned char)calibrateImage->imageData[srcY* calibrateImage->widthStep + srcX * 3 + 1]));
//						//undistorImage->imageData[jj* undistorImage->widthStep + ii * 3 + 2] = (char)(((unsigned char)calibrateImage->imageData[srcY* calibrateImage->widthStep + srcX * 3 + 2]));
//
//					}
//				 }
//			  }
//
//			cvReleaseImage(&calibrateImage);
//			cvSaveImage(spath, undistorImage);
//			cvZero(undistorImage);
////		}
////	} while (FindNextFile(hFind, &findData));
//
//
//
//
//	//cvWaitKey(0);
//
//	return 0;
//}
