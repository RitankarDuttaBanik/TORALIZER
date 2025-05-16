#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <toralizer.h>

// You must define these in "toralizer.h" or in this file if not already defined
#define PROXY "127.0.0.1"
#define PROXYPORT 9050
#define USERNAME "toralize"

typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;

struct proxy_request {
    int8 vn;
    int8 cd;
    int16 dstport;
    int32 dstip;
    unsigned char userid[8];
};
typedef struct proxy_request Req;

struct proxy_response {
    int8 vn;
    int8 cd;
    int16 dstport;
    int32 dstip;
};
typedef struct proxy_response Res;

#define reqsize sizeof(struct proxy_request)
#define ressize sizeof(struct proxy_response)

Req *request(const char *dstip, const int dstport) {
    Req *req = malloc(reqsize);
    if (!req) {
        perror("malloc");
        exit(1);
    }

    req->vn = 4;
    req->cd = 1;
    req->dstport = htons(dstport);
    req->dstip = inet_addr(dstip);
    memset(req->userid, 0, 8);
    strncpy((char*)req->userid, USERNAME, 8);

    return req;
}

int main(int argc, char *argv[]) {
    char *host;
    int port, s;
    struct sockaddr_in sock;
    Req *req;
    Res *res;
    char buf[ressize];
    int success;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <host> <port>\n", argv[0]);
        return -1;
    }

    host = argv[1];
    port = atoi(argv[2]);

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        perror("socket");
        return -1;
    }

    sock.sin_family = AF_INET;
    sock.sin_port = htons(PROXYPORT);
    sock.sin_addr.s_addr = inet_addr(PROXY);

    if (connect(s, (struct sockaddr *)&sock, sizeof(sock)) < 0) {
        perror("connect");
        close(s);
        return -1;
    }

    printf("CONNECTION ESTABLISHED TO PROXY\n");

    req = request(host, port);
    if (write(s, req, reqsize) < 0) {
        perror("write");
        free(req);
        close(s);
        return -1;
    }

    memset(buf, 0, ressize);
    if (read(s, buf, ressize) < 1) {
        perror("read");
        free(req);
        close(s);
        return -1;
    }

    res = (Res *)buf;
    success = (res->cd == 90);

    if (!success) {
        fprintf(stderr, "Unable to traverse the proxy, error code: %d\n", res->cd);
        close(s);
        free(req);
        return -1;
    }

    printf("Successfully connected through proxy to %s:%d\n", host, port);
    close(s);
    free(req);
    return 0;
}
