#pragma once

#include <Winsock2.h>
#pragma comment(lib,"ws2_32.lib")

class CSocket
{
public:
	CSocket();
	~CSocket();

	void Listen(void);
	void Receive(void* pData, int& nSize);
	void Send(char* pData, int nSize);

private:
	SOCKET m_sockServer;
	SOCKET m_sockClient;
};
