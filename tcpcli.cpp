#include"unp.h"
#include<pthread.h>

int Score;
void a2srv();
bool other_head_dead;
void* thr_fn(void *arg);

int	sockfd, n;			
char sendline[MAXLINE],recvline[MAXLINE];

int main(int argc, char **argv)
{
	struct sockaddr_in	servaddr;
	pid_t pid;

	if (argc != 2)
		err_quit("usage: a.out <IPaddress>");

	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_sys("socket error");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(1300);	
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
		err_quit("inet_pton error for %s", argv[1]);

	if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
		err_sys("connect error");


	while(fgets(sendline,MAXLINE,stdin)!=NULL)
	{
		writen(sockfd,sendline,strlen(sendline));
		if(!strcmp(sendline,"start game\n"))
		{
			pthread_t ntid;
			int err;

			err=pthread_create(&ntid,NULL,thr_fn,NULL);
		}
		if(readline(sockfd,recvline,MAXLINE)==0)
			err_quit("str_cli:server terminated prematurely");
		else
			fputs(recvline,stdout);
		if(!strcmp(recvline,"game over!!!"))
		{
			other_head_dead=true;
		}
	}

	exit(0);
}

void *thr_fn(void* arg)
{
	a2srv();
	printf("Your score is %d\n",Score);
	strcpy(sendline,"game over!!!");
	printf("%s\n",sendline);
	writen(sockfd,sendline,strlen(sendline));

	char score[20];
	int ix;
	for(ix=0;Score!=0;++ix)
	{
		score[ix]=Score%10+'0';
		Score/=10;
	}
	score[ix]='\0';
	strcpy(sendline,score);
	sleep(1);
	int kk;
	kk=writen(sockfd,sendline,strlen(sendline));
	printf("%d\n",kk);
	printf("%s\n",sendline);
	exit(0);
}
