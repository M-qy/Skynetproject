#include "equipments.h"

using namespace std;

int puton(int sockfd, vector<Things_str*>&package, int select);
int takeoff(int sockfd, vector<Things_str*>&package, int select);

void equipments(int sockfd, Character *cha, vector<Things_str*>&package)
{

	int select1;
	while(1)
	{
		string arm = cha->Getarmname();
		if(arm == "NULL")
			cout << "您没有穿戴武器！" << endl;
		else
			cout << "您穿戴着" << arm << endl;
		string armor = cha->Getarmorname();
		if(arm == "NULL")
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
		string selection = package[select1-1]->things->get_name();

		if(select1 == 0)
			return;
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
						int ret = takeoff(sockfd, selection, select1);
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

int puton(int sockfd, vector<Things_str*>&package, int select)
{
	string str;
	int n = 0;
	char buf[MAXLINE];

	pth_simble = 1;
	str = "puton";
	write(sockfd, str.c_str(), str.size());
	pthread_mutex_lock(&lock); 

	pth_simble = 0;
	pthread_mutex_unlock(&lock);
	pthread_cond_signal(&pth_do); 
}

int takeoff(int sockfd, string selection, int select)
{
	string str;
	int n = 0;
	char buf[MAXLINE];

	pth_simble = 1;
	str = "takeoff";
	write(sockfd, str.c_str(), str.size());
	pthread_mutex_lock(&lock); 

	n = read(sockfd, buf, MAXLINE);
	if(n == 0)
		print_disconnect(sockfd);
	str == buf;
	while(str != "ok");

	string::size_type pos = selection.find("armor");
	if(pos != selection.npos)
		cha->Takeoff_armor();
	else
		cha->Takeoff_arm(); 

	pth_simble = 0;
	pthread_mutex_unlock(&lock);
	pthread_cond_signal(&pth_do); 
}
