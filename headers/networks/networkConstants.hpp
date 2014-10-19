/*
 * networkConstants.hpp
 *
 *  Created on: 18 Oct 2014
 *      Author: Ervin
 */

#ifndef NETWORKCONSTANTS_HPP_
#define NETWORKCONSTANTS_HPP_

// Other Constants
const int FLOAT_DIGIT_SIZE = 10;
const int NUM_FIELDS = 9;
const int NUM_FIELDS_WITHOUT_COMMAND = 8;
const int NUM_PLAYERS = 2;

// Commands
const int UPDATE = 0;

// Game Packet
const int COMMAND = 0;
const int PLAYER_NUMBER = COMMAND + FLOAT_DIGIT_SIZE;
const int PLAYER_POSITION_X = COMMAND + FLOAT_DIGIT_SIZE * 2;
const int PLAYER_POSITION_Y = COMMAND + FLOAT_DIGIT_SIZE * 3;
const int PLAYER_POSITION_Z = COMMAND + FLOAT_DIGIT_SIZE * 4;
const int PLAYER_DIRECTION_X = COMMAND + FLOAT_DIGIT_SIZE * 5;
const int PLAYER_DIRECTION_Y = COMMAND + FLOAT_DIGIT_SIZE * 6;
const int PLAYER_DIRECTION_Z = COMMAND + FLOAT_DIGIT_SIZE * 7;
const int PLAYER_HP = COMMAND + FLOAT_DIGIT_SIZE * 8;

const int GAME_PACKET_SIZE = FLOAT_DIGIT_SIZE * NUM_FIELDS;
const int GAME_PACKET_SIZE_WITHOUT_COMMAND = FLOAT_DIGIT_SIZE * NUM_FIELDS_WITHOUT_COMMAND;

// GAME_STATE_PACKET
const int GAMESTATE_ID = 0;
const int GS_PLAYER_NUMBER = GAMESTATE_ID + FLOAT_DIGIT_SIZE;
const int GS_PLAYER_POSITION_X = GAMESTATE_ID + FLOAT_DIGIT_SIZE * 2;
const int GS_PLAYER_POSITION_Y = GAMESTATE_ID + FLOAT_DIGIT_SIZE * 3;
const int GS_PLAYER_POSITION_Z = GAMESTATE_ID + FLOAT_DIGIT_SIZE * 4;
const int GS_PLAYER_DIRECTION_X = GAMESTATE_ID + FLOAT_DIGIT_SIZE * 5;
const int GS_PLAYER_DIRECTION_Y = GAMESTATE_ID + FLOAT_DIGIT_SIZE * 6;
const int GS_PLAYER_DIRECTION_Z = GAMESTATE_ID + FLOAT_DIGIT_SIZE * 7;
const int GS_PLAYER_HP = GAMESTATE_ID + FLOAT_DIGIT_SIZE * 8;

const int GS_PACKET_SIZE = FLOAT_DIGIT_SIZE + FLOAT_DIGIT_SIZE * NUM_FIELDS_WITHOUT_COMMAND * NUM_PLAYERS;




#endif /* NETWORKCONSTANTS_HPP_ */
