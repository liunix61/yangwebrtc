#ifndef __YangVideoEncoderHandle__
#define __YangVideoEncoderHandle__
#include "YangVideoEncoder.h"
#include "stdint.h"

#include <vector>

#include "yangutil/buffer/YangVideoEncoderBuffer.h"
#include "yangutil/buffer/YangVideoBuffer.h"
#include "yangutil/sys/YangIni.h"
#include "yangutil/sys/YangThread.h"

using namespace std;
class YangVideoEncoderHandle:public YangThread,public YangEncoderCallback
{
public:
	YangVideoEncoderHandle(YangVideoInfo *pini,YangVideoEncInfo *enc);
	~YangVideoEncoderHandle(void);

private:
	int32_t m_isInit;

public:
	int32_t m_isStart;
	int32_t m_uid;
	void init();
	void stop();
	void setOutVideoBuffer(YangVideoEncoderBuffer * pvl);
	void setInVideoBuffer(YangVideoBuffer *pvl);

	//void setRoomState(int32_t pst);
	void setVideoMetaData(YangVideoMeta *pvmd);
	void sendKeyframe();
	void onVideoData(YangFrame* pframe);
	void onAudioData(YangFrame* pframe);
protected:
	void run();
	void stopLoop();
	void startLoop();
	void saveFile(char *fileName, uint8_t *pBuffer, long BufferLen);

private:
	YangVideoBuffer *m_in_videoBuffer;
	YangVideoEncoderBuffer *m_out_videoBuffer;
	YangVideoMeta *m_vmd;
	int32_t m_isConvert;
	YangVideoInfo *m_para;
	YangVideoEncInfo *m_enc;
	int32_t m_sendKeyframe;

};
#endif