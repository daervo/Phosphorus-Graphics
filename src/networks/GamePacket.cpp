/*
 * GamePacket.cpp
 *
 *  Created on: 16 Oct 2014
 *      Author: Ervin
 */

#include <networks/GamePacket.h>

namespace phosphorus {

GamePacket::GamePacket() {
	// TODO Auto-generated constructor stub

}

GamePacket::~GamePacket() {
	// TODO Auto-generated destructor stub
}

void GamePacket::createUpdatePacket(char* buffer, int playerId, glm::vec3 position, glm::vec3 direction, float hp){
	buffer[COMMAND] = UPDATE;
	buffer[PLAYER_ID] = playerId;
	buffer[PLAYER_POSITION] = position.x;
	buffer[PLAYER_POSITION+4] = position.y;
	buffer[PLAYER_POSITION+8] = position.z;
	buffer[PLAYER_DIRECTION] = direction.x;
	buffer[PLAYER_DIRECTION+4] = direction.y;
	buffer[PLAYER_DIRECTION+8] = direction.z;
	buffer[PLAYER_HP] = hp;
}

} /* namespace phosphorus */
