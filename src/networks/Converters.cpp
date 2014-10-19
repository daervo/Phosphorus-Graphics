/*
 * Converters.cpp
 *
 *  Created on: 19 Oct 2014
 *      Author: Ervin
 */

#include <networks/Converters.h>

void floatToNetworkString (char* buffer, float fl, int place)
{
	snprintf(&buffer[place], FLOAT_DIGIT_SIZE, "%f", fl);
}

float networkStringToFloat (char* buffer, int place)
{

	return atof(&buffer[place]);

}



