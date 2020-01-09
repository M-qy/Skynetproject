#include "login.h"

using namespace std;

void Register(int sockfd)
{
    string account, password;
    string str;
    int n = 0;
    char buf[MAXLINE];

    pth_simble = 1;
    str = "register";
    write(sockfd, str.c_str(), str.size());
    pthread_mutex_lock(&lock);

    cout << "\n注册：" << endl;
    while(1)
    {
        cout << "请输入账号(仅限数字，不能0开头)：";
        cin >> account;
        if(account[0] == '0')
        {
            cout << "输入错误！" << endl;
            continue;
        }
        write(sockfd, account.c_str(), account.size());
        memset(buf, 0, MAXLINE);
        n = read(sockfd, buf, MAXLINE);
        if(n == 0)
		    print_disconnect(sockfd);
        str = buf;
        while(str != "success");
        cout << "请输入密码：";
        cin >> password;
        write(sockfd, password.c_str(), password.size());
        memset(buf, 0, MAXLINE);
        n = read(sockfd, buf, MAXLINE);
        if(n == 0)
		    print_disconnect(sockfd);
        str = buf;
        if(str == "default")
        {
            cout << "账号已存在或输入错误！\n" << endl;
            continue;
        }         
        else
        {
            cout << "注册成功！" << endl;
            break;
        }           
    }

    pth_simble = 0;
    pthread_mutex_unlock(&lock);
	pthread_cond_signal(&pth_do);
}

int Sign_in(int sockfd)
{
    string account, password;
    string str;
    int n = 0;
    char buf[MAXLINE];

    pth_simble = 1;
    str = "signin";
    write(sockfd, str.c_str(), str.size());
    pthread_mutex_lock(&lock);

    cout << "请输入账号：";
    cin >> account;
    write(sockfd, account.c_str(), account.size());
    n = read(sockfd, buf, MAXLINE);
    if(n == 0)
        print_disconnect(sockfd);
    str = buf;
    cout << "请输入密码：";
    cin >> password;
    write(sockfd, password.c_str(), password.size());
    memset(buf, 0, MAXLINE);
    n = read(sockfd, buf, MAXLINE);
    if(n == 0)
        print_disconnect(sockfd);
    str = buf;
    if(str == "default")
    {
        cout << "账号或密码错误！" << endl;
        pth_simble = 0;
        pthread_mutex_unlock(&lock);
		pthread_cond_signal(&pth_do);
        return 0;
    }
    else
    {
        cout << "登录成功！" << endl;
		str = to_string(sockfd);
		write(sockfd, str.c_str(), str.size());
        pth_simble = 0;
        pthread_mutex_unlock(&lock);
		pthread_cond_signal(&pth_do);
        int ret = atoi(account.c_str());
        return ret;
    }             
}

int login(int sockfd)
{
	while(1)
	{
		int select, ret;
		cout << "\n1、登录游戏 2、注册账号" << endl;
		cin >> select;
		switch(select)
		{
		case 1:
			ret = Sign_in(sockfd);
			return ret;
		case 2:
			Register(sockfd);
			break;
		default:
			cout << "您的输入有误！" << endl;
			break;
		}
	}
}
