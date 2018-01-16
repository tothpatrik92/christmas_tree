/*
 * snow.h
 *
 *  Created on: Nov 27, 2017
 *      Author: patrik
 */

#ifndef SNOW_H_
#define SNOW_H_
#include "config.h"

extern struct M_ELEMENTS snow_matrix;

void init_snow(void);
void create_snow(struct M_ELEMENTS *);
void move_snow(struct M_ELEMENTS *);
void snow_intensity(uint16_t *,uint16_t *);

#endif /* SNOW_H_ */
