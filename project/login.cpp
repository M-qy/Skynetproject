#include "login.h"

void Register(int sockfd)
{
    string account, password;
    string str;
    char buf[MAXLINE];

    pth_simble = 1;
    str = "register";
    write(sockfd, str.c_str(), str.size());
    pthread_mutex_lock(&lock);

    cout << "\n注册：" << endl;
    while(1)
    {
        cout << "请输入账号：";
        cin >> account;
        write(sockfd, account.c_str(), account.size());
        read(sockfd, buf, MAXLINE);
        str = buf;
        if(str == "default")
            cout << "账号已存在！" << endl;
        else
            break;
    }
    cout << "请输入密码：";
    cin >> password;
    write(sockfd, password.c_str(), password.size());
    read(sockfd, buf, MAXLINE);
    str = buf;
    while(str != "ok");
    cout << "注册成功！" << endl;

    pth_simble = 0;
    pthread_mutex_unlock(&lock);
}

void Sign_in(int sockfd)
{
    string account, password;
    string str;
    char buf[MAXLINE];

    pth_simble = 1;
    str = "signin";
    write(sockfd, str.c_str(), str.size());
    pthread_mutex_lock(&lock);

    while(1)
    {
        cout << "请输入账号：";
        cin >> account;
        write(sockfd, account.c_str(), account.size());
        read(sockfd, buf, MAXLINE);
        str = buf;
        while(str != "ok");
        cout << "请输入密码：";
        cin >> password;
        write(sockfd, password.c_str(), password.size());
        read(sockfd, buf, MAXLINE);
        str = buf;
        if(str == "default")
            cout << "账号或密码错误！" << endl;
        else
        {
            cout << "登陆成功！" << endl;
            break;
        }            
    }

    pth_simble = 0;
    pthread_mutex_unlock(&lock);
}

int login(int sockfd)
{
    int select;

    cout << "0、离开游戏 1、登陆游戏 2、注册账号" << endl;
    cin >> select;
    switch(select)
    {
    case 0:
        exit(0);
    case 1:
        Sign_in(sockfd);
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