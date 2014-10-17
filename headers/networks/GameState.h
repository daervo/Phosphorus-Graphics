/*
 * GameState.h
 *
 *  Created on: 16 Oct 2014
 *      Author: Ervin
 */

#ifndef GAMESTATE_H_
#define GAMESTATE_H_
#include <iostream>
#define GAME_STATE_SIZE 76
#define PLAYER_PACKET_SIZE 36

namespace phosphorus {

class GameState {
	int gameNum;

	char gameStateBuffer[GAME_STATE_SIZE];

	//attributes

public:
	int const GS_ID = 0;
	int const PLAYER_0_ID = 4;
	int const PLAYER_0_POSITION = 8;
	int const PLAYER_0_DIRECTION = 20;
	int const PLAYER_0_HP = 32;

	GameState(int _gameNum);
	virtual ~GameState();

	int getGameNum(){
		return gameNum;
	}


	void updateState(char* buffer, int player);

	void updateState(char* buffer){
		for (int i = 0; i < GAME_STATE_SIZE; i++){
			gameStateBuffer[i] = buffer[i];
		}
	}

	void getState(char* buffer){
		for (int i = 0; i < GAME_STATE_SIZE; i++){
			buffer[i] = gameStateBuffer[i];
		}
	}

	float get(int attribute, int playerNum){
		return (float) gameStateBuffer[attribute + playerNum * PLAYER_PACKET_SIZE];
	}

};

} /* namespace phosphorus */

#endif /* GAMESTATE_H_ */
