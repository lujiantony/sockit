#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 

int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr; 

    char sendBuff[1025];
    time_t ticks; 
    char *info="Connection established";
    struct sockaddr_in client_addr;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(42000); 

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

    listen(listenfd, 10); 
    socklen_t len = sizeof client_addr;
    char ipstr[INET6_ADDRSTRLEN];
    while(1)
    {
        connfd = accept(listenfd, (struct sockaddr*)&client_addr, NULL); 
	getpeername(connfd,(struct sockaddr*)&client_addr,&len);
	struct sockaddr_in *s = (struct sockaddr_in *)&client_addr;
	inet_ntop(AF_INET,&s->sin_addr,ipstr, sizeof ipstr);
	printf("Peer IP address: %s\n",ipstr);
        ticks = time(NULL);
	printf("%d.%d.%d.%d\n",
  	(int)(client_addr.sin_addr.s_addr&0xFF),
  	(int)((client_addr.sin_addr.s_addr&0xFF00)>>8),
  	(int)((client_addr.sin_addr.s_addr&0xFF0000)>>16),
  	(int)((client_addr.sin_addr.s_addr&0xFF000000)>>24));
	printf("IP address is : %s\n",inet_ntoa(client_addr.sin_addr));
        snprintf(sendBuff, sizeof(sendBuff), "%s\r\n",info);
        write(connfd, sendBuff, strlen(sendBuff)); 
	
        close(connfd);
        sleep(1);
     }
}
