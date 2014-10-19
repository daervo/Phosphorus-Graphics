/*
 * GameState.h
 *
 *  Created on: 16 Oct 2014
 *      Author: Ervin
 */

#ifndef GAMESTATE_H_
#define GAMESTATE_H_
#include <iostream>
#include <networks/networkConstants.hpp>
#include <networks/Converters.h>
#include <stdlib.h>

namespace phosphorus {

class GameState {
	int gameNum;

	std::array<char, GS_PACKET_SIZE> gameStateBuffer;

	//attributes

public:

	GameState(int _gameNum);
	virtual ~GameState();

	int getGameNum(){
		return gameNum;
	}


	void updateState(char* buffer, int player);

	void updateState(char* buffer){
		for (int i = 0; i < GS_PACKET_SIZE; i++){
			//gameStateBuffer[i] = buffer[i];
			gameStateBuffer.at(i) = networkStringToFloat(buffer, i);
		}
	}

	void getState(char* buffer){
		for (int i = 0; i < GS_PACKET_SIZE; i++){
			//buffer[i] = gameStateBuffer[i];
			floatToNetworkString(buffer, networkStringToFloat(gameStateBuffer.data(), i), i);
		}
	}

	float get(int attribute, int playerNum){
		return networkStringToFloat(gameStateBuffer.data(), attribute + playerNum * GAME_PACKET_SIZE);
	}

};

} /* namespace phosphorus */

#endif /* GAMESTATE_H_ */
