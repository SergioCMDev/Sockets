#include <iostream>
#include <thread>
#include "StateGame.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include"SocketAddress.h"
#include"TCPSocket.h"
#include <vector>
#include "Game.h"

int GetRandomInt(int max) {
	//return (rand() % max + 1); //Desde 1 a Max
	return (rand() % max); //Desde 0 a Max
}

void playWithClient(StatusGame partida, TCPSocket tcpSocket) {
	const char* buffer;
	while (partida.numberGames < MAX_GAMES) {

		StatusGame partida = StatusGame::deserialize(buffer);
		int move = GetRandomInt(MAX_GAMES / 2);
		partida.movePlayer2 = StateGame(move);
		Game::CheckWinner(partida);
		std::string s = StatusGame::serialize(partida);
		const char* charstring = s.c_str();
		std::cout << "Devolvemos " << buffer << std::endl;
		tcpSocket.sendTo(const_cast<char*>(charstring), 1);
		int receciveValue = tcpSocket.receiveFrom(&buffer, sizeof(buffer));
	}

}

int main() {
	std::cout << "Empieza Server" << std::endl;
	////Server

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET listeningSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	struct sockaddr_in saServer;
	memset(saServer.sin_zero, 0, sizeof(saServer.sin_zero));
	saServer.sin_family = AF_INET;
	saServer.sin_port = htons(5354);

	//saServer.sin_addr.S_un.S_addr = inet_addr("0.0.0.0");
	//saServer.sin_addr.S_un.S_addr = inet_addr("192.168.1.50"); 
	//saServer.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	InetPton(AF_INET, "127.0.0.1", &saServer.sin_addr);


	SocketAddress sa(saServer.sin_addr.S_un.S_addr, saServer.sin_port);
	std::vector<std::thread> threads[MAX_GAMES];
	int numberThread = 0;
	TCPSocket tcpSocket = TCPSocket::TCPSocket(listeningSocket);
	int res = tcpSocket.bindTo(sa);
	if (res == 0) {

		int listenStatus = -1;
		bool ok = true;
		while (ok) {

			listenStatus = tcpSocket.listenTo();
			if (listenStatus == NO_ERROR) {
				TCPSocketPtr tcp = tcpSocket.acceptCon(sa);

				const char* buffer;
				int receciveValue = tcpSocket.receiveFrom(&buffer, sizeof(buffer));
				if (receciveValue > 0) {
					//creamos nuevo thread
					std::cout << "RECIBIMOS " << buffer << std::endl;
					StatusGame partida = StatusGame::deserialize(buffer);
					std::thread threadWithPlayer(playWithClient, partida, tcpSocket);
					threads->push_back(threadWithPlayer);
					/*Game::CheckWinner(partida);
					std::string s = StatusGame::serialize(partida);*/
					//const char* charstring = s.c_str();
					//std::cout << "Devolvemos " << buffer << std::endl;
					//tcpSocket.sendTo(const_cast<char*>(charstring), 1);
				//	if (partida.numberGames = MAX_GAMES) {
				////Cerramos conexcion
				//	}
				}


			}
			else {
				ok != ok;
			}
		}
		for (size_t i = 0; i < threads->size(); i++)
		{
			threads->at(i).join();

		}
	}
	WSACleanup();
	shutdown(listeningSocket, SD_SEND);
	closesocket(listeningSocket);
};