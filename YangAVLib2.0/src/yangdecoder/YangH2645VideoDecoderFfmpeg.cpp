/*
 * YangH2645VideoDecoderFfmpeg.cpp
 *
 *  Created on: 2019年9月20日
 *      Author: yang
 */

#include "YangH2645VideoDecoderFfmpeg.h"

#include "stdlib.h"
#ifndef _WIN32
void YangH2645VideoDecoderFfmpeg::loadLib() {
//yang_speex_lib_get_mode=(const SpeexMode * (*) (int32_t mode))m_lib.loadFunction("");
	yang_av_frame_alloc = (AVFrame* (*)(void)) m_lib1.loadFunction(
			"av_frame_alloc");
	yang_av_buffer_unref = (void (*)(AVBufferRef **buf)) m_lib1.loadFunction(
			"av_buffer_unref");
	yang_av_hwframe_ctx_init = (int32_t (*)(AVBufferRef *ref)) m_lib1.loadFunction(
			"av_hwframe_ctx_init");
	yang_av_image_get_buffer_size = (int32_t (*)(enum AVPixelFormat pix_fmt,
			int32_t width, int32_t height, int32_t align)) m_lib1.loadFunction(
			"av_image_get_buffer_size");
	yang_av_hwdevice_ctx_create = (int32_t (*)(AVBufferRef **device_ctx,
			enum AVHWDeviceType type, const char *device, AVDictionary *opts,
			int32_t flags)) m_lib1.loadFunction("av_hwdevice_ctx_create");
	yang_av_hwframe_transfer_data = (int32_t (*)(AVFrame *dst, const AVFrame *src,
			int32_t flags)) m_lib1.loadFunction("av_hwframe_transfer_data");
	yang_av_free = (void (*)(void *ptr)) m_lib1.loadFunction("av_free");
	yang_av_frame_free = (void (*)(AVFrame **frame)) m_lib1.loadFunction(
			"av_frame_free");
	yang_av_buffer_ref =
			(AVBufferRef* (*)(AVBufferRef *buf)) m_lib1.loadFunction(
					"av_buffer_ref");
	yang_av_image_fill_arrays = (int32_t (*)(uint8_t *dst_data[4],
			int32_t dst_linesize[4], const uint8_t *src, enum AVPixelFormat pix_fmt,
			int32_t width, int32_t height, int32_t align)) m_lib1.loadFunction(
			"av_image_fill_arrays");
	yang_av_hwframe_ctx_alloc =
			(AVBufferRef* (*)(AVBufferRef *device_ctx)) m_lib1.loadFunction(
					"av_hwframe_ctx_alloc");
	yang_av_malloc = (void* (*)(size_t size)) m_lib1.loadFunction("av_malloc");

	yang_avcodec_open2 = (int32_t (*)(AVCodecContext *avctx, const AVCodec *codec,
			AVDictionary **options)) m_lib.loadFunction("avcodec_open2");
	yang_av_init_packet = (void (*)(AVPacket *pkt)) m_lib.loadFunction(
			"av_init_packet");
	yang_av_hwframe_get_buffer = (int32_t (*)(AVBufferRef *hwframe_ctx,
			AVFrame *frame, int32_t flags)) m_lib.loadFunction(
			"av_hwframe_get_buffer");
	yang_avcodec_find_decoder =
			(AVCodec* (*)(enum AVCodecID id)) m_lib.loadFunction(
					"avcodec_find_decoder");
	yang_avcodec_find_decoder_by_name=(AVCodec *(*)(const char *name)) m_lib.loadFunction(
			"avcodec_find_decoder_by_name");
	yang_avcodec_alloc_context3 =
			(AVCodecContext* (*)(const AVCodec *codec)) m_lib.loadFunction(
					"avcodec_alloc_context3");
	yang_avcodec_send_packet = (int32_t (*)(AVCodecContext *avctx,
			const AVPacket *avpkt)) m_lib.loadFunction("avcodec_send_packet");
	yang_avcodec_receive_frame =
			(int32_t (*)(AVCodecContext *avctx, AVFrame *frame)) m_lib.loadFunction(
					"avcodec_receive_frame");
	yang_avcodec_close = (int32_t (*)(AVCodecContext *avctx)) m_lib.loadFunction(
			"avcodec_close");
}
void YangH2645VideoDecoderFfmpeg::unloadLib() {
	yang_avcodec_find_decoder_by_name=NULL;
	yang_av_free = NULL;
	yang_av_hwframe_ctx_alloc = NULL;
	yang_av_hwframe_ctx_init = NULL;
	yang_av_buffer_ref = NULL;
	yang_av_malloc = NULL;
	yang_av_hwdevice_ctx_create = NULL;
	yang_avcodec_open2 = NULL;
	yang_av_frame_alloc = NULL;
	yang_av_image_get_buffer_size = NULL;
	yang_av_image_fill_arrays = NULL;
	yang_av_init_packet = NULL;
	yang_av_hwframe_get_buffer = NULL;
	yang_avcodec_find_decoder = NULL;
	yang_avcodec_alloc_context3 = NULL;
	yang_avcodec_send_packet = NULL;
	yang_avcodec_receive_frame = NULL;
	yang_av_hwframe_transfer_data = NULL;
	yang_av_frame_free = NULL;
	yang_avcodec_close = NULL;
}
#endif
void YangH2645VideoDecoderFfmpeg::getH265RtmpHeader(uint8_t *meta, uint8_t *src, int32_t *hLen) {
				uint8_t s[4];
				s[0]=0x00;
				s[1]=0x00;
				s[2]=0x00;
				s[3]=0x01;

				int32_t pos=0;
				int32_t vpsLen=*(meta+32);
				int32_t vpsPos=33;

				int32_t spsLen=*(meta+32+vpsLen+5);
				int32_t spsPos=32+vpsLen+5+1;

				int32_t ppsLen=*(meta+32+vpsLen+5+spsLen+5);
				int32_t ppsPos=32+vpsLen+5+spsLen+5+1;

				//printf("\n***************vpsLen=%d,spsLen=%d,ppsLen=%d\n",vpsLen,spsLen,ppsLen);
				memcpy(src,s,4);
				memcpy(src+4,meta+vpsPos,vpsLen);
				pos+=4+vpsLen;
				memcpy(src+pos,s,4);
				pos+=4;
				memcpy(src+pos,meta+spsPos,spsLen);
				pos+=spsLen;
				memcpy(src+pos,s,4);
				pos+=4;
				memcpy(src+pos,meta+ppsPos,ppsLen);
				pos+=ppsLen;
				*hLen=pos;
				//printf("\n***********************************\n");
				//for(int32_t i=0;i<pos;i++){
				//	if(i%50==0) printf("\n");
				//	printf("%02x,",*(src+i));
				//}
				//printf("\n***********************************\n");
}

