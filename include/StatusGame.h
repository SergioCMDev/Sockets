#include <String>
#include "Constants.h"


class StatusGame {
public:
	int winner = -1; //0 first player, 1 second player
	enum StateGame movePlayer2; //state-> piedra, papel, tijeras, lagarto,spock
	enum StateGame movePlayer1; //state-> piedra, papel, tijeras, lagarto,spock
	int numberGames = 0;
	int winnerGames[MAX_GAMES];
	//static const char* serialize(StatusGame partida);
	static std::string serialize(StatusGame partida);
	static StatusGame deserialize(const char* statusGame);
private:
	static  int getInt(std::string value);
};

