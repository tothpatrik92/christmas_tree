/*
 * config.h
 *
 *  Created on: Nov 27, 2017
 *      Author: patrik
 */

#include "inttypes.h"
#include <pthread.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "communication.h"

#ifndef CONFIG_H_
#define CONFIG_H_

#define NO_ERROR 0U
#define FALSE 0U
#define TRUE !FALSE


#define NUM_OF_ARRAY 10
#define _X 211
#define _Y 40
#define _Y_2 49
#define _Y_MAX 50
#define CENTRAL 101
#define CUT_END_OF_LINE 3
#define CUT_AMOUNT 2
#define CUT_FROM 15
#define DEFAULT_SNOW_INTENSITY 5000
#define INTENSITY_UNIT 100
#define MIN_UNIT 5
#define MAX_UNIT 1000
#define FULL_INT_SCALE (MAX_UNIT+MIN_UNIT)


#define BUFLEN 20
#define NPACK 10000
#define PORT 15000
#define SRV_IP		"127.0.0.1"


#define SIN_LINE 	'@'
#define TREE_E		'^'
#define SNOW_F		'*'

#define WIND_INT	3

#define S	1
#define MS	2
#define US	3
#define FRESH_T	100

typedef struct M_ELEMENTS{
		unsigned char array[_Y_MAX][_X];
		uint8_t x_n;
		uint8_t y_n;
		uint8_t c_offset;
		uint8_t c_global_offset;
		uint8_t n;
		uint8_t i;
		uint16_t intensity;

}M_ELEMENTS;


typedef struct FOR_THREAD{
	struct M_ELEMENTS *snow;
	struct sockaddr_in *si_me;
	struct sockaddr_in *si_other;
	int *s;
	int *slen;
};


#define RED 	"\x1B[31m"
#define GREEN 	"\x1B[32m"
#define YELLOW 	"\x1B[33m"
#define BLUE 	"\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYANE 	"\x1B[36m"
#define WHITE 	"\x1B[37m"
#define RESET 	"\x1B[0m"
//printf("%s",RED);

#define BTEST(a,b) ((a&b)==b?1:0)
#define BSET(a,b) a=(a|b)
#define BCLR(a,b) a=(a&(~b))


#endif /* CONFIG_H_ */