void YangH2645VideoDecoderFfmpeg::getH264RtmpHeader(uint8_t *buf, uint8_t *src, int32_t *hLen) {
	int32_t spsLen = *(buf + 12) + 1;
	uint8_t *spsStart = buf + 13;
	int32_t ppsLen = *(spsStart + spsLen + 1) + 1;
	uint8_t *ppsStart = buf + 13 + spsLen + 2;
	*(src + 3) = 0x01;
	memcpy(src + 4, spsStart, spsLen);
	*(src + 4 + spsLen + 3) = 0x01;
	memcpy(src + 4 + spsLen + 4, ppsStart, ppsLen);
	*hLen = 8 + spsLen + ppsLen;

}
enum AVPixelFormat get_hw_format1(AVCodecContext *ctx,
		const enum AVPixelFormat *pix_fmts) {
	if(YangH2645VideoDecoderFfmpeg::g_hwType==YangV_Hw_Intel) return AV_PIX_FMT_VAAPI;
	if(YangH2645VideoDecoderFfmpeg::g_hwType==YangV_Hw_Nvdia) return AV_PIX_FMT_CUDA;
	if(YangH2645VideoDecoderFfmpeg::g_hwType==YangV_Hw_Android) return AV_PIX_FMT_MEDIACODEC;
	//return AV_PIX_FMT_VAAPI;
	return AV_PIX_FMT_VAAPI;
	/** const enum AVPixelFormat *p;

	 for (p = pix_fmts; *p != -1; p++) {
	 if (*p == hw_pix_fmt)
	 return *p;
	 }

	 fprintf(stderr, "Failed to get HW surface format.\n");
	 return AV_PIX_FMT_NONE;**/
}

