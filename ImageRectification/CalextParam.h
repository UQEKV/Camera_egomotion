#pragma once
#ifndef _CALEXTPARAM_H
#define _CALEXTPARAM_H

#define A_M2MM (1000)
#define A_PI (3.141592653)
#define MATRIX_ORDER 3
#define FLT_EPSILON      1.192092896e-07F        // smallest such that 1.0+FLT_EPSILON != 1.0
#define DA_DEPTH_SIGN      0x8000        // smallest such that 1.0+FLT_EPSILON != 1.0


typedef struct
{
	float fx;
	float fy;
	float cx;
	float cy;
} APlanarParam;

/**
* @brief Wide view camera intrinsic parameters.
*/
typedef struct
{
	float fx;
	float fy;
	float cx;
	float cy;
	float k1;
	float k2;
	float k3;
	float p1;
	float p2;
} AWideViewParam;

/**
* @brief Fish-eye camera intrinsic parameters.
*/
typedef struct
{
	float cx;
	float cy;
	float k1;
	float k3;
	float k5;
	float k7;
	float k9;
	float p1;
	float p2;
	float asp;
} AFisheyeParam;


typedef struct _tag_ANewFishParam {

	int 	invDistCoeffNum;
	float 	cx;
	float 	cy;
	float 	distCoeff[5];
	float 	invDistCoeff[15];
	float 	c;
	float 	d;
	float 	e;

}ANewFishParam;

typedef union
{
	APlanarParam pParam;
	AWideViewParam wParam;
	AFisheyeParam fParam;
	ANewFishParam	nfParam;
} ACamIntParam;


typedef struct
{
	int tx;
	int ty;
	int tz;
	float rx;
	float ry;
	float rz;
} ACamExtParam;



typedef struct
{
	float		fX;				/**< X position. */
	float		fY;				/**< Y position. */
	float		fZ;				/**< Z position. */
} ASupPoint3D;


typedef struct
{
	float		fX;				/**< X position. */
	float		fY;				/**< Y position. */
} ASupPoint2D;



typedef enum
{
	AE_IMAGE_GRAY = 0,		/**< 8 bit gray plane,1 channel. */
	AE_IMAGE_RGB = 1,		/**< 8 bit red plane,8 bit green plane,8 bit blue plane.3 channels. */
	AE_IMAGE_R = 2,			/**< 8 bit red plane.1 channel. */
	AE_IMAGE_NV12 = 3,		/**< 8-bit Y plane followed by an interleaved V/U plane with 2x2 subsampling */
	AE_IMAGE_NV21 = 4,		/**< 8-bit Y plane followed by an interleaved U/V plane with 2x2 subsampling */
	AE_IMAGE_YUY2 = 5,		/**< 8-bit Y plane, 8-bit U plane, 8-bit v plane, [Y U Y V] */
	AE_IMAGE_UYVY = 6,		/**< 8-bit Y plane, 8-bit U plane, 8-bit v plane, [U Y V Y] */
	AE_IMAGE_FORMAT_MAX
} AImgFormat;

typedef enum
{
	AE_CAM_TYPE_PLANAR = 0,
	AE_CAM_TYPE_WIDEVIEW = 1,
	AE_CAM_TYPE_FISHEYE = 2
} ACamType;

typedef struct
{
	ACamIntParam intParam;
	ACamExtParam extParam;
} ACalibration;

typedef struct
{
	int width;
	int height;
	int mDashboardRowInPixel;
	AImgFormat format;
	ACamType type;
	ACalibration param;
} AVision;

//typedef struct
//{
//	unsigned char	nChannels;      /**< The number of channels.                        */
//	unsigned char	depth;          /**< Pixel depth in bits, DA_DEPTH_8U only.        */
//	char		colorModel[4];  /**< Color model:"YUV", or "RGB".                   */
//	unsigned short	width;          /**< Image width in pixels.                         */
//	unsigned short	height;         /**< Image height in pixels.                        */
//	unsigned char*	imageData;     /**< Pointer to aligned image data.                 */
//	unsigned long	widthStep;      /**< Size of aligned image row in bytes.            */
//} daImage;


typedef struct
{
	ASupPoint2D dmat[7];
} DISmat;


int Calexparam(DISmat *dismat);
int CalDisLine(DISmat *dismat);
int CalDis(ASupPoint2D *point2D, ASupPoint3D* worldpt);

int aa3DToCam(ASupPoint2D* campt, ASupPoint3D* worldpt, const AVision* param);
int aaVectorToPoint2D(ASupPoint2D* campt, const ASupPoint3D* vec, const AVision* param);
int aaCamTo3D(ASupPoint3D* worldpt, const ASupPoint2D* campt, const AVision* param);

int newFish3D22D(ASupPoint2D* campt, ASupPoint3D* worldpt, AVision* param);
int newFish2D23D(ASupPoint3D* worldpt, ASupPoint2D* campt, AVision* param);

#endif
