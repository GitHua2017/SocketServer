#pragma once
#include <string>
typedef unsigned int value_type;
enum MSG_TYPE
{
	MSG_TEST_NONE,
	MSG_TEST_1,
	MSG_TEST_2,
	MSG_TEST_3,
	MSG_TEST_4,
};

typedef struct Card {
	char c;
	value_type suit;
	value_type value;
}card_type;

class CNetMsg
{
public:
	enum { BUFFERSIZE = 1024, };
	typedef union MsgData
	{
		char buffer[BUFFERSIZE];
		struct
		{
			unsigned int nMsgSize;
			unsigned int nMsgType;
		};
	};
public:
	CNetMsg();
	virtual ~CNetMsg();
	virtual void Create(const char* pMsgBuf, int nSize);
	virtual void Process(void);

	// STATIC METHOD
	static CNetMsg* CreateMsg(const char* pMsgBuf, int nSize);
	static unsigned int GetSize(const char* pMsgBuf, int nSize);
	static unsigned int GetType(const char* pMsgBuf, int nSize);
	
	MsgData* m_pMsgData;
};

class CMsgName1 : public CNetMsg
{
public:
	struct strMsgName1
	{
		unsigned int unType;
		char name[256];
	}*m_pInfo;
public:
	CMsgName1();
	virtual ~CMsgName1();

	virtual void Create(const char* pMsgBuf, int nSize);
	void CreateMsg(unsigned int unType, const char* pName);
	void Send(void);
	virtual void Process(void);
};