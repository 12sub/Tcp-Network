#include "tcp-server.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	//PCWSTR ip_adr;
	int port;

	if (argc < 3) {
		printf("Usage %s %d: <ip_address> <port> \n", argv[1], argv[2]);
	}
	const char *ip_adr = argv[1];
	int wideStrLength = MultiByteToWideChar(CP_UTF8, 0, ip_adr, -1, NULL, 0);
	wchar_t* wideString = new wchar_t[wideStrLength];
	int newIpAdr = MultiByteToWideChar(CP_UTF8, 0, ip_adr, -1, wideString, wideStrLength);
	delete[] wideString;
	port = atoi(argv[2]);

	//Declaring initial variables
	WSADATA wsaData;
	int wsaerr, af, sock_type, protocol;
	WORD wVersionRequested = MAKEWORD(2, 2);
	char  wsaStatus = wsaData.szSystemStatus[WSASYS_STATUS_LEN + 1];
	SOCKET clientSocket = INVALID_SOCKET;

	// Initializing WSAStartup
	wsaerr = WSAStartup(wVersionRequested, &wsaData);
	if (wsaerr != 0) {
		printf("Winsock dll is not found! Error: %ld \n  ", WSAGetLastError);
		return EXIT_FAILURE;
	}
	else
	{
		/*Winsock is ready and avaliable for use */
		printf("Winsock dll is found!\n");
	}
	//Declaring Address_family, socket type and protocol
	af = AF_INET;
	sock_type = SOCK_STREAM;
	protocol = IPPROTO_TCP;
	int clientConnect;
	sockaddr_in clientService;
	clientService.sin_family = AF_INET;

	// Creating socket
	clientSocket = socket(af, sock_type, protocol);
	if (clientSocket == INVALID_SOCKET)
	{
		printf("Error at socket(): %ld\n", WSAGetLastError);
		WSACleanup();
		return EXIT_FAILURE;
	}
	else
	{
		printf("Socket() is Created and OK!\n");
	}

	// Accepting Sockets
	InetPton(AF_INET, (PCWSTR) ip_adr, &clientService.sin_addr.s_addr);
	clientService.sin_port = htons(port);
	clientConnect = connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService));
	if (clientConnect == SOCKET_ERROR)
	{
		printf("Client: Failed to connect!\n");
		WSACleanup();
		return 0;
	}
	else
	{
		printf("Client: Connection Established\n");
		printf("Client can now send and receive data! \n");
	}

	//int recvbuflen = DEFAULT_BUFLEN;
	char buflen[200];
	char RecvBuffer[200] = "";
	int iResult;

	printf("Enter your message: ");
	cin.getline(buflen, 200);
	
	iResult = send(clientSocket, buflen, (int)strlen(buflen), 0);
	if (iResult == SOCKET_ERROR) {
		printf("Server send error %ld.\n", WSAGetLastError);
		return EXIT_FAILURE;
	}
	else {
		printf("Server: sent %ld bytes\n", iResult);
	}

	int byteCount = recv(clientSocket, RecvBuffer, 200, 0);
	if (byteCount < 0) {
		printf("Client: Error %ld. \n", WSAGetLastError);
		return 0;
	}
	else
	{
		printf("Received Data: %s \n", RecvBuffer);
	}


	return EXIT_SUCCESS;
}