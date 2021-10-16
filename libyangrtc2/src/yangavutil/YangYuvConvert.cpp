﻿/*
 * YangYuvUtil.cpp
 *
 *  Created on: 2020年10月8日
 *      Author: yang
 */

#include <memory.h>
#include "yangavutil/video/YangYuvConvert.h"




void YangYuvConvert::loadLib() {

	yang_YUY2ToNV12 = (int32_t (*)(const uint8_t *src_yuy2, int32_t src_stride_yuy2,
			uint8_t *dst_y, int32_t dst_stride_y, uint8_t *dst_uv,
			int32_t dst_stride_uv, int32_t width, int32_t height)) m_lib.loadFunction(
			"YUY2ToNV12");
	yang_YUY2ToI420 =(int32_t (*)(const uint8_t *src_yuy2, int32_t src_stride_yuy2,
					uint8_t *dst_y, int32_t dst_stride_y, uint8_t *dst_u,
					int32_t dst_stride_u, uint8_t *dst_v, int32_t dst_stride_v,
					int32_t width, int32_t height)) m_lib.loadFunction("YUY2ToI420");


	yang_I420ToNV12=(int32_t (*)(const uint8_t* src_y, int32_t src_stride_y, const uint8_t* src_u,
	               int32_t src_stride_u,const uint8_t* src_v,int32_t src_stride_v,	uint8_t* dst_y,
	               int32_t dst_stride_y, uint8_t* dst_uv,  int32_t dst_stride_uv,  int32_t width, int32_t height)) m_lib.loadFunction("I420ToNV12");

	yang_I420ToNV21=(int32_t (*)(const uint8_t* src_y,
	               int32_t src_stride_y,
	               const uint8_t* src_u,
	               int32_t src_stride_u,
	               const uint8_t* src_v,
	               int32_t src_stride_v,
	               uint8_t* dst_y,
	               int32_t dst_stride_y,
	               uint8_t* dst_vu,
	               int32_t dst_stride_vu,
	               int32_t width,
	               int32_t height)) m_lib.loadFunction("I420ToNV21");

	yang_I420ToRGB24 = (int32_t (*)(const uint8_t *src_y, int32_t src_stride_y,
			const uint8_t *src_u, int32_t src_stride_u, const uint8_t *src_v,
			int32_t src_stride_v, uint8_t *dst_rgb24, int32_t dst_stride_rgb24,
			int32_t width, int32_t height)) m_lib.loadFunction("I420ToRGB24");
	yang_NV12ToRGB24 = (int32_t (*)(const uint8_t *src_y, int32_t src_stride_y,
			const uint8_t *src_uv, int32_t src_stride_uv, uint8_t *dst_rgb24,
			int32_t dst_stride_rgb24, int32_t width, int32_t height)) m_lib.loadFunction(
			"NV12ToRGB24");
	yang_NV21ToRGB24 = (int32_t (*)(const uint8_t *src_y, int32_t src_stride_y,
			const uint8_t *src_vu, int32_t src_stride_vu, uint8_t *dst_rgb24,
			int32_t dst_stride_rgb24, int32_t width, int32_t height)) m_lib.loadFunction(
			"NV21ToRGB24");
	yang_ARGBToRGB24 =
			(int32_t (*)(const uint8_t *src_argb, int32_t src_stride_argb,
					uint8_t *dst_rgb24, int32_t dst_stride_rgb24, int32_t width,
					int32_t height)) m_lib.loadFunction("ARGBToRGB24");
	yang_RGB24ToI420 =
			(int32_t (*)(const uint8_t *src_rgb24, int32_t src_stride_rgb24,
					uint8_t *dst_y, int32_t dst_stride_y, uint8_t *dst_u,
					int32_t dst_stride_u, uint8_t *dst_v, int32_t dst_stride_v,
					int32_t width, int32_t height)) m_lib.loadFunction("RGB24ToI420");
	yang_RGB24ToARGB=(int32_t (*)(const uint8_t* src_rgb24,
	                int32_t src_stride_rgb24,
	                uint8_t* dst_argb,
	                int32_t dst_stride_argb,
	                int32_t width,
	                int32_t height)) m_lib.loadFunction("RGB24ToARGB");
	yang_RAWToARGB=(int32_t (*)(const uint8_t* src_raw,
	              int32_t src_stride_raw,
	              uint8_t* dst_argb,
	              int32_t dst_stride_argb,
	              int32_t width,
	              int32_t height)) m_lib.loadFunction("RAWToARGB");
	yang_NV12Scale = (int32_t (*)(const uint8_t *src_y, int32_t src_stride_y,
			const uint8_t *src_uv, int32_t src_stride_uv, int32_t src_width,
			int32_t src_height, uint8_t *dst_y, int32_t dst_stride_y, uint8_t *dst_uv,
			int32_t dst_stride_uv, int32_t dst_width, int32_t dst_height,
			enum FilterMode filtering)) m_lib.loadFunction("NV12Scale");
	yang_I420Scale = (int32_t (*)(const uint8_t *src_y, int32_t src_stride_y,
			const uint8_t *src_u, int32_t src_stride_u, const uint8_t *src_v,
			int32_t src_stride_v, int32_t src_width, int32_t src_height, uint8_t *dst_y,
			int32_t dst_stride_y, uint8_t *dst_u, int32_t dst_stride_u, uint8_t *dst_v,
			int32_t dst_stride_v, int32_t dst_width, int32_t dst_height,
			enum FilterMode filtering)) m_lib.loadFunction("I420Scale");
	yang_ScalePlane =
			(void (*)(const uint8_t *src, int32_t src_stride, int32_t src_width,
					int32_t src_height, uint8_t *dst, int32_t dst_stride, int32_t dst_width,
					int32_t dst_height, enum FilterMode filtering)) m_lib.loadFunction(
					"ScalePlane");
	yang_ARGBScale=(int32_t (*)(const uint8_t* src_argb,
	              int32_t src_stride_argb,
	              int32_t src_width,
	              int32_t src_height,
	              uint8_t* dst_argb,
	              int32_t dst_stride_argb,
	              int32_t dst_width,
	              int32_t dst_height,
	              enum FilterMode filtering)) m_lib.loadFunction(
	  					"ARGBScale");
}

