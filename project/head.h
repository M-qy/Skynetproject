#ifndef _head_h
#define _head_h

#include <iostream>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <vector>
#include <map>
#include <time.h>

using namespace std;

#define MAXLINE 128
#define SERV_PORT 8001

extern pthread_cond_t pth_do;
extern pthread_mutex_t lock;
extern int pth_simble;

void print_disconnect(int sockfd)
{
     printf("The other side has been closed\n");
        close(sockfd);
        exit(0);

#endif