/*
 * GamePacket.h
 *
 *  Created on: 16 Oct 2014
 *      Author: Ervin
 */

#ifndef GAMEPACKET_H_
#define GAMEPACKET_H_
#include <glm/glm.hpp>
#include <networks/networkConstants.hpp>

namespace phosphorus {

class GamePacket {

public:
	GamePacket();
	virtual ~GamePacket();
	void createUpdatePacket(char* buffer, int playerId, glm::vec3 position, glm::vec3 direction, float hp);
};

} /* namespace phosphorus */

#endif /* GAMEPACKET_H_ */
