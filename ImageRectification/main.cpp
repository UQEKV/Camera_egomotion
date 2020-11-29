//
//  main.cpp
//  rectification
//
//  Created by Jiangqiu chen on 10.02.20.
//  Copyright © 2020 Jiangqiu chen. All rights reserved.
//

#include <opencv2/highgui/highgui_c.h>
#include <opencv/cv.h>
#include <opencv2/core/core_c.h>
#include "CalextParam.h"
#include "math.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <dirent.h>

using namespace cv;
using namespace std;


int main(int argc, const char * argv[]) {
//    ASupPoint3D stHmi3D;
    ASupPoint2D stHmi2D;

    ASupPoint3D stHmi3DVir;
    ASupPoint2D stHmi2DVir;

//    AVision hmiParam;

    // = cvLoadImage("E:\\VanishLine\\28.png");
    

    AVision param;

    AVision VirParam;

//    float deltaRx = 0;
//    float deltaRy = 0;

    param.height = 1208;
    param.width = 1920;
    param.type = AE_CAM_TYPE_WIDEVIEW;

    IplImage* undistorImage = cvCreateImage(cvSize(1920, 1208), 8, 3);


    param.param.intParam.wParam.cx = 955.774;
    param.param.intParam.wParam.cy = 656.288;
    param.param.intParam.wParam.fx = 1844.712;
    param.param.intParam.wParam.fy = 1840.831;
    param.param.intParam.wParam.k1 = -3.01248e-01;
    param.param.intParam.wParam.k2 = 1.31695e-01;
    param.param.intParam.wParam.k3 = 0;
    param.param.intParam.wParam.p1 = -1.877e-03;
    param.param.intParam.wParam.p2 = -2.48e-04;

    param.param.extParam.rx = 4.0+0.065;// 4.2543;//-5.14888;// 0.013;//0.9166;//-5.201;// -7.9863;//-24.3756;
    param.param.extParam.ry = 4.1;// 4.1287;//-0.2855;// -0.764293;// -23.2627;//-21.6973;//-1.2736;//-56.5748;//-56.8538;
    param.param.extParam.rz = -0.543;// -0.543;//-0.114;//0.5356;// 0.53202;// 1.936487;//1.1541;//-0.1474;// 3.1047;// 2.9492;// 1.8635;//0.59;//-25.7819;



    param.param.extParam.tx = 0;
    param.param.extParam.ty = 1280;
    param.param.extParam.tz = 0;// 1740;//2.5717

    VirParam.type = AE_CAM_TYPE_PLANAR;

    VirParam.param.intParam.pParam.cx = param.param.intParam.wParam.cx;
    VirParam.param.intParam.pParam.cy = param.param.intParam.wParam.cy;
    VirParam.param.intParam.pParam.fx = param.param.intParam.wParam.fx;
    VirParam.param.intParam.pParam.fy = param.param.intParam.wParam.fy;

    VirParam.param.extParam.rx = 0;
    VirParam.param.extParam.ry = 0;
    VirParam.param.extParam.rz = 0;
    VirParam.param.extParam.tx = 0;
    VirParam.param.extParam.ty = param.param.extParam.ty;
    VirParam.param.extParam.tz = 0;

    short srcX, srcY;
    float fsrcX, fsrcY;

    float a1, a2, a3, a4;
    CvCapture* cap =cvCreateFileCapture("/Users/jiangqiuchen/Desktop/Work/human_horizon_ADAS /ego-motion-data/Record_2019-03-22_08-04-51_0.mkv");
    IplImage* calibrateImage;
    //cvSetCaptureProperty(cap, CV_CAP_PROP_POS_FRAMES, 14806);
    double rate = cvGetCaptureProperty(cap,CV_CAP_PROP_FPS );
    printf("frame rate: %f\n",rate);//capture.get(CAP_PROP_FPS);
    //    cout << "帧率为:" << rate << endl;
    int minute1 ;
    int second1 ;
    int minute2 ;
    int second2 ;
    
    printf("请输入开始时间：");
    scanf("%d, %d",&minute1,&second1);
    printf("请输入结束时间：");
    scanf("%d, %d",&minute2,&second2);
    printf("Video rectification from %d:%d to %d:%d\n",minute1,second1,minute2,second2 );
    
    int frameToStart=minute1*60*rate+second1*rate-10;
//    cvSetCaptureProperty(cap, CV_CAP_PROP_POS_FRAMES, frameToStart);
    int frameToStop=minute2*60*rate+second2*rate+10;
    
    int frameID =1 ;
    char path[128];
    ;
    while ((calibrateImage = cvQueryFrame(cap)) != NULL) {

        if (frameID >= frameToStart && frameID <= frameToStop) {
            //cvShowImage("win", src);
            for (int jj = 0; jj < undistorImage->height; jj++) {
                for (int ii = 0; ii < undistorImage->width; ii++) {
    
                    stHmi2DVir.fX = ii;
                    stHmi2DVir.fY = jj;
    
    //                if (ii == 300 && jj == 300)
    //                    printf("break point\n");
    
                    aaCamTo3D(&stHmi3DVir, &stHmi2DVir, &VirParam);
    
                    aa3DToCam(&stHmi2D, &stHmi3DVir, &param);
    
    
                    fsrcX = stHmi2D.fX;
                    fsrcY = stHmi2D.fY;
    
                    srcX = (short)(fsrcX);
                    srcY = (short)(fsrcY);
    
                    a1 = (1.0 - (fsrcX - srcX)) * (1.0 - (fsrcY - srcY));
                    a2 = (fsrcX - srcX) * (1.0 - (fsrcY - srcY));
                    a3 = (1.0 - (fsrcX - srcX)) * (fsrcY - srcY);
                    a4 = (fsrcX - srcX) * (fsrcY - srcY);
    
                    if (srcX > 0 && srcX < calibrateImage->width-1 && srcY > 0 && srcY < calibrateImage->height-1) {
    
                        undistorImage->imageData[jj* undistorImage->widthStep + ii * 3 + 0] = (char)(((unsigned char)calibrateImage->imageData[srcY* calibrateImage->widthStep + srcX * 3 + 0]) * a1 + ((unsigned char)calibrateImage->imageData[srcY* calibrateImage->widthStep + (srcX + 1) * 3 + 0])*a2 + ((unsigned char)calibrateImage->imageData[(srcY + 1)* calibrateImage->widthStep + srcX * 3 + 0])*a3 + ((unsigned char)calibrateImage->imageData[(srcY + 1)* calibrateImage->widthStep + (srcX + 1) * 3 + 0])*a4);
                        undistorImage->imageData[jj* undistorImage->widthStep + ii * 3 + 1] = (char)(((unsigned char)calibrateImage->imageData[srcY* calibrateImage->widthStep + srcX * 3 + 1]) * a1 + ((unsigned char)calibrateImage->imageData[srcY* calibrateImage->widthStep + (srcX + 1) * 3 + 1]) * a2 + ((unsigned char)calibrateImage->imageData[(srcY + 1)* calibrateImage->widthStep + srcX * 3 + 1]) * a3 + ((unsigned char)calibrateImage->imageData[(srcY + 1)* calibrateImage->widthStep + (srcX + 1) * 3 + 1]) * a4);
                        undistorImage->imageData[jj* undistorImage->widthStep + ii * 3 + 2] = (char)(((unsigned char)calibrateImage->imageData[srcY* calibrateImage->widthStep + srcX * 3 + 2]) * a1 + ((unsigned char)calibrateImage->imageData[srcY* calibrateImage->widthStep + (srcX + 1) * 3 + 2]) * a2 + ((unsigned char)calibrateImage->imageData[(srcY + 1)* calibrateImage->widthStep + srcX * 3 + 2]) * a3 + ((unsigned char)calibrateImage->imageData[(srcY + 1)* calibrateImage->widthStep + (srcX + 1) * 3 + 2]) * a4);
                        //undistorImage->imageData[jj* undistorImage->widthStep + ii * 3 + 0] = (char)(((unsigned char)calibrateImage->imageData[srcY* calibrateImage->widthStep + srcX * 3 + 0]));
                        //undistorImage->imageData[jj* undistorImage->widthStep + ii * 3 + 1] = (char)(((unsigned char)calibrateImage->imageData[srcY* calibrateImage->widthStep + srcX * 3 + 1]));
                        //undistorImage->imageData[jj* undistorImage->widthStep + ii * 3 + 2] = (char)(((unsigned char)calibrateImage->imageData[srcY* calibrateImage->widthStep + srcX * 3 + 2]));
    
                            }
                         }
                     }
    
//                cvReleaseImage(&calibrateImage);
                sprintf(path, "%s%d.png","/Users/jiangqiuchen/Desktop/Work/human_horizon_ADAS /ego-motion-data/allPicture/", frameID);
                printf("%s",path);
                cvSaveImage(path, undistorImage);
                cvZero(undistorImage);
                
//            cvSaveImage(path, src);
            //cvWaitKey(0);
        }
        printf("%d\n",frameID);
        //usleep(10);
        frameID++;
        if ( frameID > frameToStop  ){
                    return -1;
                }
    }

    calibrateImage = cvQueryFrame(cap);



    return 0;
}

