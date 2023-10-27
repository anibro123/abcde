#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <arpa/inet.h>

#include <unistd.h>

#include <sys/socket.h>

#include <netinet/in.h>



#define SERVER_IP "127.0.0.1"

#define SERVER_PORT 1234
struct abc{
int time;
char a[100];

};


int main() {

    int sockfd;

    char buffer[1024];

    struct sockaddr_in server_addr;



    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {

        perror("Socket creation failed");

        exit(EXIT_FAILURE);

    }



    memset(&server_addr, 0, sizeof(server_addr));



    server_addr.sin_family = AF_INET;

    server_addr.sin_port = htons(SERVER_PORT);

    server_addr.sin_addr.s_addr = INADDR_ANY;


struct abc tem;
strcpy(tem.a,"Discover");
    
    sendto(sockfd, (struct abc*)&tem, sizeof(struct abc), 0, (const struct sockaddr*)&server_addr, sizeof(server_addr));

    int len =sizeof(server_addr);

recvfrom(sockfd, (struct abc*)&tem, sizeof(struct abc), 0, (struct sockaddr*)&server_addr, &len);

printf("Received offer: %s\n", tem.a);

printf("sending request");

sendto(sockfd, (struct abc*)&tem, sizeof(struct abc), 0, (const struct sockaddr*)&server_addr, sizeof(server_addr));

     len =sizeof(server_addr);

recvfrom(sockfd, (struct abc*)&tem, sizeof(struct abc), 0, (struct sockaddr*)&server_addr, &len);
printf("Received ACK: %s\n", buffer);
printf("\n time =%d counting half of timer\n",tem.time);
sleep(tem.time/2);

strcpy(tem.a,"renew");
sendto(sockfd, (struct abc*)&tem, sizeof(struct abc), 0, (const struct sockaddr*)&server_addr, sizeof(server_addr));

recvfrom(sockfd, (struct abc*)&tem, sizeof(struct abc), 0, (struct sockaddr*)&server_addr, &len);
printf("\n%s",tem.a);


    close(sockfd);

    return 0;

}
