#include "package.h"

using namespace std;

int package_find(vector<Things_str*>&package, string name)
{
	int i = 0;
	for(auto it = package.begin(); it != package.end(); ++it, ++i)
	{
		if((*it)->things->get_name() == name)
			return i;
	}
	return -1;
}

int package_init(int sockfd, string name, vector<Things_str*>&package)
{
	string str;
    int n = 0;
    char buf[MAXLINE];
	int num;

    pth_simble = 1;
    str = "package";
    write(sockfd, str.c_str(), str.size());
    pthread_mutex_lock(&lock); 
	
	n = read(sockfd, buf, MAXLINE);
	if(n == 0)
		print_disconnect(sockfd);
	str = buf;
	while(str != "ok");

	write(sockfd, name.c_str(), name.size());

	while(1)
	{
		Things_str *things_str = new Things_str;

		memset(buf, 0, MAXLINE);
		n = read(sockfd, buf, MAXLINE);
		if(n == 0)
			print_disconnect(sockfd);
		str = buf;
		if(str == "over")
			break;
		name = buf;
		
		str = "ok";
		write(sockfd, str.c_str(), str.size());

		memset(buf, 0, MAXLINE);
		n = read(sockfd, buf, MAXLINE);
		if(n == 0)
			print_disconnect(sockfd); 
		num = atoi(buf);

		if(name == "sword1")
			(*things_str).things = new Sword1();
		else if(name == "sword2")
			(*things_str).things = new Sword2();
		else if(name == "armor1")
			(*things_str).things = new Armor1();
		else if(name == "armor2")
			(*things_str).things = new Armor2(); 

		(*things_str).num = num;
		package.push_back(things_str);
		str = "ok";
		write(sockfd, str.c_str(), str.size()); 
	}

	pth_simble = 0;
    pthread_mutex_unlock(&lock);
	pthread_cond_signal(&pth_do);
	return 1;
}

