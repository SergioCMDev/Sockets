#include "StatusGame.h"
#include <sstream>

//const char* StatusGame::serialize(StatusGame partida) {
std::string StatusGame::serialize(StatusGame partida) {
	std::string strin1g;
	strin1g.append("{Winner: " + std::to_string(partida.winner));
	strin1g.append(";PlayerMove1: " + std::to_string(partida.movePlayer1));
	strin1g.append(";PlayerMove2: " + std::to_string(partida.movePlayer2));
	strin1g.append(";NumberOfGames: " + std::to_string(partida.numberGames));
	for (size_t i = 0; i < partida.numberGames; i++)
	{
		strin1g.append(";Winner->" + std::to_string(i) + ":" + std::to_string(partida.winnerGames[i]));
	}
	strin1g.append("}");
	return strin1g.c_str();
}


StatusGame StatusGame::deserialize(const char* statusGame) {
	std::string string = statusGame;
	size_t stringSize = string.size();
	StatusGame status;
	std::size_t winnerPos = string.find("Winner");
	std::size_t PlayerMove1Pos = string.find(";PlayerMove1");
	std::size_t PlayerMove2Pos = string.find(";PlayerMove2");
	std::size_t NumberOfGamesPos = string.find(";NumberOfGames");
	std::size_t PlayerWinnerPos = string.find(";Winner");

	std::string winnerValueText = string.substr(winnerPos, PlayerMove1Pos);
	std::string winnerValue = winnerValueText.substr(winnerValueText.size() - 2, 1);

	std::string playerMove1ValueText = string.substr(PlayerMove1Pos + 1, PlayerMove2Pos - PlayerMove1Pos);
	std::string playerMove1Value = playerMove1ValueText.substr(playerMove1ValueText.size() - 2, 1);
	status.movePlayer1 = StateGame(getInt(playerMove1Value));
	std::string playerMove2ValueText = string.substr(PlayerMove2Pos + 1, NumberOfGamesPos - PlayerMove2Pos);
	std::string playerMove2Value = playerMove2ValueText.substr(playerMove2ValueText.size() - 2, 1);
	status.movePlayer2 = StateGame(getInt(playerMove2Value));

	std::string NumberOfGamesPosValueText = string.substr(NumberOfGamesPos + 1, PlayerWinnerPos - NumberOfGamesPos);
	std::string NumberOfGamesPosValue = NumberOfGamesPosValueText.substr(NumberOfGamesPosValueText.size() - 3, 2); //NEED TRIM
	status.numberGames = getInt(NumberOfGamesPosValue);
	int offset = 0;
	for (size_t i = 0; i < status.numberGames; i++)
	{
		std::string GameWinedNumberAndWinner = string.substr(PlayerWinnerPos + 1 + 8 + offset, 3);
		std::string game = GameWinedNumberAndWinner.substr(0, 1);
		std::string winner = GameWinedNumberAndWinner.substr(2, 1);
		int playerWinner = getInt(winner);

		status.winnerGames[i] = playerWinner;
		offset += 12;
	}
	return status;
}

int StatusGame::getInt(std::string value) {
	int intValue;
	std::istringstream iss(value);
	iss >> intValue;
	return intValue;
}