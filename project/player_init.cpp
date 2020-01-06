#include "player_init.h"

using namespace std;

int player_init(Character *cha, int sockfd, string name, string job, vector<Things_str*>&package)
{
    string str;
    int n = 0;
    char buf[MAXLINE];

    pth_simble = 1;
    str = "player_init";
    write(sockfd, str.c_str(), str.size());
    pthread_mutex_lock(&lock);
    
    n = read(sockfd, buf, MAXLINE);
    if(n == 0)
        print_disconnect(sockfd);
    str = buf;
    while(str != "ok");

    write(sockfd, name.c_str(), name.size());
    memset(buf, 0, MAXLINE);
    n = read(sockfd, buf, MAXLINE);
    if(n == 0)
        print_disconnect(sockfd);
    str = buf;
    while(str != "ok");

    write(sockfd, job.c_str(), job.size());
    memset(buf, 0, MAXLINE);
    n = read(sockfd, buf, MAXLINE);
    if(n == 0)
        print_disconnect(sockfd);
    str = buf;
    while(str != "ok");

    int blood, attack, defense;

    memset(buf, 0, MAXLINE);
    n = read(sockfd, buf, MAXLINE);
    if(n == 0)
        print_disconnect(sockfd);
    blood = atoi(buf);
    str = "ok";
    write(sockfd, str.c_str(), str.size());

    memset(buf, 0, MAXLINE);
    n = read(sockfd, buf, MAXLINE);
    if(n == 0)
        print_disconnect(sockfd);
    attack = atoi(buf);
    str = "ok";
    write(sockfd, str.c_str(), str.size());

    memset(buf, 0, MAXLINE);
    n = read(sockfd, buf, MAXLINE);
    if(n == 0)
        print_disconnect(sockfd);
    defense = atoi(buf);
    str = "ok";
    write(sockfd, str.c_str(), str.size());

	int ret;
    memset(buf, 0, MAXLINE);
    n = read(sockfd, buf, MAXLINE);
    if(n == 0)
        print_disconnect(sockfd);
    str = buf;
	if(str != "NULL")
	{
		ret = package_find(package, str);
		if(ret != -1)
		{
			cha->Puton_arm(package[ret]->things);
			package[ret]->things->init(cha);
		}
	}
	str = "ok";
    write(sockfd, str.c_str(), str.size());

    memset(buf, 0, MAXLINE);
    n = read(sockfd, buf, MAXLINE);
    if(n == 0)
        print_disconnect(sockfd);
    str = buf;
	if(str != "NULL")
	{
		ret = package_find(package, str); 
		if(ret != -1)
		{
			cha->Puton_armor(package[ret]->things);
			package[ret]->things->init(cha);
		}
	}
	
	int m_blood = cha->Getblood();
	int m_attack = cha->Getattack();
	int m_defense = cha->Getdefense();
	if(m_blood != blood || m_attack != attack || m_defense != defense)
		cout << "属性与服务端数据不同！" << endl;
    
    pth_simble = 0;
    pthread_mutex_unlock(&lock);
	pthread_cond_signal(&pth_do);
    return 1;
}
