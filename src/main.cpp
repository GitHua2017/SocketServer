#include <Winsock2.h>
#include <cstdio>
#include <vector>
#include <iostream>
#pragma comment(lib,"ws2_32.lib")
#include "NetMsg.h"
#include "socket.h"

#define BUFFER_SIZE 1024

void TestForSocket(void)
{
	char sendBuf[BUFFER_SIZE] = { 0 };//�������ͻ��˵��ַ���
	char recvBuf[BUFFER_SIZE] = { 0 };//���ܿͻ��˷��ص��ַ���
	int nRevSize = 0;
	CSocket soc;
	soc.Listen();
	memset(recvBuf, 0, BUFFER_SIZE);
	soc.Receive(recvBuf, nRevSize);
	card_type card;
	memcpy(&card, recvBuf, nRevSize);
	std::cout << nRevSize<< " : ";
	std::cout << card.c << " " << card.suit << " " << card.value << std::endl;
}

void TestForSocket1(void)
{
	struct strMsgName1
	{
		unsigned int unType;
		char name[256];
	}myMsg;

	char buff[32] = "this is my message!";
	myMsg.unType = 19;
	memcpy(myMsg.name, buff, strlen(buff));

	union MsgData
	{
		char buffer[BUFFER_SIZE];
		struct
		{
			unsigned int nMsgSize;
			unsigned int nMsgType;
		};
	}myMsgSend;
	int lenUn = sizeof(unsigned int);
	int lenstr = sizeof(myMsg);
	myMsgSend.nMsgSize = sizeof(myMsg) + sizeof(unsigned int) * 2;
	myMsgSend.nMsgType = myMsg.unType;
	memcpy(myMsgSend.buffer + sizeof(unsigned int) * 2, &myMsg, sizeof(myMsg));

	char sendBuf[BUFFER_SIZE] = { 0 };//�������ͻ��˵��ַ���
	memcpy(sendBuf, &myMsgSend, sizeof(myMsgSend));

	unsigned int recvLen = CNetMsg::GetSize(sendBuf, sizeof(sendBuf));
	unsigned int recvType = CNetMsg::GetType(sendBuf, sizeof(sendBuf));

	CNetMsg* pMsg = CNetMsg::CreateMsg(sendBuf, sizeof(sendBuf));
	if (pMsg) {
		pMsg->Process();
	}
	if (pMsg)
	{
		delete(pMsg);
	}
}


void main()
{
	{
		TestForSocket1();
	}
	std::cout << "main()" << std::endl;
// 	std::vector<card_type> vec_card;
// 	WSADATA wsaData;
// 	SOCKET sockServer;
// 	SOCKADDR_IN addrServer;
// 	SOCKET sockClient;
// 	SOCKADDR_IN addrClient;
// 	WSAStartup(MAKEWORD(2, 2), &wsaData);
// 	sockServer = socket(AF_INET, SOCK_STREAM, 0);
// 	addrServer.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//INADDR_ANY��ʾ�κ�IP
// 	addrServer.sin_family = AF_INET;
// 	addrServer.sin_port = htons(6000);//�󶨶˿�6000
// 	bind(sockServer, (SOCKADDR*)&addrServer, sizeof(SOCKADDR));
// 
// 	//Listen������
// 	listen(sockServer, 5);//5Ϊ�ȴ�������Ŀ
// 	printf("������������,������...\n");
// 	int len = sizeof(SOCKADDR);
// 	char sendBuf[BUFFER_SIZE] = { 0 };//�������ͻ��˵��ַ���
// 	char recvBuf[BUFFER_SIZE] = { 0 };//���ܿͻ��˷��ص��ַ���
// 	strcpy_s(sendBuf, "I have receive success!\n");
// 
// 					 //���������̣�ֱ���пͻ�����������Ϊֹ
// 	sockClient = accept(sockServer, (SOCKADDR*)&addrClient, &len);
// 	memset(recvBuf, 0, BUFFER_SIZE);
// 	int len1 = recv(sockClient, recvBuf, BUFFER_SIZE, 0); // ���ܹ������� 
// 	card_type stuTemp;
// 	std::vector<card_type> vecTemp;
// 	char *pTemp = recvBuf;
// 	for (int i = 0; i < len1 / sizeof(stuTemp); ++i)
// 	{
// 		memset(&stuTemp, 0, sizeof(stuTemp));
// 		memcpy(&stuTemp, pTemp, sizeof(stuTemp));
// 		vecTemp.push_back(stuTemp);
// 		pTemp += sizeof(stuTemp);
// 	}
// 	memcpy(&vec_card, recvBuf, len1);
// 	while (1)
// 	{
// 		//���ղ���ӡ�ͻ�������
// 		memset(recvBuf, 0, sizeof(recvBuf));
// 		recv(sockClient, recvBuf, 10, 0);
// 		printf("%s", recvBuf);
// 		if (0 == strcmp(recvBuf, "exit\n"))
// 		{
// 			break;
// 		}
// 		send(sockClient, sendBuf, sizeof(sendBuf), 0);
// 	}
// 
// 	//�ر�socket
// 	closesocket(sockClient);
// 	WSACleanup();
	system("pause");
}