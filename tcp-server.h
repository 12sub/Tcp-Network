#ifndef UNICODE
#define UNICODE
#define InetPton
#endif

#define WIN32_LEAN_AND_MEAN
#define DEFAULT_BUFLEN 512


#include <WinSock2.h>
#include <Windows.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#pragma comment(lib, "ws2_32.lib")
