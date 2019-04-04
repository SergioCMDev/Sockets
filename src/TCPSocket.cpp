

#include"TCPSocket.h"
#include "SocketAddress.h"
#include <iostream>
#include "StatusGame.h"

TCPSocket::~TCPSocket() {

}
int TCPSocket::connectTo(const SocketAddress& inAddress) const {
	const int err = connect(socket_, &inAddress.sockAddr_, inAddress.getSize());
	if (err < 0) {
		std::cout << "Error Connecting Socket" << std::endl;
		return -WSAGetLastError();
	}
	return NO_ERROR;
}
int TCPSocket::bindTo(const SocketAddress& inBindAddress) const {

	const int error = bind(socket_, &inBindAddress.sockAddr_, inBindAddress.getSize());

	if (error != 0) {
		wchar_t *s = NULL;
		//FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,			NULL, WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&s, 0, NULL);
		std::cout << "Error Binding Socket" << std::endl;
		return WSAGetLastError();
	}
	return NO_ERROR;
}



int TCPSocket::listenTo(int inBackLog) const {
	const int err = listen(socket_, inBackLog);
	if (err < 0) {
		std::cout << "Error Listening Socket" << std::endl;
		return -WSAGetLastError();
	}
	return NO_ERROR;
}

std::shared_ptr<TCPSocket> TCPSocket::acceptCon(SocketAddress& inFromAddress) const
{
	int length = inFromAddress.getSize();
	SOCKET newSocket = accept(socket_, &inFromAddress.sockAddr_, &length);
	if (newSocket != INVALID_SOCKET) {
		return std::shared_ptr<TCPSocket>(new TCPSocket(newSocket));
	}
	else {
		std::cout << "Error Accepting Socket" << std::endl;
		return nullptr;
	}
}

int TCPSocket::sendTo(void* inData, int inLen) const {
	int bytesSentCount = send(socket_, static_cast<char*>(inData), inLen, 0);
	if (bytesSentCount < 0) {
		std::cout << "Error Sending Data" << std::endl;
		return -WSAGetLastError();
	}
	return bytesSentCount;
}

int TCPSocket::receiveFrom(void* inData, int inLen) const {
	int bytesReceivedCount = recv(socket_, static_cast<char*>(inData), inLen, 0);
	if (bytesReceivedCount < 0) {
		std::cout << "Error Receiving Data" << std::endl;
		return -WSAGetLastError();
	}
}
//typedef std::shared_ptr<TCPSocket> TCPSocketPtr;