/*
 * communication.c
 *
 *  Created on: Nov 28, 2017
 *      Author: patrik
 */


#include "communication.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include "config.h"
#include "sdata.h"


struct 	sockaddr_in si_me, si_other;
int 		s, i;
int slen;

void init_udp(void)
{

	slen=sizeof(si_other);
	char 		buf[BUFLEN],buf_to_client[BUFLEN],ack_msg[BUFLEN],buff_str[20];
  	if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1) diep("socket");
	memset((char *) &si_me, 0, sizeof(si_me));

	si_me.sin_family = AF_INET;
	si_me.sin_port = htons(PORT);
	si_me.sin_addr.s_addr = htonl(INADDR_ANY);

	if (inet_aton(SRV_IP, &si_other.sin_addr)==0) diep("inet_aton()");
	if (bind(s, &si_me, sizeof(si_me))==-1) diep("bind");

}

void udp_comm_handling(struct FOR_THREAD *ptr)
{

	//struct FOR_THREAD
	unsigned char buf[BUFLEN];
	unsigned char ack_msg[BUFLEN];
	memset(&ack_msg,0,BUFLEN);
	sprintf(ack_msg,"ACK");



		while(1)
		{
			recvfrom(*ptr->s, buf, BUFLEN, 0, (ptr->si_other), (ptr->slen));

			if(!(strcmp(buf,"GD_WIND_LEFT")))
			{
				BCLR(global_data,GD_WIND_RIGHT);
				BSET(global_data,GD_WIND_LEFT);
			}
			else if(!(strcmp(buf,"GD_WIND_RIGHT")))
			{
				BCLR(global_data,GD_WIND_LEFT);
				BSET(global_data,GD_WIND_RIGHT);
			}
			else if(!(strcmp(buf,"GD_WIND_OFF")))
			{

				BCLR(global_data,GD_WIND_LEFT);
				BCLR(global_data,GD_WIND_RIGHT);
			}
			else if(!(strcmp(buf,"INTENSITY")))
			{
				ptr->snow->intensity=(uint16_t)900;//atoi(&buf);
				ptr->snow->intensity=FULL_INT_SCALE-(ptr->snow->intensity);
			}
			else if(!(strcmp(buf,"GD_LED_BLINK_ON")))
			{
				BSET(global_data,GD_LED_BLINK_ON);
			}
			else if(!(strcmp(buf,"GD_LED_BLINK_OFF")))
			{
				BCLR(global_data,GD_LED_BLINK_ON);
			}
			else
			{
				ptr->snow->intensity=(uint16_t)atoi(&buf);
				ptr->snow->intensity=FULL_INT_SCALE-(ptr->snow->intensity);
			}


			if (sendto(*ptr->s, &ack_msg, sizeof(ack_msg), 0, (ptr->si_other), *(ptr->slen))==-1);// diep("sendto()");
			memset(&buf,0,BUFLEN);
			usleep(1000);

		}

}

void diep(char *s)
{
  perror(s);
  exit(1);
}