//int main(int argc, const char * argv[]) {
//    ASupPoint3D stHmi3D;
//    ASupPoint2D stHmi2D;
//
//    ASupPoint3D stHmi3DVir;
//    ASupPoint2D stHmi2DVir;
//
//    AVision hmiParam;
//
//    IplImage* calibrateImage;// = cvLoadImage("E:\\VanishLine\\28.png");
//
//
//    AVision param;
//
//    AVision VirParam;
//
//    float deltaRx = 0;
//    float deltaRy = 0;
//
//    param.height = 1208;
//    param.width = 1920;
//    param.type = AE_CAM_TYPE_WIDEVIEW;
//
//    IplImage* undistorImage = cvCreateImage(cvSize(1920, 1208), 8, 3);
//
//
//    param.param.intParam.wParam.cx = 955.774;
//    param.param.intParam.wParam.cy = 656.288;
//    param.param.intParam.wParam.fx = 1844.712;
//    param.param.intParam.wParam.fy = 1840.831;
//    param.param.intParam.wParam.k1 = -3.01248e-01;
//    param.param.intParam.wParam.k2 = 1.31695e-01;
//    param.param.intParam.wParam.k3 = 0;
//    param.param.intParam.wParam.p1 = -1.877e-03;
//    param.param.intParam.wParam.p2 = -2.48e-04;
//
//    param.param.extParam.rx = 4.0+0.065;// 4.2543;//-5.14888;// 0.013;//0.9166;//-5.201;// -7.9863;//-24.3756;
//    param.param.extParam.ry = 4.1;// 4.1287;//-0.2855;// -0.764293;// -23.2627;//-21.6973;//-1.2736;//-56.5748;//-56.8538;
//    param.param.extParam.rz = -0.543;// -0.543;//-0.114;//0.5356;// 0.53202;// 1.936487;//1.1541;//-0.1474;// 3.1047;// 2.9492;// 1.8635;//0.59;//-25.7819;
//
//
//
//    param.param.extParam.tx = 0;
//    param.param.extParam.ty = 1280;
//    param.param.extParam.tz = 0;// 1740;//2.5717
//
//    VirParam.type = AE_CAM_TYPE_PLANAR;
//
//    VirParam.param.intParam.pParam.cx = param.param.intParam.wParam.cx;
//    VirParam.param.intParam.pParam.cy = param.param.intParam.wParam.cy;
//    VirParam.param.intParam.pParam.fx = param.param.intParam.wParam.fx;
//    VirParam.param.intParam.pParam.fy = param.param.intParam.wParam.fy;
//
//    VirParam.param.extParam.rx = 0;
//    VirParam.param.extParam.ry = 0;
//    VirParam.param.extParam.rz = 0;
//    VirParam.param.extParam.tx = 0;
//    VirParam.param.extParam.ty = param.param.extParam.ty;
//    VirParam.param.extParam.tz = 0;
//
//    short srcX, srcY;
//    float fsrcX, fsrcY;
//
//    float a1, a2, a3, a4;
//
//
//
//    struct dirent *dirp;
//
//    DIR* dir = opendir("/Users/jiangqiuchen/Desktop/human_horizon_ADAS /real_pic/5DATA/1.1.36/croptxt");
//
//    while ((dirp = readdir(dir)) != nullptr) {
//        if (dirp->d_type == DT_REG) {
//            // 文件
//            printf("%s\n", dirp->d_name);
//
//        } else if (dirp->d_type == DT_DIR) {
//            // 文件夹
//        }
//    }
//
//closedir(dir);
//
//   do
////    {
////        // \BA\F6\C2\D4"."\BA\CD".."\C1\BD\B8\F6\BD\E1\B9\FB
////        if (strcmp(findData.cFileName, ".") == 0 || strcmp(findData.cFileName, "..") == 0)
////            continue;
////        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)    // \CAǷ\F1\CA\C7Ŀ¼
////        {
////            //cout << findData.cFileName << "\t<dir>\n";
////        }
////        else
////        {
////            size.LowPart = findData.nFileSizeLow;
////            size.HighPart = findData.nFileSizeHigh;
////            //cout << findData.cFileName << "\t" << size.QuadPart << " bytes\n";
////            printf("%s\n", findData.cFileName);
////
////            sprintf(path, "%s%s", argv[1], findData.cFileName);
////            sprintf(spath, "%s\\result\\%s-correct.png", argv[1], findData.cFileName);
////
////            calibrateImage = cvLoadImage(path);
////
////
////            deltaY =  tan(param.param.extParam.rx*3.1415926 / 180) * param.param.intParam.wParam.fy;
//
//
//            //main undistor image code
//            for (int jj = 0; jj < undistorImage->height; jj++) {
//                for (int ii = 0; ii < undistorImage->width; ii++) {
//
//                    stHmi2DVir.fX = ii;
//                    stHmi2DVir.fY = jj;
//
//                    if (ii == 300 && jj == 300)
//                        printf("break point\n");
//
//                    aaCamTo3D(&stHmi3DVir, &stHmi2DVir, &VirParam);
//
//                    aa3DToCam(&stHmi2D, &stHmi3DVir, &param);
//
//
//                    fsrcX = stHmi2D.fX;
//                    fsrcY = stHmi2D.fY;
//
//                    srcX = (short)(fsrcX);
//                    srcY = (short)(fsrcY);
//
//                    a1 = (1.0 - (fsrcX - srcX)) * (1.0 - (fsrcY - srcY));
//                    a2 = (fsrcX - srcX) * (1.0 - (fsrcY - srcY));
//                    a3 = (1.0 - (fsrcX - srcX)) * (fsrcY - srcY);
//                    a4 = (fsrcX - srcX) * (fsrcY - srcY);
//
//                    if (srcX > 0 && srcX < calibrateImage->width-1 && srcY > 0 && srcY < calibrateImage->height-1) {
//
//                        undistorImage->imageData[jj* undistorImage->widthStep + ii * 3 + 0] = (char)(((unsigned char)calibrateImage->imageData[srcY* calibrateImage->widthStep + srcX * 3 + 0]) * a1 + ((unsigned char)calibrateImage->imageData[srcY* calibrateImage->widthStep + (srcX + 1) * 3 + 0])*a2 + ((unsigned char)calibrateImage->imageData[(srcY + 1)* calibrateImage->widthStep + srcX * 3 + 0])*a3 + ((unsigned char)calibrateImage->imageData[(srcY + 1)* calibrateImage->widthStep + (srcX + 1) * 3 + 0])*a4);
//                        undistorImage->imageData[jj* undistorImage->widthStep + ii * 3 + 1] = (char)(((unsigned char)calibrateImage->imageData[srcY* calibrateImage->widthStep + srcX * 3 + 1]) * a1 + ((unsigned char)calibrateImage->imageData[srcY* calibrateImage->widthStep + (srcX + 1) * 3 + 1]) * a2 + ((unsigned char)calibrateImage->imageData[(srcY + 1)* calibrateImage->widthStep + srcX * 3 + 1]) * a3 + ((unsigned char)calibrateImage->imageData[(srcY + 1)* calibrateImage->widthStep + (srcX + 1) * 3 + 1]) * a4);
//                        undistorImage->imageData[jj* undistorImage->widthStep + ii * 3 + 2] = (char)(((unsigned char)calibrateImage->imageData[srcY* calibrateImage->widthStep + srcX * 3 + 2]) * a1 + ((unsigned char)calibrateImage->imageData[srcY* calibrateImage->widthStep + (srcX + 1) * 3 + 2]) * a2 + ((unsigned char)calibrateImage->imageData[(srcY + 1)* calibrateImage->widthStep + srcX * 3 + 2]) * a3 + ((unsigned char)calibrateImage->imageData[(srcY + 1)* calibrateImage->widthStep + (srcX + 1) * 3 + 2]) * a4);
//                        //undistorImage->imageData[jj* undistorImage->widthStep + ii * 3 + 0] = (char)(((unsigned char)calibrateImage->imageData[srcY* calibrateImage->widthStep + srcX * 3 + 0]));
//                        //undistorImage->imageData[jj* undistorImage->widthStep + ii * 3 + 1] = (char)(((unsigned char)calibrateImage->imageData[srcY* calibrateImage->widthStep + srcX * 3 + 1]));
//                        //undistorImage->imageData[jj* undistorImage->widthStep + ii * 3 + 2] = (char)(((unsigned char)calibrateImage->imageData[srcY* calibrateImage->widthStep + srcX * 3 + 2]));
//
//                    }
//                 }
//              }
//
//            cvReleaseImage(&calibrateImage);
//            cvSaveImage(spath, undistorImage);
//            cvZero(undistorImage);
////        }
////    } while (FindNextFile(hFind, &findData));
//
//
//
//
//    //cvWaitKey(0);
//
//    return 0;
//}
//
