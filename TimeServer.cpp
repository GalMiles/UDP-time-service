#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")
#include <winsock2.h>
#include <string.h>
#include <time.h>
#include <Windows.h>

#define TIME_PORT	27015 //server port

#define UTC 0   //
#define JST 9  //Japan Standart Time
#define AEST 10    //Australian Eastern Standard Time
#define PST  (-7)     //Pacific Standart Time - San Francisco
#define WET  0     //Western European Time - Porto 


//1 - creating socket
//2 - server address
//3 - bind
//4 - while : receivefrom
//5 - creating answer
//6 - send to

void receiveMessage(char* recvBuff, SOCKET m_socket, sockaddr* client_addr);
void sendMessage(char* sendBuff, SOCKET m_socket, sockaddr* client_addr);
void GetTime(char* sendBuff);
void GetTimeWithoutDate(char* sendBuff);
void GetTimeSinceEpoch(char* sendBuff);
void GetClientToServerDelayEstimation(char* sendBuff);
void MeasureRTT(char* sendBuff);
void GetTimeWithoutDateOrSeconds(char* sendBuff);
char* GetYear();
void GetMonthAndDay(char* sendBuff);
void GetSecondsSinceBeginingOfMonth(char* sendBuff);
void GetWeekOfYear(char* sendBuff);
void GetDaylightSavings(char* sendBuff);
void GetTimeWithoutDateInCity(char* sendBuff, char *recvBuff);
void MeasureTimeLap(char* sendBuff, time_t* timer);

void main()
{
	WSAData wsaData;
	if (NO_ERROR != WSAStartup(MAKEWORD(2, 2), &wsaData))                         //load DLL
	{
		cout << "Time Server: Error at WSAStartup()\n";
		return;
	}

	//creating socket
	SOCKET m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (INVALID_SOCKET == m_socket) //check errors
	{
		cout << "Time Server: Error at socket(): " << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}
	
	//creating server address
	sockaddr_in serverService;
	serverService.sin_family = AF_INET;
	serverService.sin_addr.s_addr = INADDR_ANY;
	serverService.sin_port = htons(TIME_PORT);
	
	//bind the socket to client's request
	//connect the socket to the server address
	if (SOCKET_ERROR == bind(m_socket, (SOCKADDR*)&serverService, sizeof(serverService)))     
	{
		cout << "Time Server: Error at bind(): " << WSAGetLastError() << endl;
		closesocket(m_socket);
		WSACleanup();
		return;
	}

	//create send and receive data
	sockaddr client_addr;              //client address
	char sendBuff[255];
	char recvBuff[255];
	time_t serverTimer = NULL;
	time_t currentServerTime;

	cout << "Time Server: Wait for clients' requests.\n";

	while (true)
	{ 
		receiveMessage(recvBuff, m_socket, &client_addr);

		if (serverTimer != NULL)
		{
			currentServerTime = time(NULL);
			if (difftime(currentServerTime, serverTimer) > 180)
			{
				serverTimer = NULL;
			}
		}

		if (strcmp(recvBuff, "1") == 0)
		{
			GetTime(sendBuff);
		}
		else if (strcmp(recvBuff, "2") == 0)
		{
			GetTimeWithoutDate(sendBuff);
		}
		else if (strcmp(recvBuff, "3") == 0)
		{
			GetTimeSinceEpoch(sendBuff);
		}
		else if (strcmp(recvBuff, "4") == 0)
		{
			GetClientToServerDelayEstimation(sendBuff);
		}
		else if (strcmp(recvBuff, "5") == 0)
		{
			MeasureRTT(sendBuff);
		}
		else if (strcmp(recvBuff, "6") == 0)
		{
			GetTimeWithoutDateOrSeconds(sendBuff);
				
		}
		else if (strcmp(recvBuff, "7") == 0)
		{
			strcpy(sendBuff, GetYear());

		}
		else if (strcmp(recvBuff, "8") == 0)
		{
			GetMonthAndDay(sendBuff);

		}
		else if (strcmp(recvBuff, "9") == 0)
		{
			GetSecondsSinceBeginingOfMonth(sendBuff);
		}
		else if (strcmp(recvBuff, "10") == 0)
		{
			GetWeekOfYear(sendBuff);
		}
		else if (strcmp(recvBuff, "11") == 0)
		{
			GetDaylightSavings(sendBuff);
		}
		else if ((strcmp(recvBuff, "121") == 0) || (strcmp(recvBuff, "122") == 0) || (strcmp(recvBuff, "123") == 0) || (strcmp(recvBuff, "124") == 0) ||(strcmp(recvBuff, "125") == 0) )
		{
			GetTimeWithoutDateInCity(sendBuff, recvBuff);
		}
		else if ((strcmp(recvBuff, "13") == 0))
		{
			if (serverTimer == NULL)
			{
				serverTimer = time(NULL);
				strcpy(sendBuff, "Start timer");
			}
			else
				MeasureTimeLap(sendBuff, &serverTimer);
		}
		
		sendMessage(sendBuff, m_socket, &client_addr);

		
	}

		cout << "Time Server: Closing Connection.\n";
		closesocket(m_socket);
		WSACleanup();
}

