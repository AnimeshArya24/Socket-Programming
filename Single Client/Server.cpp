#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>

#define PORT 8080

int main()
{

    struct sockaddr_in soc
    {
    };

    int Listner_soc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (Listner_soc < 0)
    {
        std::cout << "Socket API failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        std::cout << "Socket successfull" << std::endl;
    }

    soc.sin_family = AF_INET;
    soc.sin_port = htons(PORT);
    soc.sin_addr.s_addr = INADDR_ANY;
    // memset(&soc.sin_zero,0,sizeof(soc));

    int nStatus = bind(Listner_soc, (struct sockaddr *)&soc, sizeof(soc));

    if (nStatus < 0)
    {
        std::cout << "Bind failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        std::cout << "Bind Successful" << std::endl;
    }

    nStatus = listen(Listner_soc, 5);
    if (nStatus < 0)
    {
        std::cout << "listen failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        std::cout << "Listen Successful" << std::endl;
    }

    socklen_t n = sizeof(soc);
    int Accept_soc = accept(Listner_soc,NULL,&n);

    if (Accept_soc < 0)
    {
        std::cout << "Accept Failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        // char buffer[1024]={0,};
        std::string buffer;
        while (true)
        {
            int Reciver = recv(Accept_soc, &buffer, buffer.length(), 0);
            if (Reciver > 0)
            {
                std::cout << buffer << std::endl;
            }
        }
    }
}