#include "characters.h"

using namespace std;
/*
void Character::Add_blood(int n){this->m_blood += n;}  
void Character::Add_attack(int n){this->m_attack += n;}   
void Character::Add_defense(int n){this->m_defense += n;}
void Character::Sub_blood(int n){this->m_blood -= (n - this->m_defense);}
void Character::Sub_attack(int n){this->m_attack -= n;}
void Character::Sub_defense(int n){this->m_defense -= n;}   
void Character::Rename(string name){this->m_name = name;}
void Character::Puton_arm(Things *arm){this->m_arm = arm;}
void Character::Puton_armor(Things *armor){this->m_armor = armor;}
void Character::Lock_opponent(Character *opponent){this->m_opponent = opponent;}
int Character::Getblood(){return this->m_blood;}
int Character::Getattack(){return this->m_attack;}
int Character::Getdefense(){return this->m_defense;}
void Character::Getarmname()
{
	if(this->m_arm == NULL)
		cout << "您没有穿戴任何武器！" << endl;
	else
		cout << "您穿戴了 " << this->m_arm->get_name() << endl;
}
void Character::Getarmorname()
{
	if(this->m_armor == NULL)
		cout << "您没有穿戴任何防具！" << endl;
	else
		cout << "您穿戴了 " << this->m_armor->get_name() << endl;
}*/
void Character::init(int blood, int attack, int defense)
{
	this->m_blood = blood;
	this->m_attack = attack;
	this->m_defense = defense;
}
void Character::Ace()
{
	this->m_opponent->Sub_blood(this->m_attack);
	if(this->bleed_sign == 1)    //判定一次流血
	{
		srand((unsigned int)time(NULL));
		int ret = rand()%100 + this->bleed_probability;
		if(ret > this->bleed_probability && ret <= 100)
			this->m_opponent->Oppo_bleed(this->o_bleed_num, this->o_bleed_blood);
	}
}
void Character::Bleeding()    //每回合访问此成员函数判断自己是否有中流血
{
	if(this->o_bleed_sign)
	{
		if(this->bleed_num > 0)
		{
			this->Sub_blood(this->bleed_blood);
			this->bleed_num--;
			cout << "你中了流血！-" << this->bleed_blood << "点血！" << endl;
			if(this->bleed_num == 0)
				this->o_bleed_sign = 0;
		}     
	}
}
void Character::Oppo_bleed(int num, int blood)    //自己被标记上流血标记
{
	this->o_bleed_sign = 1;
	this->bleed_num = num;
	this->bleed_blood = blood;
}
void Character::Bleed(int num, int blood, int probability)    //武器带有流血被动技能
{
	this->bleed_sign = 1;
	this->bleed_probability = probability;
	this->o_bleed_num = num;
	this->o_bleed_blood = blood;
}
void Character::Unbleed(){this->bleed_sign = 0;}    //武器不带有流血被动技能

void make_character(int sockfd)
{
	string str;
	char buf[MAXLINE];
	string job, name;
	int select;
	int temp = 0;
	int n = 0;

	str = "make";
	write(sockfd, str.c_str(), str.size());
	n = read(sockfd, buf, MAXLINE);
	if(n == 0)
		print_disconnect(sockfd);
	str = buf;
	while(str != "success");

	while(temp == 0)
	{
		cout << "1、剑客 2、射手 3、法师" << endl;
		cout << "请选择职业：";
		cin >> select;
		switch(select)
		{
			case 1:
				job = "saber";
				temp = 1;
				break;
			case 2:
				job = "archer";
				temp = 1;
				break;
			case 3:
				job = "caster";
				temp = 1;
				break;
			default:
				cout << "您的输入有误！" << endl;
				break;
		}
	}  

	write(sockfd, job.c_str(), job.size());
	memset(buf, 0, MAXLINE);
	n = read(sockfd, buf, MAXLINE);
	if(n == 0)
		print_disconnect(sockfd);
	str = buf;
	while(str != "success");

	while(1)
	{       
		cout << "请输入昵称：";
		cin >> name;
		write(sockfd, name.c_str(), name.size());
		memset(buf, 0, MAXLINE);
		n = read(sockfd, buf, MAXLINE);
		if(n == 0)
			print_disconnect(sockfd);
		str = buf;
		if(str == "success")
		{
			cout << "创建成功！" << endl;
			break;
		}          
		else
			cout << "昵称已存在！" << endl;
	}
}

character_info character(int sockfd, int account)
{
	string str;
	int  n = 0;
	char buf[MAXLINE];

	pth_simble = 1;

	str = "character";
	write(sockfd, str.c_str(), str.size());
	pthread_mutex_lock(&lock);

	n = read(sockfd, buf, MAXLINE);
	if(n == 0)
		print_disconnect(sockfd);
	str = buf;  
	while(str != "success");

	str = to_string(account);
	write(sockfd, str.c_str(), str.size());
	memset(buf, 0, MAXLINE);
	n = read(sockfd, buf, MAXLINE);
	if(n == 0)
		print_disconnect(sockfd);
	str = buf;
	while(str != "success");

	while(1)
	{
		int num;
		str = "check_character";
		write(sockfd, str.c_str(), str.size());     
		memset(buf, 0, MAXLINE);  
		n = read(sockfd, buf, MAXLINE);
		if(n == 0)
			print_disconnect(sockfd);
		num = atoi(buf);

		if(num == 0)
		{
			cout << "\n您还没创建过角色！下面进行角色创建！" << endl;
			make_character(sockfd);
		}

		else
		{
			str = "character_signin";
			write(sockfd, str.c_str(), str.size());
			string name, job;
			vector<string> Name, Job;
			int select;
			struct character_info player;
			cout << "\n您拥有 " << num << " 个角色，分别是：" << endl;
			for(int i = 0; i < num; ++i)
			{
				memset(buf, 0, MAXLINE);
				n = read(sockfd, buf, MAXLINE);
				if(n == 0)
					print_disconnect(sockfd);
				str = buf;
				name = str;
				Name.push_back(name);
				cout << "昵称：" << name;
				str = "ok";
				write(sockfd, str.c_str(), str.size());

				memset(buf, 0, MAXLINE);
				n = read(sockfd, buf, MAXLINE);
				if(n == 0)
					print_disconnect(sockfd);
				str = buf;
				job = str;
				Job.push_back(job);
				cout << " 职业：" << str << endl;
				str = "ok";
				write(sockfd, str.c_str(), str.size());
			}
			for(int i = 0; i < num; ++i)
			{
				cout << i + 1 << "、" << Name[i] << " ";
			}
			if(num == 3)
			{
				cout << endl;
				cout << "\n请选择角色进入游戏：";
				cin >> select;
				player.name = Name[select-1];
				player.job = Job[select-1];
				str = "over";
				write(sockfd, str.c_str(), str.size());
				pth_simble = 0;
				pthread_mutex_unlock(&lock);
				pthread_cond_signal(&pth_do);
				return player;
			}
			else
			{
				cout << "0、创建角色" << endl;
				cout << "\n请选择角色进入游戏：";
				cin >> select;                
				if(select == 0)
					make_character(sockfd);
				else
				{
					player.name = Name[select-1];
					player.job = Job[select-1];
					str = "over";
					write(sockfd, str.c_str(), str.size());
					pth_simble = 0;
					pthread_mutex_unlock(&lock);
					pthread_cond_signal(&pth_do);
					return player;
				}
			}
		}
	}
}
