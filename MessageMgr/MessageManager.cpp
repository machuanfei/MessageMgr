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
	// 各个模块注册的时候在这里添加
	// 例如商城模块  这里我用的是静态函数的借口， 以后想注册商城相关的消息就在regMsgHandler函数里注册了。
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
		// 此处警告一下， 这个消息码已经注册过了
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


	// 消息处理函数
	MH_Base* pFunc = m_msgHandler[hdr.msgId];
	if (pFunc == NULL)
		return;
	
	// 该消息被临时禁止，可能存在刷数据操作
	if (m_msgHandlerEnable[hdr.msgId] == 0)
	{
		// 需要警告一下
		//WarningLn(" msgId=" << hdr.msgId << " disable");
		return;
	}

	// 该消息可能被过滤了，不做处理
	if (m_msgHandlerFilter[hdr.msgId] == 1)
	{
		// 需要警告一下
		//WarningLn("msgId = " << hdr.msgId << " filtered");
		return;
	}

	//--消息处理
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