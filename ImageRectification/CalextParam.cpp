//#include "stdafx.h"
#include"CalextParam.h"
#include"math.h"


static void GenerateRMatrix(const ACamExtParam* exParam, float RMatrix[3][3])
{
	//R = Rx*Ry*Rz
	float rx_rad = (float)((exParam->rx*A_PI) / 180.f);
	float ry_rad = (float)((exParam->ry*A_PI) / 180.f);
	float rz_rad = (float)((exParam->rz*A_PI) / 180.f);
	float cosRx = (float)cos(rx_rad);
	float sinRx = (float)sin(rx_rad);
	float cosRy = (float)cos(ry_rad);
	float sinRy = (float)sin(ry_rad);
	float cosRz = (float)cos(rz_rad);
	float sinRz = (float)sin(rz_rad);
	float sinRx_sinRy = sinRx * sinRy;
	float cosRx_sinRy = cosRx * sinRy;

	//zhangbo
	//RMatrix[0][0] = cosRy * cosRz;
	//RMatrix[0][1] = -cosRy * sinRz;
	//RMatrix[0][2] = sinRy;
	//RMatrix[1][0] = (sinRx_sinRy*cosRz) + (cosRx*sinRz);
	//RMatrix[1][1] = (-sinRx_sinRy*sinRz) + (cosRx*cosRz);
	//RMatrix[1][2] = -sinRx * cosRy;
	//RMatrix[2][0] = -(cosRx_sinRy*cosRz) + (sinRx*sinRz);
	//RMatrix[2][1] = (cosRx_sinRy*sinRz) + (sinRx*cosRz);
	//RMatrix[2][2] = cosRx * cosRy;

	//leige
	RMatrix[0][0] = cosRy * cosRz;
	RMatrix[0][1] = cosRy * sinRz;
	RMatrix[0][2] = -sinRy;
	RMatrix[1][0] = (sinRx_sinRy*cosRz) - (cosRx*sinRz);
	RMatrix[1][1] = (sinRx_sinRy*sinRz) + (cosRx*cosRz);
	RMatrix[1][2] = sinRx * cosRy;
	RMatrix[2][0] = (cosRx_sinRy*cosRz) + (sinRx*sinRz);
	RMatrix[2][1] = (cosRx_sinRy*sinRz) - (sinRx*cosRz);
	RMatrix[2][2] = cosRx * cosRy;
}

static void CoordinateConvert(const ASupPoint3D* src, ASupPoint3D* dst, const float R[3][3])
{
	//zhangbo
	//dst->fX = (R[0][0] * src->fX) + (R[1][0] * src->fY) + (R[2][0] * src->fZ);
	//dst->fY = (R[0][1] * src->fX) + (R[1][1] * src->fY) + (R[2][1] * src->fZ);
	//dst->fZ = (R[0][2] * src->fX) + (R[1][2] * src->fY) + (R[2][2] * src->fZ);
	dst->fX = (R[0][0] * src->fX) + (R[0][1] * src->fY) + (R[0][2] * src->fZ);
	dst->fY = (R[1][0] * src->fX) + (R[1][1] * src->fY) + (R[1][2] * src->fZ);
	dst->fZ = (R[2][0] * src->fX) + (R[2][1] * src->fY) + (R[2][2] * src->fZ);
}

