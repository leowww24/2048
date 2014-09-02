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
			printf("buffpro1: %s\n",buffpro);  //debug

			if(!strcmp(buffpro,"game over!!!"))
			{
				other_head_dead=true;
				printf("it's right\n");  //debug
				printf("buffpro2: %s\n",buffpro);  //debug
			}
			else
			{
				int other_score=0;
				int ix=0;
				while(buffpro[ix]!='\0')
					++ix;
				for(int i=ix-1;ix>=0;--ix)
				{
					other_score=other_score*10+buffpro[ix]+'0';
				}
				printf("The other guy scored:");
				printf("%d\n",other_score);
			}
			if(!strcmp(buffpro,"start game\n"))
			{
				pthread_t ntid;
				int err;

				err=pthread_create(&ntid,NULL,thr_fn,NULL);
			}
			else
			{
				strcpy(buffpro,"?");
				writen(connfd,buffpro,n);
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
	strcpy(buffthr,"game over!!!");
	writen(connfd,buffthr,n);

	char score[20];
	int ix;
	for(ix=0;Score!=0;++ix)
	{
		score[ix]=Score%10+'0';
		Score/=10;
	}
	score[ix]='\0';
	strcpy(buffthr,"");
	strcpy(buffthr,score);
	printf("%s\n",buffthr);
	writen(connfd,buffthr,strlen(buffthr));
	exit(0);
}
