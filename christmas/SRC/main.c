/*
 ============================================================================
 Name        : sort.c
 Author      : Toth Patrik
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "unistd.h"
#include "inttypes.h"
#include "fcntl.h"
#include "string.h"
#include "time.h"
#include "math.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>

#include "communication.h"
#include "config.h"
#include "tree.h"
#include "snow.h"
#include "thread.h"
#include "sdata.h"



void create_all(void);
void print_out(struct M_ELEMENTS *);
void print_sine_blink(struct M_ELEMENTS *ptr,uint8_t *led_blk_tmp);
void wait(unsigned long int time,unsigned char type);
void clear_screen(void);



int main(int argc, char * argv[]) {

	//int error=NO_ERROR;

	init_sdata();
	init_udp();
	init_tree();
	init_snow();
	init_thread();
	create_all();

while(!BTEST(global_data,GD_ERROR)){

	move_snow(&snow_matrix);
	merge(&tree_matrix,&snow_matrix,&fin_matrix);
	print_out(&fin_matrix);
	wait(FRESH_T,MS);
	//clear_screen();
}

close(s);
return EXIT_SUCCESS;
}


void print_out(struct M_ELEMENTS *ptr)
{
	static uint8_t led_blk_tmp=0;
	printf("\n\n\n\n\n\n");


				for(ptr->n=0;ptr->n<_Y_MAX;ptr->n++)
				{
					for(ptr->i=0;ptr->i<_X;ptr->i++)
					{
						if(ptr->array[ptr->n][ptr->i]==TREE_E)
						{
							printf("%s",GREEN);
							printf("%c",ptr->array[ptr->n][ptr->i]);
							printf("%s",RESET);
						}
						else if(ptr->array[ptr->n][ptr->i]==SIN_LINE)
						{
							if(BTEST(global_data,GD_LED_BLINK_ON))
							{
								print_sine_blink(ptr,&led_blk_tmp);
							}
							else
							{
								printf("%s",RED);
								printf("%c",ptr->array[ptr->n][ptr->i]);
								printf("%s",RESET);
							}
						}
						else
						{
							printf("%s",WHITE);
							printf("%c",ptr->array[ptr->n][ptr->i]);
						}

					}

					printf("\n");
				}
				if(BTEST(global_data,GD_LED_BLINK_ON))
				{
					led_blk_tmp++;
					if(led_blk_tmp==7)led_blk_tmp=0;
				}
}

void print_sine_blink(struct M_ELEMENTS *ptr,uint8_t *led_blk_tmp)
{
	if(*led_blk_tmp==1)
	{
		printf("%s",RED);
		printf("%c",ptr->array[ptr->n][ptr->i]);
		printf("%s",RESET);
	}
	else if (*led_blk_tmp==2)
	{
		printf("%s",YELLOW);
		printf("%c",ptr->array[ptr->n][ptr->i]);
		printf("%s",RESET);

	}
	else if (*led_blk_tmp==3)
	{
		printf("%s",BLUE);
		printf("%c",ptr->array[ptr->n][ptr->i]);
		printf("%s",RESET);

	}
	else if (*led_blk_tmp==4)
	{
		printf("%s",MAGENTA);
		printf("%c",ptr->array[ptr->n][ptr->i]);
		printf("%s",RESET);

	}
	else if (*led_blk_tmp==5)
	{
		printf("%s",CYANE);
		printf("%c",ptr->array[ptr->n][ptr->i]);
		printf("%s",RESET);

	}
	else if (*led_blk_tmp==6)
	{
		printf("%s",WHITE);
		printf("%c",ptr->array[ptr->n][ptr->i]);
		printf("%s",RESET);

	}

}
void create_all(void)
{
	create_top(&tree_matrix);
	create_mid(&tree_matrix);
	create_bot(&tree_matrix);
	create_sin(&tree_matrix);
	create_snow(&snow_matrix);
	merge(&tree_matrix,&snow_matrix,&fin_matrix);


}

void wait(unsigned long int time,unsigned char type){
	switch(type){
	case S:
		sleep(time);
		break;
	case MS:
		usleep(time*1000);
		break;
	case US:
		usleep(time);
		break;
	default:
		fprintf(stderr,"Error in wait().\n");
		fflush(NULL);
		exit(1);

	}

}

void clear_screen(void)
{
	system("clear");
}


