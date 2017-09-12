#include <iostream>

#include "socket.h"

CSocket::CSocket()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	m_sockServer = socket(AF_INET, SOCK_STREAM, 0);
}

CSocket::~CSocket()
{
	closesocket(m_sockClient);
	WSACleanup();
}

void CSocket::Listen(void)
{
	SOCKADDR_IN addrServer;
	SOCKADDR_IN addrClient;
	addrServer.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//INADDR_ANY表示任何IP
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(6000);//绑定端口6000
	bind(m_sockServer, (SOCKADDR*)&addrServer, sizeof(SOCKADDR));

	//Listen监听端
	listen(m_sockServer, 5);//5为等待连接数目
	std::cout << "服务器已启动,监听中...\n";
	int len = sizeof(SOCKADDR);

	//会阻塞进程，直到有客户端连接上来为止
	m_sockClient = accept(m_sockServer, (SOCKADDR*)&addrClient, &len);
	int mytest = 0;
}

void CSocket::Receive(void* pData, int& nSize)
{
	nSize = recv(m_sockClient, static_cast<char *>(pData), 1024, 0);
}

void CSocket::Send(char* pData, int nSize)
{
	send(m_sockClient, pData, nSize, 0);
}
