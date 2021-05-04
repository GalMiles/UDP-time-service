#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")
#include <winsock2.h>            //socket library
#include <string.h>             //string library

#define TIME_PORT	27015 //server port

//creating client:
//1- create socket
//2- server address
//3 - sent to(SEND message)
//4 - receive - (receive massage)
//5 - close socket

void sendMessage(char* sendBuff, SOCKET connSocket, sockaddr_in server);
void receiveMeassage(char* recvBuff, SOCKET connSocket, sockaddr_in server);

void main()
{
	WSAData wsaData;
	if (NO_ERROR != WSAStartup(MAKEWORD(2, 2), &wsaData))    //load DLL  - first action in windowes
	{
		cout << "Time Client: Error at WSAStartup()\n";
		return;
	}

	//creating socket-internet,untrasted, UDP
	SOCKET connSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);  

	//if system can't create socket
	if (INVALID_SOCKET == connSocket)   
	{
		cout << "Time Client: Error at socket(): " << WSAGetLastError() << endl;     //WSAGetLastError() - return last error that occured
		WSACleanup();                                                                //clean DLL we finish
		return;
	}

	//if we're here we have socket, and now we need server address to connect to server
	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");   //look back
	server.sin_port = htons(TIME_PORT);

	//create send and receive data
	int choice = 0;
	bool flag = true; 
	char sendBuff[255];
	char recvBuff[255];
	

	cout << " Please enter your choice:" << endl;
	cout << " 1 - General time" << endl;
	cout << " 2 - Time only" << endl;
	cout << " 3 - Time in seconds" << endl;
	cout << " 4 - Delay Estamination" << endl;
	cout << " 5 - Measure RTT" << endl;
	cout << " 6 - Time in hours" << endl;
	cout << " 7 - Year only" << endl;
	cout << " 8 - Date only" << endl;
	cout << " 9 - Seconds since beginning of the month" << endl;
	cout << " 10 - Week of the year" << endl;
	cout << " 11 - Summer clock or Winte clock" << endl;
	cout << " 12 - Time only in City" << endl;
	cout << " 13 - Meaure time lap" << endl;
	cout << " 14 - Exit" << endl;

	while (choice != 14)
	{
		cin >> choice;
		if (choice == 1)
		{
			strcpy(sendBuff, "1");
			sendMessage(sendBuff, connSocket, server);
			receiveMeassage(recvBuff, connSocket, server);
		}
		else if (choice == 2)
		{
			strcpy(sendBuff, "2");
			sendMessage(sendBuff, connSocket, server);
			receiveMeassage(recvBuff, connSocket, server);
		}
		else if (choice == 3)
		{
			strcpy(sendBuff, "3");
			sendMessage(sendBuff, connSocket, server);
			receiveMeassage(recvBuff, connSocket, server);
		}
		else if (choice == 4)
		{
			int totalSum = 0;
			int timeStamp;
			int nextTimeStamp;
			int subTimeStamps;

			for (int i = 0; i < 100; i++)   //send 100 messages 
			{
				strcpy(sendBuff, "4");
				sendMessage(sendBuff, connSocket, server);
			}

			receiveMeassage(recvBuff, connSocket, server);  //receive first message
			timeStamp = atoi(recvBuff);

			for (int i = 1; i < 100; i++)  //receive 99 messages
			{
				receiveMeassage(recvBuff, connSocket, server);  //receive next message
				nextTimeStamp = atoi(recvBuff);          
				subTimeStamps = timeStamp - nextTimeStamp;      //calculate sub
				totalSum = totalSum + subTimeStamps;            //add to sum

				timeStamp = atoi(recvBuff);                   
			}
			double resTimeStamps = totalSum/100;
			cout << "The Client to Server delay estamination is:" << resTimeStamps << endl;
			
		}
		else if (choice == 5)
		{
			int sendTime;
			int recvTime;
			int subTimes;
			int totalSum = 0;

			for (int i = 0; i < 100; i++)   //send one and receive one
			{
				strcpy(sendBuff, "5");
				sendMessage(sendBuff, connSocket, server);
				sendTime = GetTickCount();
				receiveMeassage(recvBuff, connSocket, server);
				recvTime = GetTickCount();

				subTimes = recvTime - sendTime;
				totalSum = totalSum + subTimes;
			}
			double resTime = totalSum / 100;
			cout << "The measure RTT is:" << resTime << endl;

		}
		else if (choice == 6)
		{
			strcpy(sendBuff, "6");
			sendMessage(sendBuff, connSocket, server);
			receiveMeassage(recvBuff, connSocket, server);
		}
		else if (choice == 7)
		{
			strcpy(sendBuff, "7");
			sendMessage(sendBuff, connSocket, server);
			receiveMeassage(recvBuff, connSocket, server);
		}
		else if (choice == 8)
		{
			strcpy(sendBuff, "8");
			sendMessage(sendBuff, connSocket, server);
			receiveMeassage(recvBuff, connSocket, server);
		}
		else if (choice == 9)
		{
			strcpy(sendBuff, "9");
			sendMessage(sendBuff, connSocket, server);
			receiveMeassage(recvBuff, connSocket, server);
		}
		else if (choice == 10)
		{
			strcpy(sendBuff, "10");
			sendMessage(sendBuff, connSocket, server);
			receiveMeassage(recvBuff, connSocket, server);
		}
		else if (choice == 11)
		{
			strcpy(sendBuff, "11");
			sendMessage(sendBuff, connSocket, server);
			receiveMeassage(recvBuff, connSocket, server);
		}
		else if (choice == 12)
		{
			char city[255];
			cout << "Please choose a city:" << endl;
			cin >> city;
			if (strcmp(city,"Tokyo")==0 )
			{
				strcpy(sendBuff, "121");
			}
			else if (strcmp(city, "Melbourne") == 0)
			{
				strcpy(sendBuff, "122");
			}
			else if (strcmp(city, "San-Francisco") == 0)
			{
				strcpy(sendBuff, "123");
			}
			else if (strcmp(city, "Porto") == 0)
			{
				strcpy(sendBuff, "124");
			}
			else
			{
				strcpy(sendBuff, "125");
			}
			sendMessage(sendBuff, connSocket, server);
			receiveMeassage(recvBuff, connSocket, server);
		}
		else if (choice == 13)
		{
			strcpy(sendBuff, "13");
			sendMessage(sendBuff, connSocket, server);
			receiveMeassage(recvBuff, connSocket, server);
		}

		else if(choice == 14)
			return; //exit
		
		// Closing connections and Winsock.
	}
	 

	cout << "Time Client: Closing Connection.\n";
	closesocket(connSocket);

	system("pause");



}
void sendMessage(char* sendBuff, SOCKET connSocket, sockaddr_in server)
{
	//send the SEND massage and the socket to the server

	int bytesSent = 0;    //how much bytes sent

	bytesSent = sendto(connSocket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr*)&server, sizeof(server));
	if (SOCKET_ERROR == bytesSent) //error check
	{
		cout << "Time Client: Error at sendto(): " << WSAGetLastError() << endl;
		closesocket(connSocket);  //close socket
		WSACleanup();             //clean DLL
		return;
	}

	//printing the massage
	cout << "Time Client: Sent: " << bytesSent << "/" << strlen(sendBuff) << " bytes of \"" << sendBuff << "\" message.\n";
}
void receiveMeassage(char* recvBuff, SOCKET connSocket, sockaddr_in server)
{
	//getting the RECEIVE massage
	int bytesRecv = 0;
	bytesRecv = recv(connSocket, recvBuff, 255, 0);
	if (SOCKET_ERROR == bytesRecv) //error check
	{
		cout << "Time Client: Error at recv(): " << WSAGetLastError() << endl;
		closesocket(connSocket);
		WSACleanup();
		return;
	}

	recvBuff[bytesRecv] = '\0'; //add \0 to do str
	//print the receiver message
	cout << "Time Client: Recieved: " << recvBuff << endl;
}
