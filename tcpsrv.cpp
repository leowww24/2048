#include"unp.h"
#include<pthread.h>

int Score;
void a2srv();
bool other_head_dead;
void* thr_fn(void *arg);

int listenfd, connfd;
ssize_t	n;
char buffpro[MAXLINE];
char buffthr[MAXLINE];

int	main(int argc, char **argv)
{
	struct sockaddr_in	servaddr;
	time_t				ticks;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(1300);	

	bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

	listen(listenfd, LISTENQ);

	for ( ; ; ) {
		connfd = accept(listenfd, (SA *) NULL, NULL);

		while( (n=read(connfd,buffpro,MAXLINE))>0)
		{
			buffpro[n]='\0';
			printf("buffpro1: %s\n",buffpro);  //debug

			if(!strcmp(buffpro,"start game\n"))
			{
				pthread_t ntid;
				int err;

				err=pthread_create(&ntid,NULL,thr_fn,NULL);
			}
			else if(!strcmp(buffpro,"game over!!!\n"))
			{
				other_head_dead=true;
				printf("Game over!\n");  
			}
			else
			{
				int other_score=0;
				int ix=0;
				printf("buffpro1: %s\n",buffpro);  //debug
				while(buffpro[ix]!='\0')
					++ix;
				for(int i=ix-1;i>=0;--i)
				{
					other_score=other_score*10+buffpro[i]-'0';
				}
				printf("The other guy scored: %d\n",other_score);
				exit(0);
			}
		}
		if(n<0)
			err_sys("str_echo:read error");

		close(connfd);
	}
}

void *thr_fn(void* arg)
{
	a2srv();
	printf("Your score is %d\n",Score);
	strcpy(buffthr,"game over!!!\n");
	writen(connfd,buffthr,n);

	char score[20];
	int ix;
	for(ix=0;Score!=0;++ix)
	{
		score[ix]=Score%10+'0';
		Score/=10;
	}
	score[ix]='\0';
	strcpy(buffthr,score);
//	printf("%s\n",buffthr);
	writen(connfd,buffthr,strlen(buffthr));
}
