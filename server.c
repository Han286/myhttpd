/* Han's Webserver*/
/* This is a simple webserver based on J. David's webserver */
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

int startup(uint16_t *);
void error_die(const char *);
void accept_request(void *);

int startup(uint16_t* port) {
    int httpd = 0;
    int on = 1;
    struct sockaddr_in name;

    httpd = socket(PF_INET, SOCK_STREAM, 0);
    if (httpd == -1)
        error_die("socket");
    memset(&name, 0, sizeof(name));
    name.sin_family = AF_INET;
    name.sin_port = htons(*port);
    name.sin_addr.s_addr = htonl(INADDR_ANY);
    if ((setsockopt(httpd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))) < 0) {  
        error_die("setsockopt failed");
    }
    if (bind(httpd, (struct sockaddr *)&name, sizeof(name)) < 0) {
        error_die("bind");
    }
    if (listen(httpd, 5) < 0)
        error_die("listen");
    return httpd;
}

void accept_request(void *arg) {

}

void error_die(const char *sc)
{
    perror(sc);
    exit(1);
}


int main() {
    int server_sock = -1;
    uint16_t port = 4000;
    int client_sock = -1;
    struct sockaddr_in client_name;
    socklen_t client_name_len = sizeof(client_name);

    // server socket initialize
    server_sock = startup(&port);
    printf("httpd running on port %d\n", port);

    while (1) {
        client_sock = accept(server_sock, (struct sockaddr *)&client_name, &client_name_len);
        // 处理客户端请求
        char buffer[1024];
        ssize_t bytes_received = recv(client_sock, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received > 0) {
            buffer[bytes_received] = '\0'; // 添加字符串结束符
            printf("Received message: %s\n", buffer);
        }

        if (client_sock == -1)
            error_die("accept");
        accept_request(&client_sock);
    }
    close(server_sock);

    return 0;
}