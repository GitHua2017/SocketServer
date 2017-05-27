#include <string.h>
#include <iostream>

#include "NetMsg.h"

CNetMsg::CNetMsg()
{
	if (m_pMsgData)
	{
		delete(m_pMsgData);
		m_pMsgData = nullptr;
	}
	m_pMsgData = new MsgData;
	if (m_pMsgData)
	{
		memset(m_pMsgData, 0, BUFFERSIZE);
	}
}

CNetMsg::~CNetMsg()
{
	std::cout << "~CNetMsg()" << std::endl;
	if (m_pMsgData)
	{
		delete(m_pMsgData);
		m_pMsgData = nullptr;
	}
}


void CNetMsg::Create(const char* pMsgBuf, int nSize)
{

}

void CNetMsg::Process(void)
{
	std::cout << "CNetMst" << std::endl;
}

CNetMsg* CNetMsg::CreateMsg(const char* pMsgBuf, int nSize)
{
	CNetMsg* pMsg = nullptr;
	unsigned int unMsgType = CNetMsg::GetType(pMsgBuf, nSize);
	unsigned int unMsgSize = CNetMsg::GetSize(pMsgBuf, nSize);
	switch (unMsgType)
	{
	case MSG_TEST_1:
		pMsg = new CMsgName1;
		break;
	case 19:
		pMsg = new CMsgName1;
		break;
	default:
		break;
	}

	if (pMsg)
	{
		pMsg->Create(pMsgBuf, unMsgSize);
	}

	return pMsg;
}

unsigned int CNetMsg::GetSize(const char* pMsgBuf, int nSize)
{
// 	unsigned int* pUnMsg = (unsigned int*)pMsgBuf;
// 	return pUnMsg[0];
	return (*(unsigned int*)(pMsgBuf));
}

unsigned int CNetMsg::GetType(const char* pMsgBuf, int nSize)
{
	unsigned int* pUnMsg = (unsigned int*)pMsgBuf;
	return pUnMsg[1];
}

CMsgName1::CMsgName1()
{
	m_pInfo = nullptr;
}

CMsgName1::~CMsgName1()
{
	std::cout << "~CMsgName1()" << std::endl;
}

void CMsgName1::Create(const char* pMsgBuf, int nSize)
{
	memcpy(m_pMsgData->buffer, pMsgBuf, nSize);
	m_pInfo = (strMsgName1*)(m_pMsgData->buffer + sizeof(unsigned int) * 2);
}

void CMsgName1::CreateMsg(unsigned int unType, const char* pName)
{
	m_pInfo->unType = unType;
	strcpy_s(m_pInfo->name, strlen(pName) + 1, pName);
}

void CMsgName1::Send(void)
{
	//socClient.Send(m_pMsgData->buffer, len);
}

void CMsgName1::Process(void)
{
	// do something with the message data
	std::cout << "CMsgName1" << std::endl;
	if (nullptr == m_pInfo)
	{
		return;
	}
	std::cout << m_pInfo->unType << "  " << m_pInfo->name << std::endl;
}
