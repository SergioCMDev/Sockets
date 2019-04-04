#pragma once
#ifndef SOCKET_ADDRESS_H
#define SOCKET_ADDRESS_H

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
class SocketAddress {
public:
	SocketAddress(uint32_t address, uint16_t port) {
		getAsSockAddrIn()->sin_family = AF_INET;
		getAsSockAddrIn()->sin_addr.S_un.S_addr = htonl(address);
		getAsSockAddrIn()->sin_port = htons(port);
	}
	SocketAddress(const sockaddr& sockAddr) {
		memcpy(&sockAddr_, &sockAddr, sizeof(sockaddr));
	}

	SocketAddress(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint16_t port) {
		getAsSockAddrIn()->sin_family = AF_INET;
		getAsSockAddrIn()->sin_addr.S_un.S_un_b.s_b1 = a;
		getAsSockAddrIn()->sin_addr.S_un.S_un_b.s_b2 = b;
		getAsSockAddrIn()->sin_addr.S_un.S_un_b.s_b3 = c;
		getAsSockAddrIn()->sin_addr.S_un.S_un_b.s_b4 = d;
		getAsSockAddrIn()->sin_port = htons(port);
	}


	size_t getSize() const { return sizeof(sockaddr); }
	sockaddr sockAddr_;
private:
	sockaddr_in* getAsSockAddrIn() {
		return reinterpret_cast<sockaddr_in*>(&sockAddr_);
	}

};
//typedef std::shared_ptr<SocketAddress> SocketAddressPtr;
#endif