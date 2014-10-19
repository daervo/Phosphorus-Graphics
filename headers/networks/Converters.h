/*
 * Converters.h
 *
 *  Created on: 19 Oct 2014
 *      Author: Ervin
 */

#ifndef CONVERTERS_H_
#define CONVERTERS_H_

#include <stdio.h>
#include <networks/networkConstants.hpp>
#include <stdlib.h>

void floatToNetworkString (char* buffer, float fl, int place = 0);
float networkStringToFloat (char* buffer, int place = 0);



#endif /* CONVERTERS_H_ */
