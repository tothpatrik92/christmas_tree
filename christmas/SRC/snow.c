/*
 * snow.c
 *
 *  Created on: Nov 27, 2017
 *      Author: patrik
 */

#include <stdio.h>
#include <stdlib.h>
#include "unistd.h"
#include "inttypes.h"
#include "fcntl.h"
#include "string.h"
#include "time.h"
#include "math.h"

#include "config.h"
#include "tree.h"
#include "snow.h"
#include "sdata.h"

struct M_ELEMENTS snow_matrix={
		{NULL},
		0,
		0,
		0,
		0,
		0,
		0,
		DEFAULT_SNOW_INTENSITY
};

void init_snow(void)
{
	static time_t t;
	srand((unsigned)time(&t));
	memset(&snow_matrix.array,' ',sizeof(snow_matrix.array));
	snow_matrix.intensity=DEFAULT_SNOW_INTENSITY;
}
void create_snow(struct M_ELEMENTS *ptr)
{

	for(ptr->y_n=0;ptr->y_n<_Y_MAX;ptr->y_n++)
	{


		for(ptr->x_n=0;ptr->x_n<_X;ptr->x_n++)
		{

			if((rand()%(ptr->intensity))==0){
				ptr->array[ptr->y_n][ptr->x_n++]=SNOW_F;//'\u2744';
			}
		}

	}
}



void move_snow(struct M_ELEMENTS *snow_m)
{
	static uint8_t n,i;
/*
 * Move flakes down.
 *
 * */
		for(n=_Y_MAX-1;n>0;n--)
		{
			for(i=0;i<_X;i++)
				{
				snow_m->array[n][i]=snow_m->array[n-1][i];
				}
		}


/*
 * Clear the 0.line.
 *
 * */

	for(n=0;n<_X;n++)
	{
		snow_m->array[0][n]=' ';

	}

/*
 * Fill the 0. line with new random flakes.
 *
 * */
	for(n=0;n<_X;n++)
	{
		if((rand()%(snow_m->intensity))==0){
			snow_m->array[0][n]=SNOW_F;
		}
	}

/*
 * Move flakes left.
 *
 *for(i=WIND_INT...) lenne a helyes,mert így a tömb negatív elemére is tudunk hivatkozni,szerencsére nem seg.fault
 *így a bal oldalról a jobbra shiftelődik a tömb eleme,
 *de ez csak több dimenziós mátrixoknál érvényes.
 *
 *  ______ ______ ______ ______ ______ ______ ______ ______
 * |      |      |      |      |      |      |      |      |
 * |[0][0]|[0][1]|[0][2]|[0][3]|[1][0]|[1][1]|[1][2]|[1][3]|
 * |______|______|______|______|______|______|______|______|
 *
 * */
if(BTEST(global_data,GD_WIND_LEFT))
{
	for(n=_Y_MAX-1;n>0;n--)
	{
		for(i=1;i<_X-1;i++)
			{
			snow_m->array[n][i-WIND_INT]=snow_m->array[n][i];
			snow_m->array[n][i]=' ';
			}
		snow_m->array[n][i]=' ';
	}
}

/*
 * Move flakes right.
 *
 * */
else if(BTEST(global_data,GD_WIND_RIGHT))
	{
		for(n=_Y_MAX-1;n>0;n--)
		{
			for(i=((_X-1));i>0;i--) // i=WIND_INT lenne a helyes,mert így a tömb negatív elemére is tudunk hivatkozni,szerencsére nem seg.fault
				{
				snow_m->array[n][i+WIND_INT]=snow_m->array[n][i];
				snow_m->array[n][i]=' ';
				}
			snow_m->array[n][i]=' ';
		}
	}

}



void snow_intensity(uint16_t * timer,uint16_t *ptr)
{

	if(*timer>=10)
	{
		*timer=0;
		if(*ptr>INTENSITY_UNIT){*ptr=(*ptr)-INTENSITY_UNIT;}
	}

}

