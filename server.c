#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT_NUM 4000

int main(){

    int server_fd;
    if((server_fd = socket(AF_INET,SOCK_STREAM,0))<0){
        perror("Socket couldn't be created!\n");
        return -1;
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT_NUM);
    address.sin_addr.s_addr = INADDR_ANY;
    socklen_t addrlen = sizeof(address);

    if((bind(server_fd,(struct sockaddr *)&address,(socklen_t)addrlen)<0)){
        perror("Bind failed!\n");
        close(server_fd);
        return -1;
    }

    if((listen(server_fd,10)<0)){
        perror("Socket can't listen!\n");
        close(server_fd);
        return -1;
    }

    printf("Connection waiting!\n");
    int client_fd;
    if(( client_fd = accept(server_fd,(struct sockaddr *)&address,(socklen_t*)&addrlen))<0){
        perror("Socket couldn't be accepted!\n");
        close(server_fd);
        return -1;
    }
    printf("Connection established!\n");

    char szMessageReceived[1024] = {0};
    int messageSize = recv(client_fd,szMessageReceived,1024,0);
    printf("Message Size : %d \nMessage Received : %s\n",messageSize,szMessageReceived);

    char szMessage[100] = "Message from server";
    send(client_fd,szMessage,strlen(szMessage),0);
    printf("Message sent from server!\n");

    
    shutdown(server_fd,SHUT_RDWR);
    close(server_fd);

    return 0;

}