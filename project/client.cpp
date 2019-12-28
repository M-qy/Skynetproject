#include "head.h"
#include "login.h"
#include "characters.h"

pthread_cond_t pth_do = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int pth_simble = 0;

string name;

void* readthread(void* arg)
{
	pthread_detach(pthread_self());
	int sockfd = (int)(long)arg;
	int n = 0;
	char buf[MAXLINE];
	while(1)
	{
		pthread_mutex_lock(&lock);
		while(pth_simble == 1)
			pthread_cond_wait(&pth_do, &lock);

		n = read(sockfd, buf, MAXLINE);
		if(n == 0)
		{
			printf("The other side has been closed\n");
			close(sockfd);
			exit(0);
		}
		pthread_mutex_unlock(&lock);
	}
	return (void*)0;
}

int main()
{
    struct sockaddr_in servaddr;
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
	servaddr.sin_port = htons(SERV_PORT);
	int ret = connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	if(ret != 0)
    {
        cout << "服务器连接错误！" << endl;
        exit(0);
    }

    pthread_t thid;
	pthread_create(&thid, NULL, readthread, (void*)(long)sockfd);

    cout << "欢迎进入游戏！" << endl;

	while(ret == 0)
	{
		ret = login(sockfd);	
		if(ret == 1)
		{/*
			while(can_character == 0)
			{
				name = character(sockfd);
			}		*/	
		}		
	}

	return 0;
}