#include "player_init.h"
#include "arms.h"
#include "armors.h"
#include "swords.h"

using namespace std;

int player_init(Character *cha, int sockfd, string name, string job)
{
    string str;
    int n = 0;
    char buf[MAXLINE];

    pth_simble = 1;
    str = "player_init";
    write(sockfd, str.c_str(), str.size());
    pthread_mutex_lock(&lock);
    
    n = read(sockfd, buf, MAXLINE);
    if(n == 0)
        print_disconnect(sockfd);
    str = buf;
    while(str != "ok");

    write(sockfd, name.c_str(), name.size());
    memset(buf, 0, MAXLINE);
    n = read(sockfd, buf, MAXLINE);
    if(n == 0)
        print_disconnect(sockfd);
    str = buf;
    while(str != "ok");

    write(sockfd, job.c_str(), job.size());
    memset(buf, 0, MAXLINE);
    n = read(sockfd, buf, MAXLINE);
    if(n == 0)
        print_disconnect(sockfd);
    str = buf;
    while(str != "ok");

    int blood, attack, defense;

    memset(buf, 0, MAXLINE);
    n = read(sockfd, buf, MAXLINE);
    if(n == 0)
        print_disconnect(sockfd);
    blood = atoi(buf);
    str = "ok";
    write(sockfd, str.c_str(), str.size());

    memset(buf, 0, MAXLINE);
    n = read(sockfd, buf, MAXLINE);
    if(n == 0)
        print_disconnect(sockfd);
    attack = atoi(buf);
    str = "ok";
    write(sockfd, str.c_str(), str.size());

    memset(buf, 0, MAXLINE);
    n = read(sockfd, buf, MAXLINE);
    if(n == 0)
        print_disconnect(sockfd);
    defense = atoi(buf);
    str = "ok";
    write(sockfd, str.c_str(), str.size());

    Armor  *armor;
    Arm *arm;

    memset(buf, 0, MAXLINE);
    n = read(sockfd, buf, MAXLINE);
    if(n == 0)
        print_disconnect(sockfd);
    str = buf;
    if(str == "Sword1")
    {
        arm = new Sword1();
        arm->init(cha);
        cha->Puton_arm(arm);
    }
    else if(str == "Sword2")
    {
        arm = new Sword2();
        arm->init(cha);
        cha->Puton_arm(arm);
    }
    str = "ok";
    write(sockfd, str.c_str(), str.size());

    memset(buf, 0, MAXLINE);
    n = read(sockfd, buf, MAXLINE);
    if(n == 0)
        print_disconnect(sockfd);
    str = buf;
    if(str == "Armor1")
    {
        armor = new Armor1();
        armor->init(cha);
        cha->Puton_armor(armor);
    }
    else if(str == "Armor2")
    {
        armor = new Armor2();
        armor->init(cha);
        cha->Puton_armor(armor);
    }
    
    pth_simble = 0;
    pthread_mutex_unlock(&lock);
    return 1;
}