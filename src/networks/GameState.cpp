/*
 * GameState.cpp
 *
 *  Created on: 16 Oct 2014
 *      Author: Ervin
 */

#include <networks/GameState.h>

namespace phosphorus {

GameState::GameState(int _gameNum):
	gameNum(_gameNum)
{
}

GameState::~GameState() {
	// TODO Auto-generated destructor stub
}

void GameState::updateState(char* buffer, int player){
	int playerOffset = player*PLAYER_PACKET_SIZE;
	std::cout<<"player id is ("<<PLAYER_0_ID + playerOffset <<")"<<(int)buffer[PLAYER_0_ID]<<std::endl;
	gameStateBuffer[PLAYER_0_ID + playerOffset] = (int)buffer[PLAYER_0_ID];

	//set player position
	std::cout<<"player position is ("<<PLAYER_0_POSITION + playerOffset <<")"<<(float)buffer[PLAYER_0_POSITION]<<" "<<(float)buffer[PLAYER_0_POSITION + 4]<<" "
			<<(float)buffer[PLAYER_0_POSITION + 8]<<std::endl;
	gameStateBuffer[PLAYER_0_POSITION + playerOffset] = (float)buffer[PLAYER_0_POSITION];
	gameStateBuffer[PLAYER_0_POSITION + playerOffset+4] = (float)buffer[PLAYER_0_POSITION+4];
	gameStateBuffer[PLAYER_0_POSITION + playerOffset+8] = (float)buffer[PLAYER_0_POSITION+8];

	//set player direction
	std::cout<<"player position is ("<<PLAYER_0_DIRECTION + playerOffset <<")"<<(float)buffer[PLAYER_0_DIRECTION]<<" "<<(float)buffer[PLAYER_0_DIRECTION + 4]<<" "
			<<(float)buffer[PLAYER_0_DIRECTION + 8]<<std::endl;
	gameStateBuffer[PLAYER_0_DIRECTION + playerOffset] = (float)buffer[PLAYER_0_DIRECTION];
	gameStateBuffer[PLAYER_0_DIRECTION + playerOffset+4] = (float)buffer[PLAYER_0_DIRECTION+4];
	gameStateBuffer[PLAYER_0_DIRECTION + playerOffset+8] = buffer[PLAYER_0_DIRECTION+8];

	//set player hp
	std::cout<<"player hp is ("<<PLAYER_0_HP + playerOffset <<")"<<(float)buffer[PLAYER_0_HP]<<std::endl;
	gameStateBuffer[PLAYER_0_HP + playerOffset] = (float)buffer[PLAYER_0_HP];

	for (int i = PLAYER_0_ID + playerOffset; i < 36; i+=4){
		std::cout<<(float)gameStateBuffer[i]<<std::endl;
	}

}

} /* namespace phosphorus */
