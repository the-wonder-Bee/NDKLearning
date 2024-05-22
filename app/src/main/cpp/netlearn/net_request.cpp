//
// Created by 廖 on 2024/5/20.
//

#include <netdb.h>
#include <unistd.h>
#include "net_request.h"
#include "../log/android_log_util.h"
#include <string.h>
#include <cstdio>

#define MAXLINE 4096
#define MAXSIZE 4096*10

char* get_request(){
    char result[MAXSIZE];
    int socketfd;
    char receive_buffer[MAXLINE];
    char send_buffer[MAXLINE];
    struct addrinfo hits, *res;
    int nNetTimeout = 5000;
    memset(&hits, 0, sizeof(hits));
    hits.ai_family = AF_UNSPEC;
    hits.ai_socktype = SOCK_STREAM;
//    hits.ai_flags = AI_PASSIVE;
//    hits.ai_protocol = 0;

    int status = getaddrinfo("static.launcher.aisee.tv","http", &hits, &res);
    if (status != 0) {
        LOGE("netlearn", "getaddrinfo error %s",gai_strerror(status));
        return receive_buffer;
    }
    if ((socketfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1) {
        LOGE("netlearn", "error create socket");
        return receive_buffer;
    }

    // Connect to server
    if (connect(socketfd, res->ai_addr, res->ai_addrlen) == -1) {
        LOGE("netlearn", "error connect");
        return receive_buffer;
    }
    setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&nNetTimeout,sizeof(int));

    const char *http_get = "GET /epgol/snmott_lanxu_10401_v7_rootcolumn.json HTTP/1.1\r\nHost: %s\r\n\r\n";
    snprintf(send_buffer, sizeof(send_buffer), http_get, "static.launcher.aisee.tv");

    // 发送HTTP GET请求
    int bytes_sent = send(socketfd, send_buffer, strlen(send_buffer), 0);
    if (bytes_sent == -1) {
        LOGE("netlearn","send error");
        close(socketfd);
        freeaddrinfo(&hits);
        return receive_buffer;
    }

    LOGD("netlearn","%s", send_buffer);
    memset(&receive_buffer, 0, MAXLINE-1);
    int n = 0;
    int bytes_received = 0;
    do {
        n = recv(socketfd, receive_buffer, MAXLINE-1, 0);
        strcpy(result+strlen(result), receive_buffer);
        LOGE("netlearn","n == %d", n);
        LOGD("netlearn","%s", receive_buffer);
        memset(receive_buffer, 0, MAXLINE-1);
    }while (n > 0);

    LOGE("netlearn","n == %d", n);
    close(socketfd);
    return result;
}


