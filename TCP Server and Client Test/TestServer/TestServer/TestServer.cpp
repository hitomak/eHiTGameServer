#include <iostream>
#include <string>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main()
{
	//Initialze winsock
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsOk = WSAStartup(ver, &wsData);
	if (wsOk != 0)
	{
		cerr << "Can't Iniialize winsock! Quitting" << endl;
		return 0;
	}

	//Create a socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
	{
		cerr << INVALID_SOCKET << "Can't Create a socket! Quitting" << endl;
		return 0;
	}

	//Bind the socket to an ip address and port
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY; //Could also use inet_pton...

	bind(listening, (sockaddr*)&hint, sizeof(hint));

	//Tell winsock the socket is for listening
	listen(listening, SOMAXCONN);

	//Wait for a connection
	sockaddr_in client;
	int clientSize = sizeof(client);

	SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

	char host[NI_MAXHOST]; //Client's remote Name
	char service[NI_MAXSERV]; // Service (i.e. port) the client is connect on

	ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(service, NI_MAXSERV);

	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0))
	{
		cout << host << "connection on port" << service << endl;
	}
	else
	{
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		cout << host << "connected on port" <<
			ntohs(client.sin_port) << endl;
	}

	//Close listening socket
	closesocket(listening);

	//While loop: accept and echo back to client
	char buf[4096];

	while (true)
	{
		ZeroMemory(buf, 4096);

		//Wait for client to send data
		int bytesRecived = recv(clientSocket, buf, 4096, 0);
		if (bytesRecived == SOCKET_ERROR)
		{
			cerr << SOCKET_ERROR << "eror in recv(). QUitting" << endl;
			break;
		}
		if (bytesRecived == 0)
		{
			cerr << "Client disconnected.quitting" << endl;
			break;
		}

		cout << string(buf, 0, bytesRecived) << endl;

		//Echo mesage back to client
		send(clientSocket, buf, bytesRecived + 1, 0);
	}

	//Close the socket
	closesocket(clientSocket);


	//Clenaup winsock
	WSACleanup();
}