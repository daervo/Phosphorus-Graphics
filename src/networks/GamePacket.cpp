/*
 * GamePacket.cpp
 *
 *  Created on: 16 Oct 2014
 *      Author: Ervin
 */

#include <networks/GamePacket.h>
#include <networks/networkConstants.hpp>
#include <networks/Converters.h>

namespace phosphorus {

GamePacket::GamePacket() {
	// TODO Auto-generated constructor stub

}

GamePacket::~GamePacket() {
	// TODO Auto-generated destructor stub
}

void GamePacket::createUpdatePacket(char* buffer, int playerId, glm::vec3 position, glm::vec3 direction, float hp){
	floatToNetworkString(buffer, UPDATE, COMMAND);
	floatToNetworkString(buffer, playerId, PLAYER_NUMBER);
	floatToNetworkString(buffer, position.x, PLAYER_POSITION_X);
	floatToNetworkString(buffer, position.y, PLAYER_POSITION_Y);
	floatToNetworkString(buffer, position.z, PLAYER_POSITION_Z);
	floatToNetworkString(buffer, direction.x, PLAYER_DIRECTION_X);
	floatToNetworkString(buffer, direction.y, PLAYER_DIRECTION_Y);
	floatToNetworkString(buffer, direction.z, PLAYER_DIRECTION_Z);;
	floatToNetworkString(buffer, hp, PLAYER_HP);
}

void GamePacket::createRegistrationPacket(char* buffer, int gameNum){
	floatToNetworkString(buffer, REGISTER, COMMAND);
	floatToNetworkString(buffer, gameNum, GAME_NUM);

}

void GamePacket::createNewGamePacket(char* buffer, int gameNum){
	floatToNetworkString(buffer, NEW_GAME, COMMAND);
	floatToNetworkString(buffer, gameNum, GAME_NUM);

}

} /* namespace phosphorus */
