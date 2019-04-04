#include <iostream>
#include <thread>
//#include <vector>
//#include <mutex>
//#include "Client.h"
#include <winsock2.h>.
#include <ws2tcpip.h>.
#include"SocketAddress.h"
#include"TCPSocket.h"

//#include "Server.h"



int main() {
	SOCKET tcpSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//WSAStartup();

	////CLIENT
	//sockaddr_in localhostAddrs;
	//localhostAddrs.sin_family = AF_INET;
	//localhostAddrs.sin_port = htons(80);
	//InetPton(AF_INET, "127.0.0.1", &localhostAddrs.sin_addr);

	//SocketAddress address = SocketAddress(localhostAddrs);
	//SocketAddress address = SocketAddress(12700001,80);
	


	TCPSocket tcpsocket(tcpSocket);
	tcpsocket.


	shutdown(tcpSocket, SD_SEND);
	closesocket(tcpSocket);
}