#include "characters.h"
#include "saber.h"

void make_character(int sockfd)
{
    string str;
    char buf[MAXLINE];
    string job, name;
    int select;
    cout << "1、剑客 2、射手 3、法师" << endl;
    cout << "请选择职业：";
    cin >> select;
    switch(select)
    {
        case 1:
            job = "Saber";
            break;
        case 2:
            job = "Archer";
            break;
        case 3:
            job = "Caster";
            break;
    }
    while(1)
    {       
        cout << "请输入昵称：";
        cin >> name;
        write(sockfd, name.c_str(), name.size());
        read(sockfd, buf, MAXLINE);
        str = buf;
        if(str == "ok")
        {
            cout << "创建成功！" << endl;
            break;
        }          
        else
            cout << "昵称已存在！" << endl;
    }
}

string character(int sockfd)
{
    string str;
    char buf[MAXLINE];

    pth_simble = 1;

    str = "charater";
    write(sockfd, str.c_str(), str.size());
    pthread_mutex_lock(&lock);

    while(1)
    {
        str = "check_charater";
        write(sockfd, str.c_str(), str.size());
        int num;
        read(sockfd, buf, MAXLINE);

        num = atoi(buf);
        if(num == 0)
        {
            cout << "您还没创建过角色！下面进行角色创建！" << endl;
            make_character(sockfd);
        }

        else if(num ==3)
        {
            vector<string> Name;
            int select;
            cout << "您拥有 " << num << " 个角色，分别是：" << endl;
            for(int i = 0; i < num; ++i)
            {
                string name;

                str = "ok";
                write(sockfd, str.c_str(), str.size());
                read(sockfd, buf, MAXLINE);
                str = buf;
                name = str;
                Name.push_back(name);
                cout << "昵称：" << name;

                str = "ok";
                write(sockfd, str.c_str(), str.size());
                read(sockfd, buf, MAXLINE);
                str = buf;
                cout << " 职业：" << str << endl;
            }
            for(int i = 0; i < num; ++i)
            {
                cout << i + 1 << "、" << Name[i] << " ";
            }
            cout << "\n请选择角色进入游戏：";
            cin >> select;
            str = "over";
            write(sockfd, str.c_str(), str.size());
            return Name[select - 1];
        }

        else
        {
            vector<string> Name;
            int select;
            cout << "您拥有 " << num << " 个角色，分别是：" << endl;
            for(int i = 0; i < num; ++i)
            {
                string name;

                str = "ok";
                write(sockfd, str.c_str(), str.size());
                read(sockfd, buf, MAXLINE);
                str = buf;
                name = str;
                Name.push_back(name);
                cout << "昵称：" << name;

                str = "ok";
                write(sockfd, str.c_str(), str.size());
                read(sockfd, buf, MAXLINE);
                str = buf;
                cout << " 职业：" << str << endl;
            }
            for(int i = 0; i < num; ++i)
            {
                cout << i + 1 << "、" << Name[i] << " ";
            }
            cout << "0、创建角色";
            cout << "\n请选择角色进入游戏：";
            cin >> select;
            if(select == 0)
                make_character(sockfd);
            else
            {
                str = "over";
                write(sockfd, str.c_str(), str.size());
                return Name[select - 1];
            }                
        }      
    }
}