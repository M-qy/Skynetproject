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

	memset(buf, 0, MAXLINE);
	n = read(sockfd, buf, MAXLINE);
	if(n == 0)
		print_disconnect(sockfd);
	str = buf; 
	string o_job = str;

	cout << "\n匹配成功！您的对手是 " << o_job << " " << o_name << endl;

	Character *o_cha;
	if(o_job == "saber")
	{
		o_cha = new Saber(o_name);

		str = "ok";
		write(sockfd, str.c_str(), str.size());
		memset(buf, 0, MAXLINE);
		n = read(sockfd, buf, MAXLINE);
		if(n == 0)
			print_disconnect(sockfd); 
		str = buf;
		Things *things;
		if(str == "sword1")
		{
			things = new Sword1();
			things->init(o_cha);
		}
		else if(str == "sword2")
		{
			things = new Sword2();
			things->init(o_cha);
		}
		cha->Puton_arm(things);
	}

	str = "ok";
	write(sockfd, str.c_str(), str.size());
	memset(buf, 0, MAXLINE);
	n = read(sockfd, buf, MAXLINE);
	if(n == 0)
		print_disconnect(sockfd); 
	str = buf;
	if(str == "armor1")
	{
		Things *things = new Armor1();
		things->init(o_cha);
		o_cha->Puton_armor(things);
	}
	else if(str == "armor2")
	{
		Things *things = new Armor2();
		things->init(o_cha);
		o_cha->Puton_armor(things);
	}
	int o_attack = o_cha->Getattack();

	cha->Lock_opponent(o_cha);
	o_cha->Lock_opponent(cha);
	int initblood = cha->Getblood();

	cout << "\n对战开始！" << endl;
	str = "start";
	write(sockfd, str.c_str(), str.size());
	memset(buf, 0, MAXLINE);
	n = read(sockfd, buf, MAXLINE);
	if(n == 0)
		print_disconnect(sockfd); 
	str = buf;
	if(str == "second")
	{
		cout << "\n对方先手！请不要输入！" << endl;
		memset(buf, 0, MAXLINE);
		n = read(sockfd, buf, MAXLINE);
		if(n == 0)
			print_disconnect(sockfd); 
		str = buf;
		cout << buf << endl;
		if(str == "surrender")
		{
			cout << "\n你的对手投降了！游戏结束！" << endl;
			str = "o_surrender";
			write(sockfd, str.c_str(), str.size());
			delete o_cha;
			pth_simble = 0;
			pthread_mutex_unlock(&lock);
			pthread_cond_signal(&pth_do); 
			return; 
		}
		else if(str == "ace")
		{
			cha->Sub_blood(o_attack);
			cout << "\n你的对手平A了你！" << endl;
			str = "ok";
			write(sockfd, str.c_str(), str.size());
			memset(buf, 0, MAXLINE);
			n = read(sockfd, buf, MAXLINE);
			if(n == 0)
				print_disconnect(sockfd); 
			str = buf; 
			if(str == "bleed")
			{
				o_cha->Setm_bleed();
				cout << "并且你中了流血！" << endl;
				cha->Bleeding();
				cout << "你剩下" << cha->Getblood() << "血！" << endl;
			}
			else
			{
				cha->Bleeding();
				cout << "你剩下" << cha->Getblood() << "血！" << endl;
			} 
		}
	}
	else
		cout << "\n你先手！" << endl;
	while(1)
	{
		int select;
		cout << "\n你的对手剩下" << o_cha->Getblood() << "血！" << endl;
		cout << "\n你的回合！\n1、平A 0、投降" << endl;
		cout << "请输入您的选择：";
		cin >> select;
		int point = 0;
		while(point == 0)
		{
			int sign;
			switch(select)
			{
				case 0:
					cout << "\n你投降了!游戏结束！" << endl;
					str = "surrender";
					write(sockfd, str.c_str(), str.size());
					delete o_cha; 
					cha->Add_blood(initblood - cha->Getblood());
					cha->Init_bleedsign();
					pth_simble = 0;
					pthread_mutex_unlock(&lock);
					pthread_cond_signal(&pth_do); 
					return;
				case 1:
					cout << "\n你平A了对手！" << endl;
					str = "ace";
					write(sockfd, str.c_str(), str.size());

					memset(buf, 0, MAXLINE);
					n = read(sockfd, buf, MAXLINE);
					if(n == 0)
						print_disconnect(sockfd); 
					str = buf; 
					while(str != "ok");
					sign = cha->Ace();
					if(sign == 1)
					{
						cout << "并且他中了流血！" << endl;
						str = "bleed";
						write(sockfd, str.c_str(), str.size());
					}
					else
					{
						str = "unbleed";
						write(sockfd, str.c_str(), str.size());
					}
					point = 1;
					break;
				default:
					cout << "您的输入有误！" << endl;
					break;
			}
		}
		memset(buf, 0, MAXLINE);
		n = read(sockfd, buf, MAXLINE);
		if(n == 0)
			print_disconnect(sockfd); 
		str = buf; 
		if(str == "surrender")
		{
			cout << "\n你的对手投降了！游戏结束！" << endl;
			str = "o_surrender";
			write(sockfd, str.c_str(), str.size());
			delete o_cha; 
			cha->Add_blood(initblood - cha->Getblood());
			cha->Init_bleedsign();
			pth_simble = 0;
			pthread_mutex_unlock(&lock);
			pthread_cond_signal(&pth_do); 
			return; 
		}
		else if(str == "over")
		{
			cout << "恭喜！你赢了！游戏结束！" << endl;
			str = "over";
			write(sockfd, str.c_str(), str.size());
			delete o_cha; 
			cha->Add_blood(initblood - cha->Getblood());
			cha->Init_bleedsign();
			pth_simble = 0;
			pthread_mutex_unlock(&lock);
			pthread_cond_signal(&pth_do);
			return;

		}
		else if(str == "ace")
		{
			cha->Sub_blood(o_attack);
			cout << "\n你的对手平A了你！" << endl;
		}
		memset(buf, 0, MAXLINE);
		n = read(sockfd, buf, MAXLINE);
		if(n == 0)
			print_disconnect(sockfd); 
		str = buf;
		if(str == "bleed")
		{
			o_cha->Setm_bleed();
			cout << "并且你中了流血！" << endl;
			cha->Bleeding();
			cout << "你剩下" << cha->Getblood() << "血！" << endl;
		}
		else
		{
			cha->Bleeding();
			cout << "你剩下" << cha->Getblood() << "血！" << endl;
		}
		if(cha->Getblood() <= 0)
		{
			cout << "\n你输了！游戏结束！" << endl;
			str = "over";
			write(sockfd, str.c_str(), str.size());
			delete o_cha; 
			cha->Add_blood(initblood - cha->Getblood());
			cha->Init_bleedsign();
			pth_simble = 0;
			pthread_mutex_unlock(&lock);
			pthread_cond_signal(&pth_do);
			return;
		}
	}
}