int aaVectorToPoint2D(ASupPoint2D* campt, const ASupPoint3D* vec, const AVision* param)
{
	int ret_val = 0;
	float x_ = 0;
	float y_ = 0;
	float CamRMatrix[3][3] = { { 1, 0, 0 },{ 0, 1, 0 },{ 0, 0, 1 } };
	ASupPoint3D tmp3Dpt;

	//A_ASSERT(param && vec && campt);

	GenerateRMatrix(&param->param.extParam, CamRMatrix);

	//CamRMatrix[0][0] = 0.4925;
	//CamRMatrix[0][1] = -0.0857;
	//CamRMatrix[0][2] = 0.866;

	//CamRMatrix[1][0] = 0.2395;
	//CamRMatrix[1][1] = 0.9703;
	//CamRMatrix[1][2] = -0.0397;

	//CamRMatrix[2][0] = -0.8482;
	//CamRMatrix[2][1] = 0.2262;
	//CamRMatrix[2][2] = 0.4985;

	//CamRMatrix[0][0] = 0.8489;
	//CamRMatrix[0][1] = -0.0179;
	//CamRMatrix[0][2] = -0.4604;

	//CamRMatrix[1][0] = 0.0199;
	//CamRMatrix[1][1] = 0.9998;
	//CamRMatrix[1][2] = -0.0003;

	//CamRMatrix[2][0] = 0.5282;
	//CamRMatrix[2][1] = -0.009;
	//CamRMatrix[2][2] = 0.8877;


	//CamRMatrix[0][0] = 0.917;
	//CamRMatrix[0][1] = 0.001349;
	//CamRMatrix[0][2] = 0.457708;

	//CamRMatrix[1][0] = -0.001518;
	//CamRMatrix[1][1] = 0.9999;
	//CamRMatrix[1][2] = 0.000009;

	//CamRMatrix[2][0] = -0.39865;
	//CamRMatrix[2][1] = -0.0007049;
	//CamRMatrix[2][2] = 0.889;

	//CamRMatrix[0][0] = 0.60165;
	//CamRMatrix[0][1] = 0.0013525;
	//CamRMatrix[0][2] = -0.83166;

	//CamRMatrix[1][0] = -0.101213;
	//CamRMatrix[1][1] = 0.992;
	//CamRMatrix[1][2] = -0.068684;

	//CamRMatrix[2][0] = 0.7923189;
	//CamRMatrix[2][1] = 0.125702;
	//CamRMatrix[2][2] = 0.551016;

	//CamRMatrix[0][0] = 0.4443;
	//CamRMatrix[0][1] = -0.0133;
	//CamRMatrix[0][2] = 0.8851;

	//CamRMatrix[1][0] = 0.0339;
	//CamRMatrix[1][1] = 0.9994;
	//CamRMatrix[1][2] = -0.0027;

	//CamRMatrix[2][0] = -0.8953;
	//CamRMatrix[2][1] = 0.0312;
	//CamRMatrix[2][2] = 0.4654;

	CoordinateConvert(vec, &tmp3Dpt, CamRMatrix);//转到摄像机坐标系
	//tmp3Dpt.fX = vec->fX;
	//tmp3Dpt.fY = vec->fY;
	//tmp3Dpt.fZ = vec->fZ;

	////matlab toolbox exter param

	//float tc[3] = { -156.056008, 	 -44.753577, 	 1759.658573 };

	//float rotation[3][3] = { { 0.999080 ,	 0.011219 	, 0.041390 },
	//					{ 0.002610 ,	 0.947473 ,- 0.319825 },
	//					{ -0.042804 ,	 0.319639 ,	 0.946572 } };

	//tmp3Dpt.fX = rotation[0][0] * vec->fX + rotation[0][1] * vec->fY + rotation[0][2] * vec->fZ;
	//tmp3Dpt.fY = rotation[1][0] * vec->fX + rotation[1][1] * vec->fY + rotation[1][2] * vec->fZ;
	//tmp3Dpt.fZ = rotation[2][0] * vec->fX + rotation[2][1] * vec->fY + rotation[2][2] * vec->fZ;

	////tmp3Dpt.fX += tc[0];
	////tmp3Dpt.fY += tc[1];
	////tmp3Dpt.fZ += tc[2];

	////end matlab


	//tmp3Dpt = *vec;

	if (fabs(tmp3Dpt.fZ) > FLT_EPSILON)
	{
		x_ = tmp3Dpt.fX / tmp3Dpt.fZ;
		y_ = tmp3Dpt.fY / tmp3Dpt.fZ;

		//x_ = -1.21105;
		//y_ = 0.255267;

		switch (param->type)
		{
		case AE_CAM_TYPE_PLANAR:
		{
			float cx_ = (float)param->param.intParam.pParam.cx;
			float cy_ = (float)param->param.intParam.pParam.cy;
			float fx_ = param->param.intParam.pParam.fx;
			float fy_ = param->param.intParam.pParam.fy;
			campt->fX = (x_ * fx_) + cx_;
			campt->fY = (y_ * fy_) + cy_;
			break;
		}
		case AE_CAM_TYPE_WIDEVIEW:
		{
			float cx_ = param->param.intParam.wParam.cx;
			float cy_ = param->param.intParam.wParam.cy;
			float fx_ = param->param.intParam.wParam.fx;
			float fy_ = param->param.intParam.wParam.fy;
			float k[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
			float r2 = (x_ * x_) + (y_ * y_);
			float angelX = 0;
			float angelY = 0;
			k[0] = param->param.intParam.wParam.k1;
			k[1] = param->param.intParam.wParam.k2;
			k[2] = param->param.intParam.wParam.p1;
			k[3] = param->param.intParam.wParam.p2;
			k[4] = param->param.intParam.wParam.k3;
			angelX = (x_ *(1 + (k[0] * r2) + (k[1] * r2 * r2) + (k[4] * r2 * r2 * r2))) + (2 * k[2] * x_ * y_) + (k[3] * (r2 + (2 * x_ * x_)));
			//matlab
			//angelX = (x_ *(1 + (k[0] * r2) + (k[1] * r2 * r2) + (k[4] * r2 * r2 * r2))) + (2 * k[2] * y_) + (k[3] * (r2 + (2 * x_ * x_)));
			//angelY = (y_ *(1 + (k[0] * r2) + (k[1] * r2 * r2))) + (2 * k[2] * x_ * y_) + (k[3] * (r2 + (2 * y_ * y_)));
			//chris zhang modify
			angelY = (y_ *(1 + (k[0] * r2) + (k[1] * r2 * r2) + (k[4] * r2 * r2 * r2))) + (2 * k[3] * x_ * y_) + (k[2] * (r2 + (2 * y_ * y_)));
			//matlab
			//angelY = (y_ *(1 + (k[0] * r2) + (k[1] * r2 * r2) + (k[4] * r2 * r2 * r2))) + (2 * k[3] * x_) + (k[2] * (r2 + (2 * y_ * y_)));
			campt->fX = (angelX * fx_) + cx_;
			campt->fY = (angelY * fy_) + cy_;
			break;
		}
		case AE_CAM_TYPE_FISHEYE:
		{
			float cx_ = param->param.intParam.fParam.cx;
			float cy_ = param->param.intParam.fParam.cy;
			float r0 = sqrtf((x_*x_) + (y_*y_));
			float t = atanf(r0);
			float r =
				(param->param.intParam.fParam.k1 * powf(t, 1.f)) +
				(param->param.intParam.fParam.k3 * powf(t, 3.f)) +
				(param->param.intParam.fParam.k5 * powf(t, 5.f)) +
				(param->param.intParam.fParam.k7 * powf(t, 7.f)) +
				(param->param.intParam.fParam.k9 * powf(t, 9.f));
			float phi = (float)atan2(y_, x_);
			campt->fX = ((r * (float)cos(phi)) / param->param.intParam.fParam.asp) + cx_;
			campt->fY = (r * (float)sin(phi)) + cy_;
			break;
		}
		default:
			break;
		}
	}
	else
	{
		ret_val = -1;
	}

	return ret_val;
}

static int InvertMatrix(float a[][MATRIX_ORDER], int n)
{
	int i, j, k, l, u, v;
	int is[MATRIX_ORDER] = { 0 }, js[MATRIX_ORDER] = { 0 };
	float d, p;
	float* _a = a[0];

	for (k = 0; k <= (n - 1); k++)
	{
		d = 0.0;
		for (i = k; i <= (n - 1); i++)
		{
			for (j = k; j <= (n - 1); j++)
			{
				l = (i*n) + j;
				p = (float)fabs(_a[l]);
				if (p > d)
				{
					d = p;
					is[k] = i;
					js[k] = j;
				}
			}
		}

		if (fabs(d) < FLT_EPSILON)
		{
			return(0);
		}

		if (is[k] != k)
		{
			for (j = 0; j <= (n - 1); j++)
			{
				u = (k*n) + j;
				v = (is[k] * n) + j;
				p = _a[u];
				_a[u] = _a[v];
				_a[v] = p;
			}
		}
		if (js[k] != k)
		{
			for (i = 0; i <= (n - 1); i++)
			{
				u = (i*n) + k;
				v = (i*n) + js[k];
				p = _a[u];
				_a[u] = _a[v];
				_a[v] = p;
			}
		}

		l = (k*n) + k;
		_a[l] = 1.0f / _a[l];
		for (j = 0; j <= (n - 1); j++)
		{
			if (j != k)
			{
				u = (k*n) + j;
				_a[u] = _a[u] * _a[l];
			}
		}

		for (i = 0; i <= (n - 1); i++)
		{
			if (i != k)
			{
				for (j = 0; j <= (n - 1); j++)
				{
					if (j != k)
					{
						u = (i*n) + j;
						_a[u] = _a[u] - (_a[(i*n) + k] * _a[(k*n) + j]);
					}
				}
			}
		}

		for (i = 0; i <= (n - 1); i++)
		{
			if (i != k)
			{
				u = (i*n) + k;
				_a[u] = -(_a[u] * _a[l]);
			}
		}
	}
	for (k = (n - 1); k >= 0; k--)
	{
		if (js[k] != k)
		{
			for (j = 0; j <= (n - 1); j++)
			{
				u = (k*n) + j;
				v = (js[k] * n) + j;
				p = _a[u];
				_a[u] = _a[v];
				_a[v] = p;
			}
		}

		if (is[k] != k)
		{
			for (i = 0; i <= (n - 1); i++)
			{
				u = (i*n) + k;
				v = (i*n) + is[k];
				p = _a[u];
				_a[u] = _a[v];
				_a[v] = p;
			}
		}
	}
	return 0;
}

static float Fastfsolve(float r, const AFisheyeParam* stParam)
{
	float tCur = 0;
	float precision = 0.01f;
	float tPre = 1;
	float diff = 999;
	float k1_ = stParam->k1;
	float k3_ = stParam->k3;
	float k5_ = stParam->k5;
	float k7_ = stParam->k7;
	float k9_ = stParam->k9;
	int cnt = 0;
	const int cnt_max = 30;

	while (diff > precision)
	{
		tCur = tPre - ((((k1_*tPre) + (k3_*powf(tPre, 3.)) + (k5_*powf(tPre, 5.)) + (k7_*powf(tPre, 7.)) + (k9_*powf(tPre, 9.))) - r) /
			(k1_ + (3 * k3_*powf(tPre, 2.)) + (5 * k5_*powf(tPre, 4.)) + (7 * k7_*powf(tPre, 6.)) + (9 * k9_*powf(tPre, 8.))));
		diff = (float)fabs(tCur - tPre);
		tPre = tCur;
		++cnt;
		if (cnt_max < cnt)
		{
			break;
		}
	}
	return tCur;
}

int aaPoint2DToVector(ASupPoint3D* vec, const ASupPoint2D* campt, const AVision* param)
{
	float x_ = 0, y_ = 0, z_ = 0;
	float CamRMatrix[3][3] = { { 1, 0, 0 },{ 0, 1, 0 },{ 0, 0, 1 } };
	ASupPoint3D tmp3Dpt;

	//A_ASSERT(param && campt && vec);

	switch (param->type)
	{
	case AE_CAM_TYPE_PLANAR:
	{
		float cx_ = (float)param->param.intParam.pParam.cx;
		float cy_ = (float)param->param.intParam.pParam.cy;
		float fx_ = param->param.intParam.pParam.fx;
		float fy_ = param->param.intParam.pParam.fy;
		x_ = (campt->fX - cx_) / fx_;
		y_ = (campt->fY - cy_) / fy_;
		z_ = 1.0;
		break;
	}
	case AE_CAM_TYPE_WIDEVIEW:
	{
		float cx_ = param->param.intParam.wParam.cx;
		float cy_ = param->param.intParam.wParam.cy;
		float fx_ = param->param.intParam.wParam.fx;
		float fy_ = param->param.intParam.wParam.fy;
		float k[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
		int i = 0;
		int iters = 10;
		float x0_ = x_ = (campt->fX - cx_) / fx_;
		float y0_ = y_ = (campt->fY - cy_) / fy_;
		k[0] = param->param.intParam.wParam.k1;
		k[1] = param->param.intParam.wParam.k2;
		k[2] = param->param.intParam.wParam.p1;
		k[3] = param->param.intParam.wParam.p2;
		k[4] = param->param.intParam.wParam.k3;
		for (i = 0; i < iters; i++)
		{
			float r2 = (x_*x_) + (y_*y_);
			float icdist = (1 + (((((k[7] * r2) + k[6])*r2) + k[5])*r2)) / (1 + (((((k[4] * r2) + k[1])*r2) + k[0])*r2));
			float deltaX = (2 * k[2] * x_*y_) + (k[3] * (r2 + (2 * x_*x_)));
			float deltaY = (k[2] * (r2 + (2 * y_*y_))) + (2 * k[3] * x_*y_);
			x_ = (x0_ - deltaX)*icdist;
			y_ = (y0_ - deltaY)*icdist;
		}
		z_ = 1.0;
		break;
	}
	case AE_CAM_TYPE_FISHEYE:
	{
		float cx_ = param->param.intParam.fParam.cx;
		float cy_ = param->param.intParam.fParam.cy;
		float rx_ = (campt->fX - cx_)*param->param.intParam.fParam.asp;
		float ry_ = campt->fY - cy_;
		float r = sqrtf((rx_*rx_) + (ry_*ry_));
		float t = Fastfsolve(r, &param->param.intParam.fParam);
		float r0 = tanf(t) * 1;
		float phi = (float)atan2(ry_, rx_);
		x_ = r0 * (float)cos(phi);
		y_ = r0 * (float)sin(phi);
		z_ = 1.0;
		break;
	}
	default:
		break;
	}

	tmp3Dpt.fX = x_;
	tmp3Dpt.fY = y_;
	tmp3Dpt.fZ = z_;

	GenerateRMatrix(&param->param.extParam, CamRMatrix);
	InvertMatrix(CamRMatrix, 3);
	CoordinateConvert(&tmp3Dpt, vec, CamRMatrix);

	return 0;
}
int aaCamTo3D(ASupPoint3D* worldpt, const ASupPoint2D* campt, const AVision* param)
{
	int ret_val = 0;
	ASupPoint3D vec = { 0 };
	float camheight = 0;
	int func_ret = 0;

	//A_ASSERT(param && campt && worldpt);

	camheight =  (float)param->param.extParam.ty;
	func_ret = aaPoint2DToVector(&vec, campt, param);

	if ((0 == func_ret)/* && (fabs(vec.fY)>FLT_EPSILON)*/)//相机坐标系转世界坐标系，+，其中tx,ty,tz都是相机在世界坐标系中的坐标
	{

		if (param->mDashboardRowInPixel) {
			worldpt->fX = (((vec.fX / vec.fY)*camheight) - (float)param->param.extParam.tx);
			worldpt->fY = camheight;
			worldpt->fZ = (((vec.fZ / vec.fY)*camheight) - (float)param->param.extParam.tz);

			if (vec.fY < 0) {
				
				ret_val = -1;

			}
		}
		else {
			worldpt->fX = vec.fX;
			worldpt->fY = vec.fY;
			worldpt->fZ = vec.fZ;
		}


	}
	else
	{
		ret_val = 0;
	}

	return ret_val;
}

//matlab poly

void world2cam(double point2D[2], double point3D[3])
{
	//double hehe[10] = { 585.675729, 481.512759 ,68.373228, - 1.399894 ,40.619231, 40.830576, - 11.119778, - 30.298443, - 14.932464 ,- 2.495842 };
	//0
	double hehe[] = { 590.293777,-492.954252,86.290088,-8.692693,35.125395,-45.238015,19.166111,-2.686190 };
	//2
	//double hehe[] = { 588.508858,-480.310300,61.067583,5.637644,43.324462,-42.896699,-9.304416,22.484301,-6.860291 };
	//1
	//double hehe[] = { 593.741270,-531.217093,163.336414,-64.822337,31.546216,-16.696041,3.834312 };

	double *invpol = hehe;

	double xc = (641.8885);
	double yc = (361.7816);
	double c = (1.0008);
	double d = (-0.0015);
	double e = (-2.6138e-04);

	//double xc = (636.7377);
	//double yc = (367.3011);
	//double c = (1.0006);
	//double d = (-0.0194);
	//double e = (0.0183);

	//double xc = (637.5648);
	//double yc = (368.9132);
	//double c = (1.0001);
	//double d = (-0.0131);
	//double e = (0.0142);

	int    width = (1280);
	int    height = (720);
	int length_invpol = sizeof(hehe)/sizeof(double);
	double norm = sqrt(point3D[0] * point3D[0] + point3D[1] * point3D[1]);
	double theta = atan(point3D[2] / norm);
	double t, t_i;
	double rho, x, y;
	double invnorm;
	int i;

	if (norm != 0)
	{
		invnorm = 1 / norm;
		t = theta;
		rho = invpol[0];
		t_i = 1;

		for (i = 1; i < length_invpol; i++)
		{
			t_i *= t;
			rho += t_i*invpol[i];
		}

		x = point3D[0] * invnorm*rho;
		y = point3D[1] * invnorm*rho;

		point2D[0] = x*c + y*d + xc;
		point2D[1] = x*e + y + yc;
	}
	else
	{
		point2D[0] = xc;
		point2D[1] = yc;
	}
}

int aa3DToCam(ASupPoint2D* campt, ASupPoint3D* worldpt, const AVision* param)
{
	int ret_val = 0;
	int func_ret;
	ASupPoint3D vec;

#if 1

	//ASSERT(param && campt && worldpt);

	//将点转化到相机坐标系 //相机坐标系转世界坐标系，-，其中tx,ty,tz都是相机在世界坐标系中的坐标
	vec.fX = (worldpt->fX) + (float)param->param.extParam.tx;
	vec.fY = worldpt->fY;// +(float)param->param.extParam.ty;//向下是正值
	vec.fZ = (worldpt->fZ) + (float)param->param.extParam.tz;

	//vec.fX = (worldpt->fX);
	//vec.fY = worldpt->fY;
	//vec.fZ = (worldpt->fZ);


	func_ret = aaVectorToPoint2D(campt, &vec, param);
	ret_val = func_ret;
	
#endif

	//matlab
#if 0

	double wd[3];
	double im[2];

	wd[0] = (worldpt->fX);
	wd[1] = worldpt->fY;
	wd[2] = (worldpt->fZ);

	world2cam(im,wd);

	campt->fX = im[0];
	campt->fY = im[1];

#endif

	//opencv

#if 0

	//int ret_val = 0;
	float x_ = 0;
	float y_ = 0;
	float CamRMatrix[3][3] = { { 1, 0, 0 },{ 0, 1, 0 },{ 0, 0, 1 } };
	ASupPoint3D tmp3Dpt;


	GenerateRMatrix(&param->param.extParam, CamRMatrix);

	CoordinateConvert(worldpt, &tmp3Dpt, CamRMatrix);//转到摄像机坐标系

	worldpt->fX = tmp3Dpt.fX;
	worldpt->fY = tmp3Dpt.fY;
	worldpt->fZ = tmp3Dpt.fZ;

	double k[4] = { 9.4480953438479329e-02, - 1.0077116372400647e-02,
		1.1616779386385469e-02, - 3.8190341752193969e-03 };

	double f[2] = { 3.0645301433866700e+02 ,3.0657476513062340e+02 };

	double c[2] = { 6.3475764019544135e+02 ,3.6285444698995644e+02 };

	double x = worldpt->fX / worldpt->fZ, y = worldpt->fY / worldpt->fZ;

	double r = sqrt(x*x + y*y);
	double theta = atan(r);

	double theta2 = theta*theta, theta4 = theta2*theta2, theta6 = theta4*theta2, theta8 = theta4*theta4;
	double theta_d = theta * (1 + k[0] * theta2 + k[1] * theta4 + k[2] * theta6 + k[3] * theta8);

	double scale = (r == 0) ? 1.0 : theta_d / r;
	campt->fX = f[0] * x*scale + c[0];
	campt->fY = f[1] * y*scale + c[1];

#endif

	return 0;
}

int Calexparam(DISmat *dismat)
{
	AVision aCamParam_ihc;
	ASupPoint3D worldPt10L = { 0 };
	ASupPoint2D camPt1 = { 0 };
	int x, y = 0;

	aCamParam_ihc.type = AE_CAM_TYPE_PLANAR;
	aCamParam_ihc.width = 720;
	aCamParam_ihc.height = 480;

	aCamParam_ihc.param.intParam.pParam.cx = 360.0f;
	aCamParam_ihc.param.intParam.pParam.cy = 240.0f;
	aCamParam_ihc.param.intParam.pParam.fx = 260.0f;
	aCamParam_ihc.param.intParam.pParam.fy = 260.0f;//单位是 pix

	aCamParam_ihc.param.extParam.rx = 0.0;
	aCamParam_ihc.param.extParam.ry = 0.0;
	aCamParam_ihc.param.extParam.rz = 0.0;
	aCamParam_ihc.param.extParam.tx = 0;//单位mm
	aCamParam_ihc.param.extParam.ty = 1950;
	aCamParam_ihc.param.extParam.tz = 0;


	for (int i = 0; i < 2000; i++)
	{
		for (int j = 3500; j < 4500; j += 100)
		{
			worldPt10L.fX = i;
			worldPt10L.fY = 0;
			worldPt10L.fZ = j;

			aa3DToCam(&camPt1, &worldPt10L, &aCamParam_ihc);
			x = (int)camPt1.fX;
			y = (int)camPt1.fY;

			if (x<0)
			{
				x = 0;
			}
			if (x>719)
			{
				x = 719;
			}

			if (y<0)
			{
				y = 0;
			}
			if (y>479)
			{
				y = 479;
			}
			
		}
	}

	return 0;
}


int CalDis(ASupPoint2D *point2D, ASupPoint3D* worldpt)
{
	AVision aparam;

	aparam.type = AE_CAM_TYPE_PLANAR;
	aparam.width = 1920;
	aparam.height = 1208;

	aparam.param.intParam.pParam.cx = 962;
	aparam.param.intParam.pParam.cy = 585;
	aparam.param.intParam.pParam.fx = 1976.0f;
	aparam.param.intParam.pParam.fy = 1982.0f;

	aparam.param.extParam.rx = 4.8;
	aparam.param.extParam.ry = 1.1;
	aparam.param.extParam.rz = 0.0;

	aparam.param.extParam.tx = 0.0;
	aparam.param.extParam.ty = 1240;
	aparam.param.extParam.tz = -1750;

	aaCamTo3D(worldpt, point2D, &aparam);

	return 0;
}

int CalDisLine(DISmat *dismat)
{
	int nVanishline;
	int x, y = 0;
	ASupPoint3D worldptcc;


	AVision aCamParam_ihc;
	ASupPoint3D worldPt10L = { 0 };
	ASupPoint3D worldPt10R = { 0 };
	ASupPoint3D worldPt60L = { 0 };
	ASupPoint3D worldPt60R = { 0 };
	ASupPoint3D worldPt120L = { 0 };
	ASupPoint3D worldPt120R = { 0 };


	ASupPoint3D worldPt3 = { 0 };//一汽要求
	ASupPoint3D worldPt4 = { 0 };

	ASupPoint3D worldPt5 = { 0 };//一汽要求
	ASupPoint3D worldPt6 = { 0 };


	ASupPoint3D worldPt1tlh = { 0 };//头灯左线
	ASupPoint3D worldPt2tlh = { 0 };


	ASupPoint2D camPt1 = { 0 };
	ASupPoint2D camPt2 = { 0 };

	ASupPoint2D camPt1r = { 0 };
	ASupPoint2D camPt2r = { 0 };

	ASupPoint2D camPt1t = { 0 };
	ASupPoint2D camPt2t = { 0 };

	ASupPoint2D camPt1t2 = { 0 };
	ASupPoint2D camPt2t2 = { 0 };

	ASupPoint2D camPt3 = { 0 };
	ASupPoint2D camPt4 = { 0 };

	ASupPoint2D camPt5 = { 0 };
	ASupPoint2D camPt6 = { 0 };

	ASupPoint2D camPt1lh = { 0 };
	ASupPoint2D camPt2lh = { 0 };

	ASupPoint2D camPt1lhh = { 0 };//画固定高度的线
	ASupPoint2D camPt2lhh = { 0 };
		
#if 1
	//////L
	worldPt10L.fX = 640;//单位是m
	worldPt10L.fY = 0;
	worldPt10L.fZ = 5000;
	worldPt120L.fX = 640;
	worldPt120L.fY = 0;
	worldPt120L.fZ = 10000;

	//R
	worldPt10R.fX = 2000;
	worldPt10R.fY = 0;
	worldPt10R.fZ = 5000;

	worldPt120R.fX = 2000;
	worldPt120R.fY = 0;
	worldPt120R.fZ = 10000;

	//60m
	worldPt60L.fX = 2000;
	worldPt60L.fY = 0;
	worldPt60L.fZ = 5000;

	worldPt60R.fX = 2000;
	worldPt60R.fY = 0;
	worldPt60R.fZ = 10000;

#endif

#if 0
	//////L
	worldPt10L.fX = -1000;//单位是m
	worldPt10L.fY = 0;
	worldPt10L.fZ = 5000;
	worldPt120L.fX = -1000;
	worldPt120L.fY = 0;
	worldPt120L.fZ = 10000;

	//R
	worldPt10R.fX = 0;
	worldPt10R.fY = 0;
	worldPt10R.fZ = 5000;

	worldPt120R.fX = 0;
	worldPt120R.fY = 0;
	worldPt120R.fZ = 10000;

	//60m
	worldPt60L.fX = 2000;
	worldPt60L.fY = 0;
	worldPt60L.fZ = 5000;

	worldPt60R.fX = 2000;
	worldPt60R.fY = 0;
	worldPt60R.fZ = 10000;

#endif
	aCamParam_ihc.type = AE_CAM_TYPE_PLANAR;
	aCamParam_ihc.width = 1920;
	aCamParam_ihc.height = 1208;

	//aCamParam_ihc.param.intParam.pParam.cx = 962;
	//aCamParam_ihc.param.intParam.pParam.cy = 585;
	//aCamParam_ihc.param.intParam.pParam.fx = 1976.0f;
	//aCamParam_ihc.param.intParam.pParam.fy = 1982.0f;//单位是 pix

	aCamParam_ihc.param.intParam.pParam.cx = 946.3;
	aCamParam_ihc.param.intParam.pParam.cy = 602.9;
	aCamParam_ihc.param.intParam.pParam.fx = 1850.0f;
	aCamParam_ihc.param.intParam.pParam.fy = 1860.0f;//单位是 pix



	aCamParam_ihc.param.extParam.rx = 5.4;
	aCamParam_ihc.param.extParam.ry = 0.2;
	aCamParam_ihc.param.extParam.rz = 0.0;
	aCamParam_ihc.param.extParam.tx = 0.0;//单位mm
	aCamParam_ihc.param.extParam.ty = 1240;
	aCamParam_ihc.param.extParam.tz = -1750;
	////L
	aa3DToCam(&camPt1, &worldPt10L, &aCamParam_ihc);
	aa3DToCam(&camPt2, &worldPt120L, &aCamParam_ihc);

	dismat->dmat[0].fX = camPt1.fX;
	dismat->dmat[0].fY = camPt1.fY;

	dismat->dmat[4].fX = camPt2.fX;
	dismat->dmat[4].fY = camPt2.fY;



	////R
	aa3DToCam(&camPt1r, &worldPt10R, &aCamParam_ihc);
	aa3DToCam(&camPt2r, &worldPt120R, &aCamParam_ihc);

	dismat->dmat[1].fX = camPt1r.fX;
	dismat->dmat[1].fY = camPt1r.fY;


	dismat->dmat[5].fX = camPt2r.fX;
	dismat->dmat[5].fY = camPt2r.fY;
	////60
	aa3DToCam(&camPt1t, &worldPt60L, &aCamParam_ihc);
	aa3DToCam(&camPt2t, &worldPt60R, &aCamParam_ihc);
	
	dismat->dmat[2].fX = camPt1t.fX;
	dismat->dmat[2].fY = camPt1t.fY;

	dismat->dmat[3].fX = camPt2t.fX;
	dismat->dmat[3].fY = camPt2t.fY;


	//////120
   
	//nVanishline
	nVanishline = 302;

	dismat->dmat[6].fX = 302;
	dismat->dmat[6].fY = 302;

	return 0;

}

int newFish3D22D(ASupPoint2D* campt, ASupPoint3D* worldpt, AVision* param) {


	int ret_val = 0;
	float x_ = 0;
	float y_ = 0;
	float CamRMatrix[3][3] = { { 1, 0, 0 },{ 0, 1, 0 },{ 0, 0, 1 } };
	ASupPoint3D tmp3Dpt;

	worldpt->fX += param->param.extParam.tx;
	////worldpt->fY += param->param.extParam.ty;
	worldpt->fZ += param->param.extParam.tz;

	GenerateRMatrix(&param->param.extParam, CamRMatrix);

	CoordinateConvert(worldpt, &tmp3Dpt, CamRMatrix);//转到摄像机坐标系

	worldpt->fX = tmp3Dpt.fX;
	worldpt->fY = tmp3Dpt.fY;
	worldpt->fZ = tmp3Dpt.fZ;

	int    width = (1280);
	int    height = (720);
	int length_invpol = param->param.intParam.nfParam.invDistCoeffNum;
	double norm = sqrt(worldpt->fX * worldpt->fX + worldpt->fY * worldpt->fY);
	double theta = atan(worldpt->fZ / norm);
	double t, t_i;
	double rho, x, y;
	double invnorm;
	int i;
	float xc = param->param.intParam.nfParam.cx;
	float yc = param->param.intParam.nfParam.cy;
	float c = param->param.intParam.nfParam.c;
	float d = param->param.intParam.nfParam.d;
	float e = param->param.intParam.nfParam.e;

	float* invpol = param->param.intParam.nfParam.invDistCoeff;

	if (norm != 0)
	{
		invnorm = 1 / norm;
		t = theta;
		rho = invpol[0];
		t_i = 1;

		for (i = 1; i < length_invpol; i++)
		{
			t_i *= t;
			rho += t_i*invpol[i];
		}

		x = worldpt->fX * invnorm*rho;
		y = worldpt->fY * invnorm*rho;

		campt->fX = x*c + y*d + xc;
		campt->fY = x*e + y + yc;
	}
	else
	{
		campt->fX = xc;
		campt->fY = yc;
	}
	return 0;
}

int newFish2D23D(ASupPoint3D* worldpt, ASupPoint2D* campt, AVision* param)
{
	float *pol = param->param.intParam.nfParam.distCoeff;
	float xc = param->param.intParam.nfParam.cx;
	float yc = param->param.intParam.nfParam.cy;
	float c = param->param.intParam.nfParam.c;
	float d = param->param.intParam.nfParam.d;
	float e = param->param.intParam.nfParam.e;
	int length_pol = (5);
	double invdet = 1 / (c - d*e); // 1/det(A), where A = [c,d;e,1] as in the Matlab file

	double xp = invdet*((campt->fX - xc) - d*(campt->fY - yc));
	double yp = invdet*(-e*(campt->fX - xc) + c*(campt->fY - yc));

	double r = sqrt(xp*xp + yp*yp); //distance [pixels] of  the point from the image center
	double zp = pol[0];
	double r_i = 1;
	int i;

	float CamRMatrix[3][3] = { { 1, 0, 0 },{ 0, 1, 0 },{ 0, 0, 1 } };
	ASupPoint3D tmp3Dpt;
	ASupPoint3D tmp3Dpt1;


	for (i = 1; i < length_pol; i++)
	{
		r_i *= r;
		zp += r_i*pol[i];
	}

	//normalize to unit norm
	double invnorm = 1 / sqrt(xp*xp + yp*yp + zp*zp);

	tmp3Dpt.fX = invnorm*xp;
	tmp3Dpt.fY = invnorm*yp;
	tmp3Dpt.fZ = invnorm*zp;

	GenerateRMatrix(&param->param.extParam, CamRMatrix);
	InvertMatrix(CamRMatrix, 3);
	CoordinateConvert(&tmp3Dpt, &tmp3Dpt1, CamRMatrix);

	worldpt->fX = (((tmp3Dpt1.fX / tmp3Dpt1.fY)*param->param.extParam.ty) - (float)param->param.extParam.tx);
	worldpt->fY = param->param.extParam.ty;
	worldpt->fZ = (((tmp3Dpt1.fZ / tmp3Dpt1.fY)*param->param.extParam.ty) - (float)param->param.extParam.tz);

	return 0;
}

