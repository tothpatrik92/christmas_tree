/*
 * thread.c
 *
 *  Created on: Nov 28, 2017
 *      Author: patrik
 */
#include <stdio.h>
#include <stdlib.h>
#include "unistd.h"
#include <pthread.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "config.h"
#include "snow.h"
#include "thread.h"

#include "communication.h"
#include "tree.h"
#include "sdata.h"

pthread_t thread_rec_handler;

struct FOR_THREAD th_handler={
		&snow_matrix,
		&si_me,
		&si_other,
		&s,
		&slen
};

void init_thread(void)
{
	if(pthread_create(&thread_rec_handler,NULL,thread_rec,&th_handler))
				{
				fprintf(stderr,"Thread_rec FAIL.\n");
				exit(1);
				}

}
void *thread_rec(struct FOR_THREAD *ptr)
{

	udp_comm_handling(ptr);
}




