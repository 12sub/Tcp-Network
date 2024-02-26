#include "tcp-server.h"

int main(int argc, char* argv[]) {
	//int newIpAdr;
	int port;

	if (argc < 3) {
		printf("Usage %s %d: <ip_address> <port> \n", argv[1], argv[2]);
	}
	const char* ip_adr = argv[1];
	int wideStrLength = MultiByteToWideChar(CP_UTF8, 0, ip_adr, -1, NULL, 0);
	wchar_t* wideString = new wchar_t[wideStrLength];
	int newIpAdr = MultiByteToWideChar(CP_UTF8, 0, ip_adr, -1, wideString, wideStrLength);
	delete[] wideString;
	port = atoi(argv[2]);

	WSADATA wsaData;
	int wsaerr, af;
	//int WSACleanup() = cleanUp;
	WORD wVersionRequested = MAKEWORD(2, 2);
	char  wsaStatus = wsaData.szSystemStatus[WSASYS_STATUS_LEN + 1];
	SOCKET serverSocket = INVALID_SOCKET;
	sockaddr_in service;
	PCSTR pszAddrString;
	PVOID pAddrBuf;
	int binder = 0;

	wsaerr = WSAStartup(wVersionRequested, &wsaData);
	if (wsaerr != 0) {
		printf("Winsock dll is not found! %d \n Error: %ld ", WSAGetLastError, wsaerr);
		return EXIT_FAILURE;
	}
	else
	{/* The Winsock DLL is acceptable. Proceed to use it. */
		printf("Winsock dll is found.\n");
	}
	af = AF_INET;
	service.sin_family = AF_INET;
	//sock_type = SOCK_STREAM;
	//protocol = IPPROTO_TCP;
	//service.sin_addr.s_addr = inet_addr("127.0.0.1");
	//pszAddrString =;
	//pAddrBuf = &service.sin_addr.s_addr;


	SOCKET acceptSocket;

	serverSocket = socket(af, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == INVALID_SOCKET)
	{
		printf("Error at socket(): %ld\n", WSAGetLastError);
		WSACleanup();
		return EXIT_FAILURE;
	}
	else
	{
		printf("Socket() is Created and OK!\n");
	}
	InetPton(AF_INET,(PCWSTR) newIpAdr, &service.sin_addr.s_addr);
	service.sin_port = htons(port);
	binder = bind(serverSocket, (SOCKADDR*)&service, sizeof(service));
	if (binder == SOCKET_ERROR)
	{
		printf("Bind connection failed! Error: %ld\n", WSAGetLastError);
		closesocket(serverSocket);
		WSACleanup();
		return EXIT_SUCCESS;
	}
	else {
		printf("Bind Connection Successful!\n");
	}

	if (listen(serverSocket, 1) == SOCKET_ERROR)
	{
		printf("Listening Function failed with error: %ld\n", WSAGetLastError);
	}
	else
		printf("Listening on socket for connections.......\n");

	// Accept the connection.
	acceptSocket = accept(serverSocket, NULL, NULL);
	if (acceptSocket == INVALID_SOCKET) {
		printf("accept failed with error: %ld\n", WSAGetLastError());
		closesocket(serverSocket);
		WSACleanup();
		return EXIT_FAILURE;
	}
	else
		printf("Client connected.\n");

	char RecvBuffer[200] = "";
	int byteCount = recv(acceptSocket, RecvBuffer, 200, 0);
	if (byteCount < 0) {
		printf("Client: Error %ld. \n", WSAGetLastError);
		return 0;
	}
	else
	{
		printf("Received Data: %s \n", RecvBuffer);
	}

	char buflen[200];
	int iResult;

	printf("Enter your message: ");
	cin.getline(buflen, 200);

	iResult = send(acceptSocket, buflen, (int)strlen(buflen), 0);
	if (iResult == SOCKET_ERROR) {
		printf("Server send error %ld.\n", WSAGetLastError);
		return EXIT_FAILURE;
	}
	else {
		printf("Server: sent %ld bytes\n", iResult);
	}


	WSACleanup();

	return EXIT_SUCCESS;
}