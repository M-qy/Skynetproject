#include "package.h"

using namespace std;

map<string, int>& package_init(int sockfd, string name)
{
	string str;
    int n = 0;
    char buf[MAXLINE];
	int num;
	map<string, int> package; 

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

	while(str != "over")
	{
		memset(buf, 0, MAXLINE);
		n = read(sockfd, buf, MAXLINE);
		if(n == 0)
			print_disconnect(sockfd);
		name = buf;
		
		str = "ok";
		write(sockfd, str.c_str(), str.size());

		memset(buf, 0, MAXLINE);
		n = read(sockfd, buf, MAXLINE);
		if(n == 0)
			print_disconnect(sockfd); 
		num = atoi(buf);
		package.insert(make_pair(name, num));
		str = "ok";
		write(sockfd, str.c_str(), str.size()); 
	}

	pth_simble = 0;
    pthread_mutex_unlock(&lock);
	pthread_cond_signal(&pth_do);
	return package;
}

