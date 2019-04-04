#include <iostream>
#include <string>
#include <thread>
//#include <vector>
//#include <mutex>
//#include "Client.h"
//#include <winsock2.h>.
//#include <ws2tcpip.h>.
#include"SocketAddress.h"
#include"TCPSocket.h"
//#include "StatusGame.h"
#include "StateGame.h"
#include "Game.h"
//#include "Server.h"



int main() {
	//WSAStartup();
	std::cout << "Empieza Cliente" << std::endl;
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	////Client
	SOCKET socketStart = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in localhostAddrs;
	localhostAddrs.sin_family = AF_INET;
	localhostAddrs.sin_port = htons(1234);
	//InetPton(AF_INET, "0.0.0.0", &localhostAddrs.sin_addr);
	InetPton(AF_INET, "192.168.1.50", &localhostAddrs.sin_addr);


	//partida.movePlayer2 = StateGame::rock;
	//Game::CheckWinner(partida);

	SocketAddress address(localhostAddrs.sin_addr.S_un.S_addr, localhostAddrs.sin_port);
	//SocketAddress address = SocketAddress(12700001,80);
	int val = 2;
	TCPSocket tcpSocket(socketStart);
	//tcpSocket.bindTo(address);
	int status = tcpSocket.connectTo(address);
	if (status == NO_ERROR) {
		StatusGame partida;
		partida.movePlayer1 = StateGame::lizard;
		std::string s = StatusGame::serialize(partida);
		const char* charstring = s.c_str();
		tcpSocket.sendTo(const_cast<char*>(charstring), 1);
	}

	shutdown(socketStart, SD_SEND);
	closesocket(socketStart);


	//partida.movePlayer1 = StateGame::lizard;
	//partida.movePlayer2 = StateGame::paper;
	//Game::CheckWinner(partida);
	//partida.movePlayer1 = StateGame::lizard;
	//partida.movePlayer2 = StateGame::scissor;
	//Game::CheckWinner(partida);
	//std::string s = StatusGame::serialize(partida);
	//StatusGame partida1;
	//const char* charstring = s.c_str();

	//partida1 = StatusGame::deserialize(charstring);
	//Game::CheckWinner(partida1);

	getchar();
}