//MessageManager.h
#ifndef __MessageMgr_h__
#define __MessageMgr_h__
#include <iostream>
#include "MH_Base.h"

/// ������Ϣ����Ϣͷ
struct MessageHeader
{
	unsigned short		msgKey;							/// ��Ϣ����
	unsigned short		msgId;							/// ��Ϣ��
};


#define MsgId_Max 100		// �����ȶ�һ����Ϣid����Ϊ100 �ĺ꣬ ��ʽ��Ŀ��ҩ������Ϣ����������ֵҲ��������
class MessageManager
{
public:
	MessageManager();
	~MessageManager();

public:
	virtual bool init();
	virtual void unint();

public:
	//--��Ϣ
	void regMessageHandler(unsigned long msgId, MH_Base* mh);
	void setMessageHandlerEnable(unsigned long msgId, bool setting);
	virtual bool hasMessageHandler(unsigned long msgId) const;
	virtual void onMessage(const MessageHeader& hdr, const void* data, size_t len);
protected:
	MH_Base*			m_msgHandler[MsgId_Max];			// ��Ϣ������
	unsigned char		m_msgHandlerEnable[MsgId_Max];		//�Ƿ���Ч(1��Ч, 0��Ч)
	unsigned char		m_msgHandlerFilter[MsgId_Max];		//�Ƿ����(1����,0������)
};

#endif
