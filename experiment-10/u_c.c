#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(PORT);

    while (1) {
        printf("Client: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        sendto(client_socket, buffer, strlen(buffer), 0,
               (struct sockaddr *)&server_addr, sizeof(server_addr));

        // 如果输入 "quit"，则退出客户端
        if (strncmp(buffer, "quit", 4) == 0) {
            break;
        }

        ssize_t bytes_received = recvfrom(client_socket, buffer, BUFFER_SIZE, 0, NULL, NULL);
        if (bytes_received <= 0) {
            perror("recvfrom error");
            break;
        }

        buffer[bytes_received] = '\0';
        printf("Server: %s\n", buffer);

        // 如果收到 "quit"，则退出客户端
        if (strncmp(buffer, "quit", 4) == 0) {
            break;
        }
    }

    // 关闭客户端Socket
    close(client_socket);

    return 0;
}

