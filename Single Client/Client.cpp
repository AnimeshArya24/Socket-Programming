#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT 8080

int main() {

    struct sockaddr_in soc{};

    int Clinet_socket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

    if(Clinet_socket<0){
        std::cout << "Unsuccessful" << std::endl;
        exit(EXIT_FAILURE);
    }

    soc.sin_family = AF_INET;
    soc.sin_port = htons(PORT);
    soc.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(&soc.sin_zero,0,sizeof(soc));


    size_t Status_client = connect(Clinet_socket,(struct sockaddr*)&soc,sizeof(soc));

    if(Status_client<0){
        std::cout << "Connection Failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    else{
        while(true){
            // char msg[1024];
            std::string msg;
            std::cin>>msg;
            // fgets(msg,1024,stdin);
            Status_client = send(Clinet_socket,&msg,1024,0);
            if(Status_client<0){
                std::cout << "Failed to send" << std::endl;
                exit(EXIT_FAILURE);
            }
            else if(Status_client>0){
                std::cout << "Message Sent" << std::endl;
            }
        }
    }
}