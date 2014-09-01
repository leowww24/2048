#include	"unp.h"

int a2srv();

int
main(int argc, char **argv)
{
	int					listenfd, connfd;
	ssize_t				n;
	struct sockaddr_in	servaddr;
	char				buff[MAXLINE];
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

		while( (n=read(connfd,buff,MAXLINE))>0)
		{
			if(!strcmp(buff,"start game\n"))
			{
				int res=a2srv();
				printf("Your score is %d\n",res);
				writen(connfd,buff,n);
			}
			else
				writen(connfd,buff,n);
		}
		if(n<0)
			err_sys("str_echo:read error");

		close(connfd);
	}
}
