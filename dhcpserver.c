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
	char fileGetIPAddr[50];
 FILE *fileStream, *fileTemp;
    char buffer[1024];

    struct sockaddr_in server_addr, client_addr;



    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {

        perror("Socket creation failed");

        exit(EXIT_FAILURE);

    }



    memset(&server_addr, 0, sizeof(server_addr));

    memset(&client_addr, 0, sizeof(client_addr));



    server_addr.sin_family = AF_INET;

    server_addr.sin_port = htons(SERVER_PORT);

    server_addr.sin_addr.s_addr = INADDR_ANY;



    // Bind to any available port for receiving messages

   

    if (bind(sockfd, (const struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {

        perror("Bind failed");

        exit(EXIT_FAILURE);

    }


	struct abc tem;

    // Receive the message from Client 1

    socklen_t len = sizeof(server_addr);

    ssize_t n = recvfrom(sockfd, (struct abc*)&tem, sizeof(struct abc), 0, (struct sockaddr*)&client_addr, &len);

    buffer[n] = '\0';

    printf("Received DHCP Discover %s\n sending offer ", buffer);
 fileStream = fopen("IPaddress.txt", "r"); //Open the IPaddress file for reading
            fgets(fileGetIPAddr, 50, fileStream); //Get the IP Address from the file to assign to the client
strcpy(tem.a,"offer");
            strcpy(tem.a, fileGetIPAddr); //Assign it to the client

tem.time=10;
sendto(sockfd, (struct abc*)&tem, sizeof(struct abc), 0, (const struct sockaddr*)&client_addr, sizeof(client_addr));



 n = recvfrom(sockfd,  (struct abc*)&tem, sizeof(struct abc), 0, (struct sockaddr*)&client_addr, &len);

    buffer[n] = '\0';

    printf("Received DHCP request %s\n sending ACK", buffer);

sendto(sockfd, (struct abc*)&tem, sizeof(struct abc), 0, (const struct sockaddr*)&client_addr, sizeof(client_addr));

recvfrom(sockfd, (struct abc*)&tem, sizeof(struct abc), 0, (struct sockaddr*)&client_addr, &len);
printf("renew recieved");
strcpy(tem.a,"ACK renew");
sendto(sockfd, (struct abc*)&tem, sizeof(struct abc), 0, (const struct sockaddr*)&client_addr, sizeof(client_addr));

    close(sockfd);

    return 0;

}
