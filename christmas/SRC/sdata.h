/*
 * sdata.h
 *
 *  Created on: Nov 29, 2017
 *      Author: patrik
 */

#ifndef SDATA_H_
#define SDATA_H_

#include "sdata.h"
void init_sdata(void);

extern unsigned long int global_data;

#define GD_ERROR			0x1UL
#define GD_WIND_LEFT		0x2UL
#define GD_WIND_RIGHT		0x4UL
#define GD_LED_BLINK_ON		0x8UL


#endif /* SDATA_H_ */
