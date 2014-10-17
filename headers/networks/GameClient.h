/*
 * GameClient.h
 *
 *  Created on: 16 Oct 2014
 *      Author: Ervin
 */

#ifndef GAMECLIENT_H_
#define GAMECLIENT_H_
#include <winsock.h>
#include <iostream>
#include "GamePacket.h"
#define CLIENT_PACKET_SIZE 36

namespace phosphorus {

class GameClient {

	SOCKET theSocket;
private:
public:
	int const PACKET_SIZE = CLIENT_PACKET_SIZE;
	int const REPLY_SIZE = 76;
	GameClient();
	virtual ~GameClient();
	bool startConnection(int port, std::string host);
	bool sendToServer(char* buffer, char* reply);
	void close();
};

} /* namespace phosphorus */

#endif /* GAMECLIENT_H_ */
