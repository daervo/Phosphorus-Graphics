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
	int playerOffset = player*GAME_PACKET_SIZE_WITHOUT_COMMAND;
	std::cout<<"player id is ("<<GS_PLAYER_NUMBER + playerOffset <<")"<<(int)networkStringToFloat(buffer, GS_PLAYER_NUMBER)<<std::endl;
	floatToNetworkString(gameStateBuffer, networkStringToFloat(buffer, GS_PLAYER_NUMBER), GS_PLAYER_NUMBER + playerOffset);

	//set player position
	std::cout<<"player position is ("<<GS_PLAYER_POSITION_X + playerOffset <<")"<<networkStringToFloat(buffer, GS_PLAYER_POSITION_X)<<" "<<networkStringToFloat(buffer, GS_PLAYER_POSITION_Y)<<" "
			<<networkStringToFloat(buffer, GS_PLAYER_POSITION_Z)<<std::endl;
	floatToNetworkString(gameStateBuffer, networkStringToFloat(buffer, GS_PLAYER_POSITION_X), GS_PLAYER_POSITION_X + playerOffset);
	floatToNetworkString(gameStateBuffer, networkStringToFloat(buffer, GS_PLAYER_POSITION_Y), GS_PLAYER_POSITION_Y + playerOffset);
	floatToNetworkString(gameStateBuffer, networkStringToFloat(buffer, GS_PLAYER_POSITION_Z), GS_PLAYER_POSITION_Z + playerOffset);

	//set player direction
	std::cout<<"player position is ("<<GS_PLAYER_DIRECTION_X + playerOffset <<")"<<networkStringToFloat(buffer, GS_PLAYER_DIRECTION_X)<<" "<<networkStringToFloat(buffer, GS_PLAYER_DIRECTION_Y)<<" "
			<<networkStringToFloat(buffer, GS_PLAYER_DIRECTION_Z)<<std::endl;
	floatToNetworkString(gameStateBuffer, networkStringToFloat(buffer, GS_PLAYER_DIRECTION_X), GS_PLAYER_DIRECTION_X + playerOffset);
	floatToNetworkString(gameStateBuffer, networkStringToFloat(buffer, GS_PLAYER_DIRECTION_Y), GS_PLAYER_DIRECTION_Y + playerOffset);
	floatToNetworkString(gameStateBuffer, networkStringToFloat(buffer, GS_PLAYER_DIRECTION_Z), GS_PLAYER_DIRECTION_Z + playerOffset);

	//set player hp
	std::cout<<"player hp is ("<<GS_PLAYER_HP + playerOffset <<")"<<networkStringToFloat(buffer, GS_PLAYER_HP)<<std::endl;
	floatToNetworkString(gameStateBuffer, networkStringToFloat(buffer, GS_PLAYER_HP), GS_PLAYER_HP + playerOffset);

}

} /* namespace phosphorus */
