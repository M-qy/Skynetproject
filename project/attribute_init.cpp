#include "attribute_init.h"

using namespace std;

void attribute(int sockfd, Character *cha)
{
	string str;
    int n = 0;
    char buf[MAXLINE];

    pth_simble = 1;
    str = "attribute";
    write(sockfd, str.c_str(), str.size());
    pthread_mutex_lock(&lock); 

	memset(buf, 0, MAXLINE);
	n = read(sockfd, buf, MAXLINE);
	if(n == 0)
		print_disconnect(sockfd);
	str = buf;
	while(str != "ok");

	write(sockfd, str.c_str(), str.size());

	memset(buf, 0, MAXLINE);
	n = read(sockfd, buf, MAXLINE);
	if(n == 0)
		print_disconnect(sockfd); 
	int blood = atoi(buf);
	write(sockfd, str.c_str(), str.size());

	memset(buf, 0, MAXLINE);
	n = read(sockfd, buf, MAXLINE);
	if(n == 0)
		print_disconnect(sockfd); 
	int attack = atoi(buf);
	write(sockfd, str.c_str(), str.size()); 

	memset(buf, 0, MAXLINE);
	n = read(sockfd, buf, MAXLINE);
	if(n == 0)
		print_disconnect(sockfd); 
	int defense = atoi(buf);
	write(sockfd, str.c_str(), str.size());

	cha->init(blood, attack, defense);

	cout << "\n血量：" << cha->Getblood() << endl; 
	cout << "攻击力：" << cha->Getattack() << endl;
	cout << "防御力：" << cha->Getdefense() << endl;

	pth_simble = 0;
    pthread_mutex_unlock(&lock);
	pthread_cond_signal(&pth_do); 
}
