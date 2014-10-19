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

	char gameStateBuffer[GS_PACKET_SIZE];

	//attributes

public:

	GameState(int _gameNum);
	virtual ~GameState();

	int getGameNum(){
		return gameNum;
	}


	void updateState(char* buffer, int player);

	void updateState(char* buffer){
		for (int i = 0; i < GS_PACKET_SIZE; i+=FLOAT_DIGIT_SIZE){
			//gameStateBuffer[i] = buffer[i];
			floatToNetworkString(gameStateBuffer, networkStringToFloat(buffer, i), i);
		}
	}

	void getState(char* buffer){
		for (int i = 0; i < GS_PACKET_SIZE; i+=FLOAT_DIGIT_SIZE){
			//buffer[i] = gameStateBuffer[i];
			floatToNetworkString(buffer, networkStringToFloat(gameStateBuffer, i), i);
			std::cout<< "sending "<<networkStringToFloat(gameStateBuffer, i)<<std::endl;
		}
	}

	float get(int attribute, int playerNum){
		return networkStringToFloat(gameStateBuffer, attribute + playerNum * GAME_PACKET_SIZE_WITHOUT_COMMAND);
	}
};

} /* namespace phosphorus */

#endif /* GAMESTATE_H_ */
