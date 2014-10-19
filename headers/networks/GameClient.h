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
#include <networks/networkConstants.hpp>

namespace phosphorus {

class GameClient {

	SOCKET theSocket;

public:
	GameClient();
	virtual ~GameClient();
	bool startConnection(int port, std::string host);
	bool sendToServer(char* buffer, char* reply);
	void close();
};

} /* namespace phosphorus */

#endif /* GAMECLIENT_H_ */
