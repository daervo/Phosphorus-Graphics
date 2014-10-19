/*
 * GameClient.cpp
 *
 *  Created on: 16 Oct 2014
 *      Author: Ervin
 */

#include <networks/GameClient.h>

namespace phosphorus {

GameClient::GameClient() {
	// TODO Auto-generated constructor stub

}

GameClient::~GameClient() {
	// TODO Auto-generated destructor stub
}

bool GameClient::startConnection(int port, std::string host){
	WORD sockVersion;
	WSADATA wsaData;
	int nret;
	sockVersion = MAKEWORD(1, 1);

	// Initialize Winsock
	WSAStartup(sockVersion, &wsaData);

	// Server info
	LPHOSTENT hostEntry;
	hostEntry = gethostbyname(host.c_str());
	// Specifying the server by its name;
	// another option: gethostbyaddr()

	//Check if it worked
	if (!hostEntry) {
		std::cout<<"gethostbyname()"<<std::endl;
		// Report the error as before
		WSACleanup();
		return false;
	}

	// Create the socket
	theSocket = socket(AF_INET,	// Go over TCP/IP
			SOCK_STREAM,	// This is a stream-oriented socket
			IPPROTO_TCP);	// Use TCP rather than UDP

	//Check if it worked
	if (theSocket == INVALID_SOCKET) {
		std::cout<<"socket()"<<std::endl;
		WSACleanup();
		return false;
	}

	// Fill a SOCKADDR_IN struct with address information
	SOCKADDR_IN serverInfo;
	serverInfo.sin_family = AF_INET;
	serverInfo.sin_addr = *((LPIN_ADDR)*hostEntry->h_addr_list);
	serverInfo.sin_port = htons(port);

	// Connect to the server
	nret = connect(theSocket, (LPSOCKADDR)&serverInfo, sizeof(struct sockaddr));
	if (nret == SOCKET_ERROR) {
		std::cout<<"connect()"<<std::endl;
		WSACleanup();
		return false;
	}

	// Successfully connected!
	// Send/receive, then cleanup:






	return true;
}

bool GameClient::sendToServer(char* buffer, char* reply){
	std::cout << "successfully connected, sending..." << std::endl;
	int nret;

	nret = send(theSocket, buffer, GAME_PACKET_SIZE, 0);
	if (nret == SOCKET_ERROR) {
		std::cout << "send()" << std::endl;
		return false;
	}else{
		std::cout << "sent " << nret << std::endl;
	}


	std::cout << "successfully connected, receiving..." << std::endl;

	nret = recv(theSocket, reply, GS_PACKET_SIZE,	// Complete size of buffer
			0);
	if (nret == SOCKET_ERROR) {
		// Get a specific code
		// Handle accordingly
		std::cout << "socket error" << std::endl;
		return false;
	} else {
		// nret contains the number of bytes received
		if (nret > 0){
		std::cout << "yaay" << std::endl;
		}else{
			std::cout<<WSAGetLastError()<<std::endl;
		}
	}
	return true;
}

void GameClient::close(){
	closesocket(theSocket);
	WSACleanup();
}

} /* namespace phosphorus */
