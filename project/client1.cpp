#include <iostream>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

using namespace std;

#define MAXLINE 128
#define SERV_PORT 8001

int buf_com(char* buf, char* str)
{
	if(strlen(buf) != strlen(str))
		return 0;
	else
	{
		for(int i = 0; i < strlen(buf); ++i, ++str)
		{
			if(buf[i] != *str)
			    return 0;
		}
	}
	return 1;
}

void Register(int sockfd)
{
    char* account;
    char* password;
    char* str;
    char buf[MAXLINE];

    cout << "\n注册：" << endl;
    while(1)
    {
        cout << "请输入账号：";
        cin >> account;
        str = "check_account";
        write(sockfd, str, strlen(str));
        read(sockfd, buf, MAXLINE);
        if(buf_com(buf, "ok"))
        {
            write(sockfd, account, strlen(account));
            read(sockfd, buf, MAXLINE);
            if(buf_com(buf, "default"))
                cout << "账号已存在！" << endl;
            else
                break;
        }       
    }
    cout << "请输入密码：";
}

int login(int sockfd)
{
    int select;
    int accout;
    string password;
    cout << "0、离开游戏 1、登陆游戏 2、注册账号" << endl;
    cin >> select;
    switch(select)
    {
    case 0:
        exit(0);
    case 1:
        return 1;
    case 2:
        Register(sockfd);
        return 1;
    default:
        cout << "您的输入有误！" << endl;
        break;
    }
    return 0;
}

int main()
{
    struct sockaddr_in servaddr;
	int sockfd;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
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

    cout << "欢迎进入游戏！" << endl;

    int ret = 0;
    while(ret = 0)
        ret = login(sockfd);
}