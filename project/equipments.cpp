#include "equipments.h"

using namespace std;

void puton(int sockfd, Character *cha, string selection, Things *things, string arm, string armor);
void takeoff(int sockfd, Character *cha, string selection, Things *things);

void equipments(int sockfd, Character *cha, vector<Things_str*>&package)
{

	int select1;
	while(1)
	{
		string arm = cha->Getarmname();
		if(arm == "NULL")
			cout << "\n您没有穿戴武器！" << endl;
		else
			cout << "\n您穿戴着" << arm << endl;
		string armor = cha->Getarmorname();
		if(armor == "NULL")
			cout << "您没有穿戴防具！" << endl;
		else
			cout << "您穿戴着" << armor << endl;

		cout << "\n您的背包有：" << endl;
		int i = 0;
		for(auto it = package.begin(); it != package.end(); ++it, ++i)
		{
			cout << i+1 << "、" << (*it)->things->get_name() << "：" << (*it)->num << "个"<< endl;
		}
		cout << "0、返回" << endl;
		cout << "\n请输入您的选择：";
		cin >> select1;
		if(select1 == 0)
			return;
		string selection = package[select1-1]->things->get_name();

		cout << "\n您选择了" << selection << endl;
		int point = 1;
		if(selection == arm || selection == armor)
		{
			while(point == 1)
			{
				int select2;
				cout << "\n1、查看属性 2、卸下 0、返回背包" << endl;
				cout << "请输入您的选择：";
				cin >> select2;
				switch(select2)
				{
					case 0:
						point = 0;
						break;
					case 1:
						package[select1-1]->things->describe();
						break;
					case 2:
						takeoff(sockfd, cha, selection, package[select1-1]->things);
						point = 0;
						break;
					default:
						cout << "您的输入有误！" << endl;
						break;
				}
			}
		}
		else
		{
			while(point == 1)
			{
				int select2;
				cout << "\n1、查看属性 2、穿戴 0、返回背包" << endl;
				cout << "请输入您的选择：";
				cin >> select2;
				switch(select2)
				{
					case 0:
						point = 0;
						break;
					case 1:
						package[select1-1]->things->describe();
						break;
					case 2:
						puton(sockfd, cha, selection, package[select1-1]->things, arm, armor);
						point = 0;
						break;
					default:
						cout << "您的输入有误！" << endl;
						break;
				}
			} 
		}
	}
}

void puton(int sockfd, Character *cha, string selection, Things *things, string arm, string armor)
{
	string str;
	int n = 0;
	char buf[MAXLINE];

	pth_simble = 1;
	str = "equipment";
	write(sockfd, str.c_str(), str.size());
	pthread_mutex_lock(&lock); 

	memset(buf, 0, MAXLINE);
	n = read(sockfd, buf, MAXLINE);
	if(n == 0)
		print_disconnect(sockfd);
	str = buf;
	while(str != "ok");

	str = "puton";
	write(sockfd, str.c_str(), str.size()); 
	memset(buf, 0, MAXLINE);
	n = read(sockfd, buf, MAXLINE);
	if(n == 0)
		print_disconnect(sockfd);
	str = buf;
	while(str != "ok"); 

	string::size_type pos = selection.find("armor");
	if(pos != selection.npos)
	{
		str = "armor";
		write(sockfd, str.c_str(), str.size());
		memset(buf, 0, MAXLINE);
		n = read(sockfd, buf, MAXLINE);
		if(n == 0)
			print_disconnect(sockfd);
		str = buf;
		while(str != "ok");

		write(sockfd, selection.c_str(), selection.size());
		memset(buf, 0, MAXLINE);
		n = read(sockfd, buf, MAXLINE);
		if(n == 0)
			print_disconnect(sockfd);
		str = buf;
		while(str != "ok"); 
		if(armor != "NULL")
		{
			Things* temp = cha->Getarmorptr();
			cha->Takeoff_armor();
			temp->takeoff(cha);
		}
		cha->Puton_armor(things);
		things->init(cha);
		cout << "\n成功穿戴" << selection << endl;
	}
	else
	{
		str = "arm";
		write(sockfd, str.c_str(), str.size());
		memset(buf, 0, MAXLINE);
		n = read(sockfd, buf, MAXLINE);
		if(n == 0)
			print_disconnect(sockfd);
		str = buf;
		while(str != "ok");

		write(sockfd, selection.c_str(), selection.size());
		memset(buf, 0, MAXLINE);
		n = read(sockfd, buf, MAXLINE);
		if(n == 0)
			print_disconnect(sockfd);
		str = buf;
		while(str != "ok"); 
		if(arm != "NULL")
		{
			Things* temp = cha->Getarmptr();
			cha->Takeoff_arm();
			temp->takeoff(cha);
		} 
		cha->Puton_arm(things); 
		things->init(cha);
		cout << "\n成功穿戴" << selection << endl;
	}
 

	pth_simble = 0;
	pthread_mutex_unlock(&lock);
	pthread_cond_signal(&pth_do); 
}

void takeoff(int sockfd, Character *cha, string selection, Things *things)
{
	string str;
	int n = 0;
	char buf[MAXLINE];

	pth_simble = 1;
	str = "equipment";
	write(sockfd, str.c_str(), str.size());
	pthread_mutex_lock(&lock); 

	memset(buf, 0, MAXLINE);
	n = read(sockfd, buf, MAXLINE);
	if(n == 0)
		print_disconnect(sockfd);
	str = buf;
	while(str != "ok");

	str = "takeoff";
	write(sockfd, str.c_str(), str.size()); 
	memset(buf, 0, MAXLINE);
	n = read(sockfd, buf, MAXLINE);
	if(n == 0)
		print_disconnect(sockfd);
	str = buf;
	while(str != "ok"); 

	string::size_type pos = selection.find("armor");
	if(pos != selection.npos)
	{
		str = "armor";
		write(sockfd, str.c_str(), str.size());
		memset(buf, 0, MAXLINE);
		n = read(sockfd, buf, MAXLINE);
		if(n == 0)
			print_disconnect(sockfd);
		str = buf;
		while(str != "ok");

		write(sockfd, selection.c_str(), selection.size());
		memset(buf, 0, MAXLINE);
		n = read(sockfd, buf, MAXLINE);
		if(n == 0)
			print_disconnect(sockfd);
		str = buf;
		while(str != "ok"); 
		cha->Takeoff_armor();
		things->takeoff(cha);
		cout << "\n成功卸下" << selection << endl;
	}
	else
	{
		str = "arm";
		write(sockfd, str.c_str(), str.size());
		memset(buf, 0, MAXLINE);
		n = read(sockfd, buf, MAXLINE);
		if(n == 0)
			print_disconnect(sockfd);
		str = buf;
		while(str != "ok");

		write(sockfd, selection.c_str(), selection.size());
		memset(buf, 0, MAXLINE);
		n = read(sockfd, buf, MAXLINE);
		if(n == 0)
			print_disconnect(sockfd);
		str = buf;
		while(str != "ok"); 
		cha->Takeoff_arm(); 
		things->takeoff(cha);
		cout << "\n成功卸下" << selection << endl;
	}

	pth_simble = 0;
	pthread_mutex_unlock(&lock);
	pthread_cond_signal(&pth_do); 
}
