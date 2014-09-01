#include	"unp.h"

static void sig_handle(int);
static bool game_over;

int
main(int argc, char **argv)
{
	int	sockfd, n;			
	char sendline[MAXLINE],recvline[MAXLINE];
	struct sockaddr_in	servaddr;

	if (argc != 2)
		err_quit("usage: a.out <IPaddress>");

	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_sys("socket error");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(1300);	/* daytime server */
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
		err_quit("inet_pton error for %s", argv[1]);

	if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
		err_sys("connect error");

	game_over=false;
	if(signal(SIGINT,sig_handle)==SIG_ERR)
		err_sys("signal error");

	while(!game_over&&fgets(sendline,MAXLINE,stdin)!=NULL)
	{
		writen(sockfd,sendline,strlen(sendline));
		if(readline(sockfd,recvline,MAXLINE)==0)
			err_quit("str_cli:server terminated prematurely");
		if(!strcmp(recvline,"game over\n"))
			raise(SIGINT);
		else
			fputs(recvline,stdout);
	}

	exit(0);
}

void sig_handle(int signo)
{
	game_over=true;
	printf("signal received\n");
}