int32_t YangH2645VideoDecoderFfmpeg::set_hwframe_ctx(AVPixelFormat ctxformat,AVPixelFormat swformat,YangVideoInfo *yvp,AVCodecContext *ctx,
		AVBufferRef *hw_device_ctx, int32_t pwid, int32_t phei) {
	AVBufferRef *hw_frames_ref;
	AVHWFramesContext *frames_ctx = NULL;
	int32_t err = 0;

	if (!(hw_frames_ref = yang_av_hwframe_ctx_alloc(hw_device_ctx))) {
		printf("Failed to create hw frame context.\n");
		return -1;
	}
	frames_ctx = (AVHWFramesContext*) (hw_frames_ref->data);
	frames_ctx->format = ctxformat;
	frames_ctx->sw_format = swformat;

	frames_ctx->width = pwid;
	frames_ctx->height = phei;
	//frames_ctx->initial_pool_size = 20;
	if ((err = yang_av_hwframe_ctx_init(hw_frames_ref)) < 0) {
		printf("Failed to initialize VAAPI frame context.Error code: %d\n",
				ret);
		yang_av_buffer_unref(&hw_frames_ref);
		return err;
	}
	ctx->hw_frames_ctx = yang_av_buffer_ref(hw_frames_ref);
	ctx->hw_device_ctx = yang_av_buffer_ref(hw_device_ctx);
	// ctx->hwaccel_flags=1;
	if (!ctx->hw_frames_ctx)
		err = AVERROR(ENOMEM);

	yang_av_buffer_unref(&hw_frames_ref);
	return err;
}

