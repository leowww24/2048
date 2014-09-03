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
		int n;
		int other_score=0;
		int ix=0;
		if(!strcmp(sendline,"start game\n"))
		{
			pthread_t ntid;
			int err;

			writen(sockfd,sendline,strlen(sendline));
			printf("After 3 seconds,the game will begin...\n");
			sleep(3);
			err=pthread_create(&ntid,NULL,thr_fn,NULL);
		}
		else
		{
			printf("Please input 'start game' to run the game!\n");
			continue;
		}
		while( (n=readline(sockfd,recvline,MAXLINE))!=0)
		{
			if(!strcmp(recvline,"game over!!!\n"))
			{
				other_head_dead=true;
				printf("Game over!\nWaiting for the result!\n");
			}
			else
			{
				recvline[n]='\0';
				//printf("%d\n",n);	//debug;
				//printf("%s\n",recvline);	//debug
				while(recvline[ix]!='\0')
					++ix;
				for(int i=ix-1;i>=0;--i)
				{
					other_score=other_score*10+recvline[i]-'0';
				}
				printf("The other guy scored: %d\n",other_score);
				if(Score>other_score)
					printf("You win!\n");
				else if(Score<other_score)
					printf("You lose!\n");
				else
					printf("The game ends in a tie!\n");
				exit(0);
			}
		}
	}

	exit(0);
}

void *thr_fn(void* arg)
{
	a2srv();
	printf("Your score is %d\n",Score);
	strcpy(sendline,"game over!!!\n");
	//printf("%s\n",sendline); //debug
	writen(sockfd,sendline,strlen(sendline));
	sleep(1);

	char score[20];
	int ix;
	int temp=Score;
	if(temp==0)
	{
		score[0]='0';
		score[1]='\0';
	}
	else
	{
		for(ix=0;temp!=0;++ix)
		{
			score[ix]=temp%10+'0';
			temp/=10;
		}
		score[ix]='\0';
	}
	strcpy(sendline,score);
	//printf("%s\n",sendline);  //debug
	writen(sockfd,sendline,strlen(sendline));
}
