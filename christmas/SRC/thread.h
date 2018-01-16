/*
 * thread.h
 *
 *  Created on: Nov 28, 2017
 *      Author: patrik
 */
#include "communication.h"
#include "config.h"

#ifndef THREAD_H_
#define THREAD_H_

void init_thread(void);
void *thread_rec(struct FOR_THREAD *ptr);

extern pthread_t thread_rec_handler;
extern struct FOR_THREAD th_handler;

#endif /* THREAD_H_ */
