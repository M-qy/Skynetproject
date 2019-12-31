#include "head.h"
#include "login.h"
#include "characters.h"
#include "saber.h"
#include "player_init.h"

using namespace std;

pthread_cond_t pth_do = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int pth_simble = 0;

int account;
struct character_info player;
Character *cha;
Saber *saber_ptr;

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

		cout << "lock" << endl;
			
		memset(buf, 0, MAXLINE);
		n = read(sockfd, buf, MAXLINE);
		if(n == 0)
		{
			printf("The other side has been closed\n");
			close(sockfd);
			exit(0);
		}
		else
		{
			cout << "readpthread read:" << buf << endl;
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

	int can_account = 0, can_character = 0;

	while(can_account == 0)
	{
		account = login(sockfd);
		usleep(800);	
		if(account)
		{
			while(can_character == 0)
			{
				player = character(sockfd, account);
				cout << "欢迎 " << player.job << " " << player.name << " 进入游戏！" << endl;
				if(player.job == "saber")
				{
					Saber saber(player.name);
					cha = &saber;
					saber_ptr = &saber;
					ret = player_init(cha, sockfd, player.name, player.job);
					if(ret)
					{
						cout << "初始化成功！" << endl;
						int blood = cha->Getblood();
						int attack = cha->Getattack();
						int defense = cha->Getdefense();
						cout << "blood:" << blood << endl;
						cout << "attack:" << attack << endl;
						cout << "defense:" << defense << endl;
					}
				}
				else if(player.job == "archer")
				{
					Saber saber(player.name);
					cha = &saber;
				}
				else if(player.job == "caster")
				{
					Saber saber(player.name);
					cha = &saber;
				}
				exit(0);
			}		
		}		
	}

	return 0;
}
