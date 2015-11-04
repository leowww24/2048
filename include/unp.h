#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdio.h>
#include<errno.h>
#include<sys/wait.h>

#define SA struct sockaddr
#define MAXLINE 4096
#define LISTENQ 1024
#define bzero(ptr,n) memset(ptr,0,n)


void err_quit(const char *,...);
void err_sys(const char *,...);
void err_msg(const char *,...);
ssize_t writen(int,const void*,size_t);
ssize_t readline(int,void*,size_t);

