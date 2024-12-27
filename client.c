#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 4000
#define BUF_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char send_buf[BUF_SIZE], recv_buf[BUF_SIZE];
    const char *request = "GET /index.html HTTP/1.0\r\nHost: localhost\r\n\r\n";

    // 创建套接字
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 设置服务器地址
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(PORT);

    // 连接到服务器
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connection to server failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // 发送请求
    send(sockfd, request, strlen(request), 0);

    // 接收服务器响应
    int bytes_received;
    while ((bytes_received = recv(sockfd, recv_buf, BUF_SIZE - 1, 0)) > 0) {
        recv_buf[bytes_received] = '\0'; // 添加字符串结束符
        printf("%s", recv_buf); // 打印响应内容
    }

    if (bytes_received < 0) {
        perror("recv failed");
    }

    // 关闭套接字
    close(sockfd);
    return 0;
}