void YangYuvConvert::unloadLib() { //srt_cleanup
	yang_YUY2ToNV12 = NULL;
	yang_YUY2ToI420 = NULL;
	yang_I420ToNV12 = NULL;
	yang_I420ToNV21 = NULL;
	yang_I420ToRGB24 = NULL;
	yang_NV12ToRGB24 = NULL;
	yang_NV21ToRGB24 = NULL;
	yang_ARGBToRGB24 = NULL;
	yang_RGB24ToARGB=NULL;
	yang_RAWToARGB=NULL;
	yang_RGB24ToI420 = NULL;
	yang_NV12Scale = NULL;
	yang_I420Scale = NULL;
	yang_ScalePlane = NULL;

	yang_ARGBScale=NULL;

}
YangYuvConvert::YangYuvConvert() {

	m_lib.loadObject("libyuv");
	loadLib();
}

YangYuvConvert::~YangYuvConvert() {
	unloadLib();
	m_lib.unloadObject();
}

int32_t YangYuvConvert::yuy2tonv12(uint8_t *src, uint8_t *dst, int32_t width, int32_t height) {
	return yang_YUY2ToNV12((const uint8_t*) src, width << 1, dst, width,
			dst + (width * height), width, width, height);
	//return ret;
}
int32_t YangYuvConvert::yuy2toi420(uint8_t *src, uint8_t *dst, int32_t width, int32_t height) {

	return yang_YUY2ToI420((const uint8_t*) src, width << 1, dst, width,
			dst + (width * height), (width >> 1),
			dst + (width * height) + (int) (width * height / 4), (width >> 1),
			width, height);

	//return ret;
}
int32_t YangYuvConvert::i420tonv12(uint8_t* src,uint8_t *dst,int32_t width,int32_t height){
	return yang_I420ToNV12((const uint8_t*) src, width,
			(const uint8_t*) (src + (width * height)), (width >> 1),
			(const uint8_t*) (src + (width * height)+ (int) (width * height / 4)), (width >> 1),
			dst, width ,dst+width*height,width,
			width, height);
}
int32_t YangYuvConvert::i420tonv21(uint8_t* src,uint8_t *dst,int32_t width,int32_t height){
	return yang_I420ToNV21((const uint8_t*) src, width,
			(const uint8_t*) (src + (width * height)), (width >> 1),
			(const uint8_t*) (src + (width * height)+ (int) (width * height / 4)), (width >> 1),
			dst, width ,dst+width*height,width,
			width, height);
}
//int32_t YangYuvUtil::bgr2yuy2(uint8_t* src,uint8_t *dst,int32_t srcWidth,int32_t srcHeiht){
//	return 0;
//}

