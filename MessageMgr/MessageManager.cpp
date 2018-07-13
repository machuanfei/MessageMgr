// MessageManager.cpp
#include "MessageManager.h"

MessageManager::MessageManager()
{
	memset(m_msgHandler, 0, sizeof(m_msgHandler));
	memset(m_msgHandlerEnable, 1, sizeof(m_msgHandlerEnable));
	memset(m_msgHandlerFilter, 0, sizeof(m_msgHandlerFilter));
}

MessageManager::~MessageManager()
{

}

bool MessageManager::init()
{
	// ����ģ��ע���ʱ�����������
	// �����̳�ģ��  �������õ��Ǿ�̬�����Ľ�ڣ� �Ժ���ע���̳���ص���Ϣ����regMsgHandler������ע���ˡ�
	//ShopMessage::regMsgHandler();  
	return true;
}

void MessageManager::unint()
{
	for (int i = 0; i < MsgId_Max; ++i )
	{
		if ( NULL != m_msgHandler[i])
		{
			delete m_msgHandler[i];
			m_msgHandler[i] = NULL;
		}
	}
}

void MessageManager::regMessageHandler(unsigned long msgId, MH_Base* mh)
{
	if (msgId >= MsgId_Max)
		return;
	if (m_msgHandler[msgId] != NULL)
	{
		// �˴�����һ�£� �����Ϣ���Ѿ�ע�����
		//ErrorLn(" msgId=" << msgId << " had register..");
	}
	m_msgHandler[msgId] = mh;
}

void MessageManager::setMessageHandlerEnable(unsigned long msgId, bool setting)
{
	if (msgId >= MsgId_Max)
		return;
	m_msgHandlerEnable[msgId] = (setting ? 1 : 0);
}

bool MessageManager::hasMessageHandler(unsigned long msgId) const
{
	return (msgId < MsgId_Max && m_msgHandler[msgId] != NULL);
}

void MessageManager::onMessage(const MessageHeader& hdr, const void* data, size_t len)
{
	if (hdr.msgId >= MsgId_Max)
		return;


	// ��Ϣ������
	MH_Base* pFunc = m_msgHandler[hdr.msgId];
	if (pFunc == NULL)
		return;
	
	// ����Ϣ����ʱ��ֹ�����ܴ���ˢ���ݲ���
	if (m_msgHandlerEnable[hdr.msgId] == 0)
	{
		// ��Ҫ����һ��
		//WarningLn(" msgId=" << hdr.msgId << " disable");
		return;
	}

	// ����Ϣ���ܱ������ˣ���������
	if (m_msgHandlerFilter[hdr.msgId] == 1)
	{
		// ��Ҫ����һ��
		//WarningLn("msgId = " << hdr.msgId << " filtered");
		return;
	}

	//--��Ϣ����
#ifdef _DEBUG
	(*pFunc)(data, len);
#else
	try
	{
		(*pFunc)(data, len);
	}
	catch (...)
	{
		ErrorLn("msgFun exect Exception, msgId=" << hdr.msgId << ", len=" << nLen);
	}
#endif
}