YangH2645VideoDecoderFfmpeg::YangH2645VideoDecoderFfmpeg(YangVideoInfo *pini,YangVideoEncDecType pencdectype) {
	m_encDecType= pencdectype;
	m_ini=pini;
	usingHw = 0;	//pini->usingHwDec==2?1:0;
	if(pini->videoDecHwType>0) usingHw=1;

	m_buffer=NULL;
	m_bufLen=0;

	g_hwType=(YangVideoHwType)pini->videoDecHwType;
	m_bitDepth=pini->bitDepth;
	//printf("\n*****YangH264Decoder***********************************FFmpeg..%d\n",usingVaapi);
	m_width = 0;
	m_height = 0;
	m_frame = NULL;
	yLen = 0;
	uLen = 0;
	allLen = 0;
	buffer = NULL;
	ret = 0;
	m_codec = NULL;

	hw_device_ctx = NULL;
	frame_mem_gpu = NULL;
#ifndef _WIN32
	unloadLib();
#endif
	//m_yvp=NULL;
	//tmp_frame;
}
YangH2645VideoDecoderFfmpeg::~YangH2645VideoDecoderFfmpeg() {
	m_ini=NULL;
	if(m_buffer) delete[] m_buffer;
	m_buffer=NULL;
	decode_close();
#ifndef _WIN32
	unloadLib();
	m_lib.unloadObject();
	m_lib1.unloadObject();
#endif

}
YangVideoHwType YangH2645VideoDecoderFfmpeg::g_hwType=YangV_Hw_Intel;
void  YangH2645VideoDecoderFfmpeg::parseHeader(uint8_t *p,int32_t pLen,int32_t *pwid,int32_t *phei,int32_t *pfps){

	AVCodec *t_codec = yang_avcodec_find_decoder(AV_CODEC_ID_H265);
	AVCodecContext*	t_codecCtx = yang_avcodec_alloc_context3(t_codec);
	t_codecCtx->extradata = (uint8_t*) yang_av_malloc(pLen + AV_INPUT_BUFFER_PADDING_SIZE);
	t_codecCtx->extradata_size = pLen;
	memcpy(t_codecCtx->extradata, p, pLen);
	int32_t ret = yang_avcodec_open2(t_codecCtx, t_codec, NULL);
		if (ret < 0)
			printf("\navcodec_open2 failure................\n");

		*pwid=t_codecCtx->width;
		*phei=t_codecCtx->height;
		*pfps=t_codecCtx->time_base.den;///t_codecCtx->time_base.num;

		yang_av_free(t_codecCtx->extradata);
		t_codecCtx->extradata=NULL;
		t_codecCtx->extradata_size = 0;
		yang_avcodec_close(t_codecCtx);
		yang_av_free(t_codecCtx);
		t_codecCtx=NULL;
		t_codec=NULL;
}
void YangH2645VideoDecoderFfmpeg::parseRtmpHeader(uint8_t *p, int32_t pLen, int32_t *pwid,
		int32_t *phei, int32_t *pfps) {

	uint8_t headers[128];
	memset(headers, 0, 128);
	int32_t headerLen = 0;
	if(m_encDecType==Yang_VED_264){
		getH264RtmpHeader(p, headers, &headerLen);
		  YangH264Header h264header;
		h264header.parseRtmpHeader(p);
		*pwid = h264header.width;
		*phei  = h264header.height;
		*pfps = h264header.fps;
	}else if(m_encDecType==Yang_VED_265) {
		getH265RtmpHeader(p, headers, &headerLen);
		parseHeader(headers,headerLen,pwid,phei,pfps);

	}
	m_width = *pwid;
	m_height= *phei ;

	if(!m_buffer) m_buffer=new uint8_t[m_width*m_height*3/2];

	int32_t bitLen=(m_bitDepth==8?1:2);
	//m_yvp->initSdlWin(1,&m_yvp->rects[0], m_width, m_height, 0, 0);
	yLen = m_width * m_height*bitLen;
	uLen = yLen / 4;
	allLen = yLen * 3 / 2;


	m_codecCtx->extradata = (uint8_t*) yang_av_malloc(headerLen + AV_INPUT_BUFFER_PADDING_SIZE);
	m_codecCtx->extradata_size = headerLen;
	memcpy(m_codecCtx->extradata, headers, headerLen);

	m_codecCtx->width = m_width;
	m_codecCtx->height = m_height;
	//m_codecCtx->profile = 66;
	//avcodec_find_decoder_by_name
	if (usingHw) {
		AVPixelFormat ctxformat,swformat;
		if(m_ini->videoDecHwType==YangV_Hw_Intel) ctxformat = AV_PIX_FMT_VAAPI;
		if(m_ini->videoDecHwType==YangV_Hw_Nvdia) ctxformat = AV_PIX_FMT_CUDA;
		if(m_ini->videoDecHwType==YangV_Hw_Android) ctxformat = AV_PIX_FMT_MEDIACODEC;
			if(m_ini->bitDepth==8) swformat = AV_PIX_FMT_NV12;
			if(m_ini->bitDepth==10) swformat = AV_PIX_FMT_P010;
			if(m_ini->bitDepth==16) swformat = AV_PIX_FMT_P016;
		if ((ret = set_hwframe_ctx(ctxformat,swformat,m_ini,m_codecCtx, hw_device_ctx, m_width, m_height))
				< 0) {
			printf("Failed to set hwframe context.\n");
			//goto close;
		}
		m_codecCtx->get_format = get_hw_format1;
	}

	ret = yang_avcodec_open2(m_codecCtx, m_codec, NULL);
	if (ret < 0)
		printf("\navcodec_open2 failure................\n");
	AVPixelFormat fmt=AV_PIX_FMT_YUV420P;
	if(m_bitDepth==8){
		if(usingHw) fmt=AV_PIX_FMT_NV12;
	}else if(m_bitDepth==10){
		fmt=AV_PIX_FMT_P010;
	}else if(m_bitDepth==16){
		fmt=AV_PIX_FMT_P016;
	}
	m_frame = yang_av_frame_alloc();
	// int32_t numBytes = avpicture_get_size(AV_PIX_FMT_YUV420P,m_width,m_height);
	int32_t numBytes = yang_av_image_get_buffer_size(fmt, m_width,m_height, 1);
	//int32_t numBytes = yang_av_image_get_buffer_size(AV_PIX_FMT_NV12, m_width,m_height, 1);
	buffer = (uint8_t*) yang_av_malloc(numBytes * sizeof(uint8_t));
	// 将分配的数据缓存空间和AVFrame关联起来
	//avpicture_fill((AVPicture *)m_frame, buffer, AV_PIX_FMT_YUV420P,m_width,m_height);av_image_fill_arrays

	if (usingHw) {
		yang_av_image_fill_arrays(m_frame->data, m_frame->linesize, buffer,
				fmt, m_width, m_height, 1);
		yang_av_init_packet(&packet);
		frame_mem_gpu = yang_av_frame_alloc();
		frame_mem_gpu->format = m_codecCtx->pix_fmt;
		frame_mem_gpu->width = m_codecCtx->width;
		frame_mem_gpu->height = m_codecCtx->height;
		ret = yang_av_hwframe_get_buffer(m_codecCtx->hw_frames_ctx,frame_mem_gpu, 0);
		if (ret < 0)
			printf("\nERROR:av_hwframe_get_buffer failure!\n");
	} else {
		yang_av_image_fill_arrays(m_frame->data, m_frame->linesize, buffer,
				fmt, m_width, m_height, 1);
		yang_av_init_packet(&packet);
	}

	m_isInit = 1;
}

