#include "package.h"

using namespace std;

int package_init(int sockfd, string name, map<string, int> &package)
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
	cout << buf << endl;
	while(str != "ok");

	write(sockfd, name.c_str(), name.size());

	while(1)
	{
		memset(buf, 0, MAXLINE);
		n = read(sockfd, buf, MAXLINE);
		if(n == 0)
			print_disconnect(sockfd);
		str = buf;
		if(str == "over")
			break;
		name = buf;
		cout << name << " ";
		
		str = "ok";
		write(sockfd, str.c_str(), str.size());

		memset(buf, 0, MAXLINE);
		n = read(sockfd, buf, MAXLINE);
		if(n == 0)
			print_disconnect(sockfd); 
		num = atoi(buf);
		cout << num << endl;
		package.insert(make_pair(name, num));
		str = "ok";
		write(sockfd, str.c_str(), str.size()); 
	}

	pth_simble = 0;
    pthread_mutex_unlock(&lock);
	pthread_cond_signal(&pth_do);
	return 1;
}

