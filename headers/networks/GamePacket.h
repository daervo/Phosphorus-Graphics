/*
 * GamePacket.h
 *
 *  Created on: 16 Oct 2014
 *      Author: Ervin
 */

#ifndef GAMEPACKET_H_
#define GAMEPACKET_H_
#include <glm/glm.hpp>
#define SIZE 36

namespace phosphorus {

class GamePacket {
	int const COMMAND  = 0;
	int const PLAYER_ID = 4;
	int const PLAYER_POSITION = 8;
	int const PLAYER_DIRECTION = 20;
	int const PLAYER_HP = 32;


	int const UPDATE  = 0;
public:
	GamePacket();
	virtual ~GamePacket();
	void createUpdatePacket(char* buffer, int playerId, glm::vec3 position, glm::vec3 direction, float hp);
};

} /* namespace phosphorus */

#endif /* GAMEPACKET_H_ */