void YangH2645VideoDecoderFfmpeg::init() {
	//AVCodecID codec_id = AV_CODEC_ID_H264;
	// av_register_all();
	// avcodec_register_all();
	// avcodec_register(AV_CODEC_ID_H264);
#ifndef _WIN32
	m_lib.loadObject("libavcodec");
	m_lib1.loadObject("libavutil");
	loadLib();
#endif

	if(usingHw){
		if(m_encDecType==Yang_VED_264){
			if(m_ini->videoDecHwType==YangV_Hw_Intel)	m_codec = yang_avcodec_find_decoder_by_name("h264_vaapi");//avcodec_find_encoder(AV_CODEC_ID_H264);
			if(m_ini->videoDecHwType==YangV_Hw_Nvdia)	m_codec = yang_avcodec_find_decoder_by_name("h264_nvdec");
			if(m_ini->videoDecHwType==YangV_Hw_Android)	m_codec = yang_avcodec_find_decoder_by_name("h264_mediacodec");
		}else if(m_encDecType==Yang_VED_265){
			if(m_ini->videoDecHwType==YangV_Hw_Intel)	m_codec = yang_avcodec_find_decoder_by_name("hevc_vaapi");
			if(m_ini->videoDecHwType==YangV_Hw_Nvdia) 	m_codec = yang_avcodec_find_decoder_by_name("hevc_nvdec");
			if(m_ini->videoDecHwType==YangV_Hw_Android)	m_codec = yang_avcodec_find_decoder_by_name("hevc_mediacodec");
		}
	}else{
		if(m_encDecType==Yang_VED_264){
			m_codec = yang_avcodec_find_decoder(AV_CODEC_ID_H264);
		}else if(m_encDecType==Yang_VED_265){
			m_codec = yang_avcodec_find_decoder(AV_CODEC_ID_H265);
		}
	}
	m_codecCtx = yang_avcodec_alloc_context3(m_codec);
}
/**int32_t YangH2645VideoDecoderFfmpeg::decode( int32_t isIframe,
		uint8_t *pData, int32_t nSize, uint8_t *dest, int32_t *pnFrameReturned) {
	if (usingHw)
		decode_2(isIframe, pData, nSize,  dest,	pnFrameReturned);
	else
		decode_1( isIframe, pData, nSize, dest,	pnFrameReturned);
	return 1;
}**/
int32_t YangH2645VideoDecoderFfmpeg::decode(YangFrame* videoFrame,YangYuvType yuvtype,YangDecoderCallback* pcallback){
	if (usingHw)
			return decode_2(videoFrame,yuvtype,pcallback);
		else
			return decode_1(videoFrame,yuvtype,pcallback);

}
int32_t YangH2645VideoDecoderFfmpeg::decode_1(YangFrame* videoFrame,YangYuvType yuvtype,YangDecoderCallback* pcallback) {
	packet.data = videoFrame->payload;
	packet.size = videoFrame->nb;
	ret = yang_avcodec_send_packet(m_codecCtx, &packet);
	if (ret != 0) {
		m_bufLen= 0;
		return Yang_Ok;
	}
	ret = yang_avcodec_receive_frame(m_codecCtx, m_frame);
	if (ret != 0) {
		m_bufLen = 0;
		return Yang_Ok;
	}
	memcpy(m_buffer, m_frame->data[0], yLen);
	if(yuvtype==YangYv12){
		memcpy(m_buffer + yLen, m_frame->data[2], uLen);
		memcpy(m_buffer + yLen + uLen, m_frame->data[1], uLen);
	}else if(yuvtype==YangI420){
		memcpy(m_buffer + yLen, m_frame->data[1], uLen);
		memcpy(m_buffer + yLen + uLen, m_frame->data[2], uLen);
	}
	m_bufLen= allLen;
	videoFrame->payload=m_buffer;
	videoFrame->nb=m_bufLen;
	if(pcallback) pcallback->onVideoData(videoFrame);
	return 1;
}
int32_t YangH2645VideoDecoderFfmpeg::decode_2(YangFrame* videoFrame,YangYuvType yuvtype,YangDecoderCallback* pcallback) {
	packet.data = videoFrame->payload;
		packet.size = videoFrame->nb;
	ret = yang_avcodec_send_packet(m_codecCtx, &packet);
	if (ret != 0) {
		m_bufLen= 0;
		return Yang_Ok;
	}

	ret = yang_avcodec_receive_frame(m_codecCtx, frame_mem_gpu);

	if (ret != 0) {
		m_bufLen= 0;
		return Yang_Ok;
	}
	yang_av_hwframe_transfer_data(m_frame, frame_mem_gpu, 0);
	memcpy(m_buffer, m_frame->data[0], yLen);
	if(yuvtype==YangYv12){
		memcpy(m_buffer + yLen, m_frame->data[1], uLen);
		memcpy(m_buffer + yLen + uLen, m_frame->data[1]+uLen, uLen);
	}else if(yuvtype==YangI420){
		memcpy(m_buffer + yLen, m_frame->data[1]+uLen, uLen);
		memcpy(m_buffer + yLen + uLen, m_frame->data[1], uLen);
	}
	//memcpy(m_buffer + yLen, m_frame->data[1], uLen * 2);
	m_bufLen = allLen;
	videoFrame->payload=m_buffer;
	videoFrame->nb=m_bufLen;
	if(pcallback) pcallback->onVideoData(videoFrame);

	return 1;
}
void YangH2645VideoDecoderFfmpeg::decode_close() {
	if (usingHw) {
		yang_av_buffer_unref(&hw_device_ctx);
		yang_av_frame_free(&frame_mem_gpu);
	}

	yang_av_frame_free(&m_frame);
	m_frame = NULL;
	if (m_codecCtx) {
		yang_avcodec_close(m_codecCtx);
		yang_av_free(m_codecCtx);
	}

	m_codecCtx = NULL;
	if (buffer)
		yang_av_free(buffer);
	buffer = NULL;

}

