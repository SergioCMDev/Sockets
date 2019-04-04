#include <iostream>
#include <string>
#include <thread>

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

//#include <winsock2.h>.
//#include <ws2tcpip.h>.
#include"SocketAddress.h"
#include"TCPSocket.h"

#include "StateGame.h"
#include "Game.h"




int GetWinnerOfGame(StatusGame partida) {
	int winner1 = 0;
	for (size_t i = 0; i < MAX_GAMES; i++)
	{
		if (partida.winnerGames[i] == 1) {
			winner1++;
		}
	}

	if (winner1 > MAX_GAMES / 2 + 1) {
		winner1 = 1;
	}
	else if (MAX_GAMES / 2 == winner1) {
		winner1 = 0;

	}
	else {
		winner1 = 2;

	}
	return winner1;
}

int GetRandomInt(int max) { 
	//return (rand() % max + 1); //Desde 1 a Max
	return (rand() % max); //Desde 0 a Max
}

int main() {
	srand(time(NULL));
	//StatusGame partida;
	//for (size_t i = 0; i < MAX_GAMES; i++)
	//{
	//	//std::cout << "Random "<< GetRandomInt(MAX_GAMES/2) << std::endl;
	//	partida.winnerGames[i] = GetRandomInt(2);
	//}
	//int  winner = GetWinnerOfGame(partida);
	//std::cout << "Winner is " << winner << std::endl;











	//OK
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


	SocketAddress address(localhostAddrs.sin_addr.S_un.S_addr, localhostAddrs.sin_port);
	TCPSocket tcpSocket(socketStart);
	int status = tcpSocket.connectTo(address);
	if (status == NO_ERROR) {
		StatusGame partida;

		while (partida.numberGames < MAX_GAMES) {
			int move = GetRandomInt(MAX_GAMES/2);
			partida.movePlayer1 = StateGame(move);
			std::string s = StatusGame::serialize(partida);
			const char* charstring = s.c_str();
			tcpSocket.sendTo(const_cast<char*>(charstring), sizeof(charstring));
			char* buffer;
			tcpSocket.receiveFrom(buffer, 1000);
			partida = StatusGame::deserialize(buffer);
		}

		//Game::CheckWinner(partida);
		int  winner = GetWinnerOfGame(partida);
		std::cout << "Winner is " << winner << std::endl;
	}
	else {

		std::cout << "Error" << std::endl;
	}
	shutdown(socketStart, SD_SEND);
	closesocket(socketStart);


	getchar();
}