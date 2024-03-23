#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char message_server[] = "Hello client";
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));

    listen(server_socket, 2);

    printf("Server waiting for connection requests...\n");

    client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_len);

    printf("Client connected\n");

    char client_message[1024];
    ssize_t received_data = recv(client_socket, client_message, sizeof(client_message), 0);
    client_message[received_data] = '\0';

    printf("Received message from client: %s\n", client_message);

    send(client_socket, message_server, strlen(message_server), 0);

    close(client_socket);
    close(server_socket);

    return 0;
}