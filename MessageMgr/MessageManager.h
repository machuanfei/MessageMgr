//MessageManager.h
#ifndef __MessageMgr_h__
#define __MessageMgr_h__
#include <iostream>
#include "MH_Base.h"

/// 所有消息的消息头
struct MessageHeader
{
	unsigned short		msgKey;							/// 消息类型
	unsigned short		msgId;							/// 消息码
};


#define MsgId_Max 100		// 这里先顶一个消息id上限为100 的宏， 正式项目中药根据消息码的增加最大值也跟着增加
class MessageManager
{
public:
	MessageManager();
	~MessageManager();

public:
	virtual bool init();
	virtual void unint();

public:
	//--消息
	void regMessageHandler(unsigned long msgId, MH_Base* mh);
	void setMessageHandlerEnable(unsigned long msgId, bool setting);
	virtual bool hasMessageHandler(unsigned long msgId) const;
	virtual void onMessage(const MessageHeader& hdr, const void* data, size_t len);
protected:
	MH_Base*			m_msgHandler[MsgId_Max];			// 消息处理函数
	unsigned char		m_msgHandlerEnable[MsgId_Max];		//是否有效(1有效, 0无效)
	unsigned char		m_msgHandlerFilter[MsgId_Max];		//是否过滤(1过滤,0不过滤)
};

#endif
