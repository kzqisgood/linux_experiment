#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void *receive_messages(void *arg) {
    int server_socket = *((int *)arg);
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    while (1) {
        ssize_t bytes_received = recvfrom(server_socket, buffer, BUFFER_SIZE, 0,
                                         (struct sockaddr *)&client_addr, &client_addr_len);
        if (bytes_received <= 0) {
            perror("recvfrom error");
            break;
        }

        buffer[bytes_received] = '\0';
        printf("Client: %s\n", buffer);

        // 如果收到 "quit"，则退出接收线程
        if (strncmp(buffer, "quit", 4) == 0) {
            break;
        }
    }

    return NULL;
}

int main() {
    int server_socket;
    struct sockaddr_in server_addr;

    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Socket binding failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);

    pthread_t thread_id;
    if (pthread_create(&thread_id, NULL, receive_messages, (void *)&server_socket) != 0) {
        perror("Thread creation failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    while (1) {
        printf("Server: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        sendto(server_socket, buffer, strlen(buffer), 0,
               (struct sockaddr *)&client_addr, client_addr_len);

        // 如果输入 "quit"，则退出服务器
        if (strncmp(buffer, "quit", 4) == 0) {
            break;
        }
    }

    // 等待接收线程结束
    pthread_join(thread_id, NULL);

    // 关闭服务器Socket
    close(server_socket);

    return 0;
}

