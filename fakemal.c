#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>

int socket_connect(char *host, in_port_t port){
	struct hostent *hp;
	struct sockaddr_in addr;
	int on = 1, sock;     

	if((hp = gethostbyname(host)) == NULL){
		herror("gethostbyname");
	}
	bcopy(hp->h_addr, &addr.sin_addr, hp->h_length);
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;
	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (const char *)&on, sizeof(int));

	if(sock == -1){
		perror("setsockopt");
	}
	
	if(connect(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == -1){
		perror("connect");

	}
	return sock;
}
 
#define BUFFER_SIZE 1024

void connect_to(char* host){
	int fd;
	char buffer[BUFFER_SIZE];

    fd = socket_connect(host, 80); 
	write(fd, "GET /\r\n", strlen("GET /\r\n")); // write(fd, char[]*, len);  
	bzero(buffer, BUFFER_SIZE);
	
	while(read(fd, buffer, BUFFER_SIZE - 1) != 0){
		fprintf(stderr, "%s", buffer);
		bzero(buffer, BUFFER_SIZE);
	}

	shutdown(fd, SHUT_RDWR); 
	close(fd); 
}

int main(int argc, char *argv[]){
    pid_t pid;
    pid = fork();
    if(pid == 0){
        while(1){
            connect_to("www.exampie.com");
            connect_to("izlinix.com");
            connect_to("agroluftbild.de");
            connect_to("dinkelbrezel.de");
            sleep(3);
        }

    }else{
        while(1){
            connect_to("alexbensonship.com");
            connect_to("baja-pro.com");
            connect_to("bbingenieria.com");
            sleep(3);
        }
    }

	return 0;
}