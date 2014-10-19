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
	int playerOffset = player*GAME_PACKET_SIZE;
	std::cout<<"player id is ("<<GS_PLAYER_NUMBER + playerOffset <<")"<<(int)buffer[GS_PLAYER_NUMBER]<<std::endl;
	//gameStateBuffer[GS_PLAYER_NUMBER + playerOffset] = networkStringToFloat(buffer, GS_PLAYER_NUMBER);

	//set player position
	std::cout<<"player position is ("<<GS_PLAYER_POSITION_X + playerOffset <<")"<<networkStringToFloat(buffer, GS_PLAYER_POSITION_X)<<" "<<networkStringToFloat(buffer, GS_PLAYER_POSITION_Y)<<" "
			<<networkStringToFloat(buffer, GS_PLAYER_POSITION_Z)<<std::endl;
	//gameStateBuffer[GS_PLAYER_POSITION_X] = networkStringToFloat(buffer, GS_PLAYER_POSITION_X);
	//gameStateBuffer[GS_PLAYER_POSITION_Y] = networkStringToFloat(buffer, GS_PLAYER_POSITION_Y);
	//gameStateBuffer[GS_PLAYER_POSITION_Z] = networkStringToFloat(buffer, GS_PLAYER_POSITION_Z);

	//set player direction
	std::cout<<"player position is ("<<GS_PLAYER_DIRECTION_X + playerOffset <<")"<<networkStringToFloat(buffer, GS_PLAYER_DIRECTION_X)<<" "<<networkStringToFloat(buffer, GS_PLAYER_DIRECTION_Y)<<" "
			<<networkStringToFloat(buffer, GS_PLAYER_DIRECTION_Z)<<std::endl;
	//gameStateBuffer[GS_PLAYER_DIRECTION_X] = networkStringToFloat(buffer, GS_PLAYER_DIRECTION_X);
	//gameStateBuffer[GS_PLAYER_DIRECTION_Y] = networkStringToFloat(buffer, GS_PLAYER_DIRECTION_Y);
	//gameStateBuffer[GS_PLAYER_DIRECTION_Z] = networkStringToFloat(buffer, GS_PLAYER_DIRECTION_Z);

	//set player hp
	std::cout<<"player hp is ("<<GS_PLAYER_HP + playerOffset <<")"<<networkStringToFloat(buffer, GS_PLAYER_HP)<<std::endl;
	//gameStateBuffer[GS_PLAYER_HP + playerOffset] = networkStringToFloat(buffer, GS_PLAYER_HP);

}

} /* namespace phosphorus */
