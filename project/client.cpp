#include "saber.h"
#include "login.h"
#include "player_init.h"
#include "package.h"
#include "equipments.h"

using namespace std;

pthread_cond_t pth_do = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int pth_simble = 0;
int simble = 0;

int account;
struct character_info player;
Character *cha;
Saber *saber_ptr;
vector<Things_str*> package;

void print_disconnect(int sockfd)
{
	printf("The other side has been closed\n");
	close(sockfd);
	exit(0);
}

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

		simble = 1;
			
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
		simble = 0;
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

	while(1)
	{
		can_account = 0;
		account = login(sockfd);
		while(simble == 0);
		if(account)
		{
			while(can_account == 0)
			{
				can_character = 0;
				player = character(sockfd, account);
				cout << "\n欢迎 " << player.job << " " << player.name << " 进入游戏！" << endl;
				while(simble == 0);
				if(player.job == "saber")
				{
					cha = new Saber(player.name);
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

				while(simble == 0);
				ret = package_init(sockfd, player.name, package);
				if(ret)
					cout << "背包初始化成功！" << endl;
				while(simble == 0);
				ret = 0;
				ret = player_init(cha, sockfd, player.name, player.job, package);
				if(ret)
					cout << "角色初始化成功！" << endl;

				while(can_character == 0)
				{
					cout << "\n1、查看属性 2、查看装备 3、匹配战斗 4、注销角色 5、注销账号" << endl;
					cout << "请输入您的选择：";
					int select;
					cin >> select;
					switch(select)
					{
						case 1:
							cout << "\nblood: " << cha->Getblood() << endl;
							cout << "attack: " << cha->Getattack() << endl;
							cout << "defense: " << cha->Getdefense() << endl;
							break;
						case 2:
							equipments(sockfd, cha, package);
							break;
						case 3:
							break;
						case 4:
							can_character = 1;
							break; 
						case 5:
							can_character = 1;
							can_account = 1;
							break;
						default:
							cout << "您的输入有误，请重新输入！" << endl;
					}
				}
			}		
		}		
	}

	return 0;
}
