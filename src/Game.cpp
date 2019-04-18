#include "Game.h"
#include "StateGame.h"

void CheckWinnerPlayerOne(StatusGame &state) {
	if (state.movePlayer2 != state.movePlayer1) {
		state.winner = 1;

	}
}

void Game::CheckWinner(StatusGame& state)
{
	//1 first player, 2 second player
	//We assume the no player will win
	state.winner = 0;
	switch (state.movePlayer1) {
		//We check every combination in case the second player has really won
	case StateGame::lizard:
		if (state.movePlayer2 == StateGame::rock || state.movePlayer2 == StateGame::scissor) {
			state.winner = 2;
		}
		else {
			CheckWinnerPlayerOne(state);

		}
		break;
	case StateGame::paper:
		if (state.movePlayer2 == StateGame::scissor || state.movePlayer2 == StateGame::lizard) {
			state.winner = 2;
		}
		else {
			CheckWinnerPlayerOne(state);

		}
		break;

	case StateGame::rock:
		if (state.movePlayer2 == StateGame::paper || state.movePlayer2 == StateGame::spock) {
			state.winner = 2;
		}
		else {
			CheckWinnerPlayerOne(state);

		}
		break;

	case StateGame::scissor:
		if (state.movePlayer2 == StateGame::rock || state.movePlayer2 == StateGame::spock) {
			state.winner = 2;
		}
		else {
			CheckWinnerPlayerOne(state);

		}
		break;

	case StateGame::spock:
		if (state.movePlayer2 == StateGame::lizard || state.movePlayer2 == StateGame::paper) {
			state.winner = 2;
		}
		else {
			CheckWinnerPlayerOne(state);

		}
		break;

	}
	if (state.winner > 0) {
		state.winnerGames[state.numberGames] = state.winner;
		state.numberGames++;
	}
}