int32_t YangYuvConvert::I420torgb24(uint8_t *src, uint8_t *dst, int32_t width,
		int32_t height) {
	return yang_I420ToRGB24((const uint8_t*) src, width,
			(const uint8_t*) (src + (width * height)), (width >> 1),
			(const uint8_t*) (src + (width * height)
					+ (int) (width * height / 4)), (width >> 1), dst, width * 3,
			width, height);
}
int32_t YangYuvConvert::nv12torgb24(uint8_t *src, uint8_t *dst, int32_t width,
		int32_t height) {
	return yang_NV12ToRGB24((const uint8_t*) src, width,
			(const uint8_t*) (src + (width * height)), width, dst,
			width * 3, width, height);
}
int32_t YangYuvConvert::nv21torgb24(uint8_t *src, uint8_t *dst, int32_t width,
		int32_t height) {
	return yang_NV21ToRGB24((const uint8_t*) src, width,
			(const uint8_t*) (src + (width * height)), width, dst,
			width * 3, width, height);
}
int32_t YangYuvConvert::argbtorgb24(uint8_t *src, uint8_t *dst, int32_t width,
		int32_t height) {
	return yang_ARGBToRGB24((const uint8_t*) src, width * 4, dst,
			width * 3, width, height);
}
int32_t YangYuvConvert::rgb24toargb(uint8_t *src, uint8_t *dst, int32_t width,
		int32_t height) {

	return yang_RGB24ToARGB((const uint8_t*) src, width * 3, dst,
			width * 4, width, height);
}
int32_t YangYuvConvert::rgb24toI420(uint8_t *src_rgb24, uint8_t *dst, int32_t width,
		int32_t height) {
	return yang_RGB24ToI420((const uint8_t*) src_rgb24, width * 3, dst,
			width, dst + (width * height), (width >> 1),
			dst + (width * height) + (int) (width * height / 4), (width >> 1),
			width, height);
}

int32_t YangYuvConvert::scaleNv12(uint8_t *src, uint8_t *dst, int32_t srcWidth,
		int32_t srcHeight, int32_t dstWidth, int32_t dstHeight, int32_t mode) {
	return yang_NV12Scale((const uint8_t*) src, srcWidth,
			(const uint8_t*) src + srcWidth * srcHeight, srcWidth, srcWidth,
			srcHeight, dst, dstWidth, dst + dstWidth * dstHeight, dstWidth,
			dstWidth, dstHeight, (libyuv::FilterMode) mode);
}
int32_t YangYuvConvert::scaleI420(uint8_t *src, uint8_t *dst, int32_t srcWidth,
		int32_t srcHeight, int32_t dstWidth, int32_t dstHeight, int32_t mode) {
	int32_t srcLen=srcWidth*srcHeight;
	int32_t dstLen=dstWidth*dstHeight;
	return yang_I420Scale((const uint8_t*) src, srcWidth,
			(const uint8_t*) (src + srcLen), srcWidth/2,
			(const uint8_t*) (src + srcLen*5/4),srcWidth/2,
			srcWidth, srcHeight,
			dst, dstWidth,
			dst + dstLen, dstWidth/2,
			dst + dstLen*5/4, dstWidth/2,
			dstWidth, dstHeight, (libyuv::FilterMode) mode);
}

int32_t YangYuvConvert::scaleYuy2(uint8_t *src, uint8_t *dst, int32_t srcWidth,
		int32_t srcHeight, int32_t dstWidth, int32_t dstHeight, int32_t mode) {
	yang_ScalePlane((const uint8_t*) src, srcWidth << 1, srcWidth, srcHeight,
			dst, dstWidth << 1, dstWidth, dstHeight, (libyuv::FilterMode) mode);
	return 0;
}

int32_t YangYuvConvert::scaleArgb(uint8_t* src,uint8_t *dst,int32_t srcWidth,int32_t srcHeight,int32_t dstWidth,int32_t dstHeight,int32_t mode){

return yang_ARGBScale((const uint8_t*)src,srcWidth*4,
srcWidth,srcHeight,
dst,dstWidth*4,
dstWidth,dstHeight,
(libyuv::FilterMode)mode
);
}

/**
 int32_t scaleRgb(uint8_t* src,int32_t srcWidth,int32_t srcHeiht,uint8_t *dst,int32_t dstWidth,int32_t dstHeight,int32_t mode=2){
	 libyuv::Scale()
 return yang_ScaleR((const uint8_t*)src,srcWidth<<1,
 srcWidth,srcHeight,
 dst,dstWidth<<1,
 dstWidth,dstHeight,
 (libyuv::FilterMode)mode
 );
 }
**/