void GetTime(char* sendBuff)
{
	time_t timer;   //vairable
	time(&timer);  //time function-number of seconds from 1/1/1970

	strcpy(sendBuff, "The general time is: ");
	strcat(sendBuff, ctime(&timer));//ctime-convert time from sec to date
}
void GetTimeWithoutDate(char* sendBuff)
{
	time_t timer;   //vairable
	time(&timer);  //time function-number of seconds from 1/1/1970
	strcpy(sendBuff, "The time is: ");
	struct tm* info;
	info = localtime(&timer);
	strftime(sendBuff, 255, "The time is: %H:%M:%S", info);
}
void GetTimeSinceEpoch(char* sendBuff)
{
	time_t timer;   //vairable
	time(&timer);  //time function-number of seconds from 1/1/1970
	sprintf(sendBuff, "The time in seconds since 1.1.1970 is: %d", timer);

}
void GetClientToServerDelayEstimation(char* sendBuff)
{
	snprintf(sendBuff, 255, "%d", GetTickCount64());
}
void MeasureRTT(char* sendBuff)
{
	strcpy(sendBuff, "Received!");
}
void GetTimeWithoutDateOrSeconds(char *sendBuff)
{
	time_t timer;   //vairable
	time(&timer);  //time function-number of seconds from 1/1/1970

	struct tm* info;
	info = localtime(&timer);
	strftime(sendBuff, 255, "The time in hours and minutes is: %H:%M", info);
}
char* GetYear()
{
	time_t timer;   //vairable
	time(&timer);  //time function-number of seconds from 1/1/1970

	char sendBuff[255];
	strcpy(sendBuff, "The year is: ");
	struct tm* info;
	info = localtime(&timer);

	char year[100];
	int realYear = 1900 + info->tm_year;
	_itoa(realYear, year, 10);
	strcat(sendBuff, year);
	return sendBuff;
}
void GetMonthAndDay(char *sendBuff)
{
	time_t timer;   //vairable
	time(&timer);  //time function-number of seconds from 1/1/1970

	strcpy(sendBuff, "The date in month and day is: ");
	char str1[255];

	strncpy(str1, ctime(&timer), 10);
	str1[10] = '\0';
	strcat(sendBuff, str1);
}
void GetSecondsSinceBeginingOfMonth(char* sendBuff)
{
	time_t timer;   //vairable
	time(&timer);  //time function-number of seconds from 1/1/1970

	int days;
	int hours;
	int secSum = 0;
	int secOfDay;
	int minutes;
	char secArr[255];

	struct tm* info;
	info = localtime(&timer);

	days = info->tm_mday - 1;
	secSum = days * 24 * 60 * 60; //total sec from beginning of month to yesterday
	hours = info->tm_hour; //today's hours
	secOfDay = hours * 60 * 60;  //today's hours in sec
	minutes = info->tm_min; //today's minutes
	secOfDay = secOfDay + (minutes * 60); //today's hours+min in sec
	secOfDay = secOfDay + info->tm_sec; //sec of the last min
	secSum = secSum + secOfDay; //total sum

	_itoa(secSum, secArr, 10); //int to string
	strcpy(sendBuff, "The number of seconds since the beginning of the month is: ");
	strcat(sendBuff, secArr);
}
void GetWeekOfYear(char* sendBuff)
{
	time_t timer;   //vairable
	time(&timer);  //time function-number of seconds from 1/1/1970

	struct tm* info;
	info = localtime(&timer);

	char week[3]; //number of the week in range 1-48 only
	strcpy(sendBuff, "The number of week since the beginning of the year is: ");
	strftime(week, 3, "%U", info);
	strcat(sendBuff, week);

}
void GetDaylightSavings(char* sendBuff)
{
	time_t timer;   //vairable
	time(&timer);  //time function-number of seconds from 1/1/1970

	struct tm* info;
	info = localtime(&timer);

	int flag = info->tm_isdst;
	if (flag == 0) //no daylight saving
	{
		strcpy(sendBuff, "The daylight saving is off: 0");
	}
	else
		strcpy(sendBuff, "The daylight saving is on: 1"); 
}
void GetTimeWithoutDateInCity(char* sendBuff, char* recvBuff)
{
	time_t timer;
	time(&timer);
	struct tm* info;
	info = gmtime(&timer);
	int clock;
	if (strcmp(recvBuff, "121") == 0)
	{
		snprintf(sendBuff, 255, "Time in Tokyo: %2d:%02d", (info->tm_hour + JST) % 24, info->tm_min);
	}
	else if (strcmp(recvBuff, "122") == 0)
	{
		if (info->tm_isdst) //daylight saving
			snprintf(sendBuff, 255, "Time in Melbourne: %2d:%02d", (info->tm_hour + AEST) % 24, info->tm_min);
		else
			snprintf(sendBuff, 255, "Time in Melbourne: %2d:%02d", (info->tm_hour + AEST+1) % 24, info->tm_min);

	}
	else if (strcmp(recvBuff, "123") == 0)
	{
		if (info->tm_isdst) //daylight saving
			snprintf(sendBuff, 255, "Time in San-Francisco: %2d:%02d", (info->tm_hour + PST) % 24, info->tm_min);
		else
			snprintf(sendBuff, 255, "Time in San-Francisco: %2d:%02d", (info->tm_hour + PST - 1) % 24, info->tm_min);

	}
	else if (strcmp(recvBuff, "124") == 0)
	{
		if (info->tm_isdst) //daylight saving
			snprintf(sendBuff, 255, "Time in Porto: %2d:%02d", (info->tm_hour + WET) % 24, info->tm_min);
		else
			snprintf(sendBuff, 255, "Time in Porto: %2d:%02d", (info->tm_hour + WET - 1) % 24, info->tm_min);
	}
	else
	{
		snprintf(sendBuff, 255, "Global time(UTC): %2d:%02d", (info->tm_hour) % 24, info->tm_min);

	}

}
void MeasureTimeLap(char* sendBuff, time_t* timer)
{
	time_t currentTime = time(NULL);
	snprintf(sendBuff, 255, "%d Seconds", (int)difftime(currentTime, *(timer)));
	*(timer) = NULL;
}
void receiveMessage(char * recvBuff, SOCKET m_socket, sockaddr *client_addr)
{
	//create answer
	int client_addr_len = sizeof(*client_addr);
	int bytesRecv = 0;	

	bytesRecv = recvfrom(m_socket, recvBuff, 255, 0, client_addr, &client_addr_len);
	if (SOCKET_ERROR == bytesRecv) //error check
	{
		cout << "Time Server: Error at recvfrom(): " << WSAGetLastError() << endl;
		closesocket(m_socket);
		WSACleanup();
		return;
	}

	//create string from request
	recvBuff[bytesRecv] = '\0'; //add the null-terminating to make it a string     
	cout << "Time Server: Recieved: " << bytesRecv << " bytes of \"" << recvBuff << "\" message.\n";
}
void sendMessage(char* sendBuff, SOCKET m_socket, sockaddr *client_addr)
{
	int client_addr_len = sizeof(*client_addr);
	int bytesSent = 0;
	//creaing the answer message to client
	bytesSent = sendto(m_socket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr*)client_addr, client_addr_len);
	if (SOCKET_ERROR == bytesSent)
	{
		cout << "Time Server: Error at sendto(): " << WSAGetLastError() << endl;
		closesocket(m_socket);
		WSACleanup();
		return;
	}

	cout << "Time Server: Sent: " << bytesSent << "\\" << strlen(sendBuff) << " bytes of \"" << sendBuff << "\" message.\n";
	
}