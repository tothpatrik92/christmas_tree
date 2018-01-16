/*
 * communication.h
 *
 *  Created on: Nov 28, 2017
 *      Author: patrik
 */

#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_
#include "config.h"
void init_udp(void);
void udp_comm_handling(struct FOR_THREAD *);
void diep(char *);

extern struct 	sockaddr_in si_me;
extern struct 	sockaddr_in si_other;
extern int 		s, i;
extern int slen;

#endif /* COMMUNICATION_H_ */
