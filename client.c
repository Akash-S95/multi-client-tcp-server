#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>

int main()
{
    int client_socket;

    char message[100];

    struct sockaddr_in server_addr;

    client_socket = socket(AF_INET,
                           SOCK_STREAM,
                           0);

    server_addr.sin_family = AF_INET;

    server_addr.sin_port = htons(8080);

    inet_pton(AF_INET,
              "127.0.0.1",
              &server_addr.sin_addr);

    connect(client_socket,
            (struct sockaddr*)&server_addr,
            sizeof(server_addr));

    printf("Enter Name and Roll Number:\n");

    fgets(message,
          sizeof(message),
          stdin);

    send(client_socket,
         message,
         strlen(message),
         0);

    close(client_socket);

    return 0;
}
