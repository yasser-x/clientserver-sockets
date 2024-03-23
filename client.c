#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int client_socket;
    struct sockaddr_in server_address;

    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(12345);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address));

    char data_buffer[1024];
    ssize_t received_data = recv(client_socket, data_buffer, sizeof(data_buffer), 0);

    data_buffer[received_data] = '\0';
    printf("Received message from the server: %s\n", data_buffer);

    close(client_socket);

    return 0;
}