#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT_NUM 4000

int main(){

    int client_fd;
    if((client_fd = socket(AF_INET,SOCK_STREAM,0))< 0){
        perror("Socket couldn't be created!\n");
        return -1;
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT_NUM);
    socklen_t addrlen = sizeof(address);

    if(inet_pton(AF_INET,"127.0.0.1",&address.sin_addr) < 1){
        perror("Address is invalid or not supported!\n");
        return -1;
    }

    int connectionStatus = connect(client_fd,(struct sockaddr*)&address,addrlen);
    if(connectionStatus < 0){
        perror("Connection couldn't be established!\n");
        return -1;
    }
    printf("Connection established!\n");

    char szMessage[100] = "Message from client!\n";
    send(client_fd,szMessage,strlen(szMessage),0);
    printf("Message sent from client!\n");
    
    char szMessageReceived[1024] = {0};
    int messageSize = recv(client_fd,szMessageReceived,1023,0);
    printf("Message Size : %d \nMessage Received : %s\n",messageSize,szMessageReceived);

    close(client_fd);

    return 0;

}