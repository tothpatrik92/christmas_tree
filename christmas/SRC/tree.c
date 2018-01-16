/*
 * tree.c
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

#include "communication.h"
#include "snow.h"
#include "sdata.h"

struct M_ELEMENTS tree_matrix={
			{NULL},
			0,
			0,
			0,
			0,
			0,
			0,
			DEFAULT_SNOW_INTENSITY
	};


struct M_ELEMENTS fin_matrix={
		{NULL},
		0,
		0,
		0,
		0,
		0,
		0,
		DEFAULT_SNOW_INTENSITY
};




void init_tree(void)
{

	memset(&tree_matrix.array,' ',sizeof(tree_matrix.array));
	memset(&fin_matrix.array,' ',sizeof(fin_matrix.array));


}



void create_top(struct M_ELEMENTS *ptr)
{
	static double actual_global_offset=0;
	for(ptr->y_n=0;ptr->y_n<_Y;ptr->y_n++)
	{
		for(ptr->c_offset=0;ptr->c_offset<(uint8_t)actual_global_offset;ptr->c_offset++)
		{
			ptr->array[ptr->y_n][CENTRAL]=TREE_E;
			ptr->array[ptr->y_n][CENTRAL+ptr->c_offset]=TREE_E;
			ptr->array[ptr->y_n][CENTRAL-ptr->c_offset]=TREE_E;

		}
		ptr->c_global_offset++;
		actual_global_offset=(uint8_t)exp(ptr->c_global_offset*0.11);
		if(ptr->c_global_offset>CUT_FROM){
			if((ptr->c_global_offset%CUT_END_OF_LINE)==0)
			{
				actual_global_offset=actual_global_offset-CUT_AMOUNT;
			}
			else
			{

			}
		}
	}
}

void create_mid(struct M_ELEMENTS *ptr)
{
	for(ptr->c_global_offset=4;ptr->y_n<_Y_2;ptr->y_n++)
	{

		for(ptr->c_offset=0;ptr->c_offset<ptr->c_global_offset;ptr->c_offset++)
		{

			ptr->array[ptr->y_n][CENTRAL]=TREE_E;
			ptr->array[ptr->y_n][CENTRAL+ptr->c_offset]=TREE_E;
			ptr->array[ptr->y_n][CENTRAL-ptr->c_offset]=TREE_E;

		}



	}
}


void create_bot(struct M_ELEMENTS *ptr)
{
	for(ptr->c_global_offset=10;ptr->y_n<_Y_MAX;ptr->y_n++)
	{

		for(ptr->c_offset=0;ptr->c_offset<ptr->c_global_offset;ptr->c_offset++)
		{

			fflush(NULL);
			ptr->array[ptr->y_n][CENTRAL]=TREE_E;
			ptr->array[ptr->y_n][CENTRAL+ptr->c_offset]=TREE_E;
			ptr->array[ptr->y_n][CENTRAL-ptr->c_offset]=TREE_E;

		}

	}

}

void create_sin(struct M_ELEMENTS *ptr)
{
	static double tmp;
	ptr->y_n=0;
	while(ptr->y_n<_Y)
	{
		tmp=ptr->y_n*sin(ptr->y_n*0.5);
		ptr->array[ptr->y_n][CENTRAL+(int)tmp]=SIN_LINE;
		ptr->y_n++;
	}

}


void merge(struct M_ELEMENTS *tree_m,struct M_ELEMENTS *snow_m,struct M_ELEMENTS *new_m)

{
	static uint8_t i,n;
	for(n=0;n<_Y_MAX;n++)
	{
		for(i=0;i<_X;i++)
		{
			if(tree_m->array[n][i]==' '){
				new_m->array[n][i]=(	tree_m->array[n][i] | snow_m->array[n][i]	);
			}
			else
			{
				new_m->array[n][i]=tree_m->array[n][i];
			}

		}
	}

}
