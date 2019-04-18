#pragma once
#ifndef TCPSOCKET_H
#define TCPSOCKET_H
#include <ws2tcpip.h>
#include <WinSock2.h>
#include <memory>

#pragma comment(lib, "wsock32.lib")
#pragma comment(lib, "Ws2_32.lib")

class SocketAddress;
class TCPSocket {
public:
	std::shared_ptr<TCPSocket> acceptCon(SocketAddress& inFromAddress) const;
	~TCPSocket();
	int connectTo(const SocketAddress& inAddress) const;
	int bindTo(const SocketAddress& inToAddress) const;
	int listenTo(int inBackLog = 32) const;
	int sendTo(void* inData, int inLen) const;

	int receiveFrom(void* inBuffer, int inLen) const;
	TCPSocket(SOCKET inSocket) : socket_(inSocket) {}
private:
	friend class SocketUtil;
	SOCKET socket_;
};
typedef std::shared_ptr<TCPSocket> TCPSocketPtr;
#endif