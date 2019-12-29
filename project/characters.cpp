#include "characters.h"
#include "saber.h"

using namespace std;

Character& character_init(string name)
{
    Saber* saber = new Saber(name);
    Character* character;
    character = saber;
}

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
    {
        printf("The other side has been closed\n");
        close(sockfd);
        exit(0);
    }
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
    {
        printf("The other side has been closed\n");
        close(sockfd);
        exit(0);
    }
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
        {
            printf("The other side has been closed\n");
            close(sockfd);
            exit(0);
        }
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

string character(int sockfd, int account)
{
    string str, name;
    int  n = 0;
    char buf[MAXLINE];

    pth_simble = 1;

    str = "character";
    write(sockfd, str.c_str(), str.size());
    pthread_mutex_lock(&lock);

    n = read(sockfd, buf, MAXLINE);
    if(n == 0)
    {
        printf("The other side has been closed\n");
        close(sockfd);
        exit(0);
    }
    str = buf;  
    while(str != "success");

    str = to_string(account);
    write(sockfd, str.c_str(), str.size());
    memset(buf, 0, MAXLINE);
    n = read(sockfd, buf, MAXLINE);
    if(n == 0)
    {
        printf("The other side has been closed\n");
        close(sockfd);
        exit(0);
    }
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
        {
            printf("The other side has been closed\n");
            close(sockfd);
            exit(0);
        }
        num = atoi(buf);

        if(num == 0)
        {
            cout << "您还没创建过角色！下面进行角色创建！" << endl;
            make_character(sockfd);
        }

        else
        {
            str = "character_signin";
            write(sockfd, str.c_str(), str.size());
            vector<string> Name;
            int select;
            cout << "您拥有 " << num << " 个角色，分别是：" << endl;
            for(int i = 0; i < num; ++i)
            {
                memset(buf, 0, MAXLINE);
                n = read(sockfd, buf, MAXLINE);
                if(n == 0)
                {
                    printf("The other side has been closed\n");
                    close(sockfd);
                    exit(0);
                }
                str = buf;
                name = str;
                Name.push_back(name);
                cout << "昵称：" << name;
                str = "ok";
                write(sockfd, str.c_str(), str.size());

                memset(buf, 0, MAXLINE);
                n = read(sockfd, buf, MAXLINE);
                if(n == 0)
                {
                    printf("The other side has been closed\n");
                    close(sockfd);
                    exit(0);
                }
                str = buf;
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
                str = "over";
                write(sockfd, str.c_str(), str.size());
                pth_simble = 0;
                pthread_mutex_unlock(&lock);
                return Name[select - 1];
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
                    str = "over";
                    write(sockfd, str.c_str(), str.size());
                    pth_simble = 0;
                    pthread_mutex_unlock(&lock);
                    return Name[select - 1];
                }
            }
        }
    }
}