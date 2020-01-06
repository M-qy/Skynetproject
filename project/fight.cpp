#include "fight.h"

using namespace std;

void fight(int sockfd, Character *cha, string name, string job)
{
	string str;
    int n = 0;
    char buf[MAXLINE];

    pth_simble = 1;
    str = "fight";
    write(sockfd, str.c_str(), str.size());
    pthread_mutex_lock(&lock); 

	cout << "\n匹配中。。。" << endl;

	memset(buf, 0, MAXLINE);
	n = read(sockfd, buf, MAXLINE);
	if(n == 0)
		print_disconnect(sockfd);
	str = buf;
	if(str == "default")
	{
		cout << "\n匹配超时！" << endl;
		pth_simble = 0;
		pthread_mutex_unlock(&lock);
		pthread_cond_signal(&pth_do); 
		return;
	}
	string o_name = str;

	str = "ok";
	write(sockfd, str.c_str(), str.size());

	n = read(sockfd, buf, MAXLINE);
	if(n == 0)
		print_disconnect(sockfd);
	str = buf; 
	string o_job = str;

	cout << "\n匹配成功！您的对手是 " << o_job << " " << o_name << endl;

	Character *m_cha;
	Character *o_cha;
	if(job == "saber")
		m_cha = new Saber(name);
	if(o_job = "saber")
		o_cha = new Saber(o_name);
	m_cha->Puton_arm(cha->Getarmptr());
	m_cha->Puton_armor(cha->Getarmorptr());
	m_cha->Lock_opponent(o_cha);
	

	pth_simble = 0;
    pthread_mutex_unlock(&lock);
	pthread_cond_signal(&pth_do); 
}
