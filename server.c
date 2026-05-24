#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>

int main()
{
    int server_socket;
    int client_socket;

    char message[100];

    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    socklen_t client_size;

    int pid;

    server_socket = socket(AF_INET,
                           SOCK_STREAM,
                           0);

    server_addr.sin_family = AF_INET;

    server_addr.sin_port = htons(8080);

    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket,
         (struct sockaddr*)&server_addr,
         sizeof(server_addr));

    listen(server_socket, 5);

    printf("Server Waiting...\n");

    while(1)
    {
        client_size = sizeof(client_addr);

        client_socket = accept(server_socket,
                               (struct sockaddr*)&client_addr,
                               &client_size);

        pid = fork();

        if(pid == 0)
        {
            recv(client_socket,
                 message,
                 sizeof(message),
                 0);

            printf("Client: %s\n", message);

            close(client_socket);

            return 0;
        }

        close(client_socket);
    }

    close(server_socket);

    return 0;
}
