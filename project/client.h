#ifndef client_h
#define client_h

#include <iostream>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <vector>
#include <map>
#include <string>
#include <time.h>

using namespace std;

#define MAXLINE 128
#define SERV_PORT 8001

extern pthread_cond_t pth_do;
extern pthread_mutex_t lock;
extern int pth_simble;
extern int simble;

void print_disconnect(int sockfd);

#endif
