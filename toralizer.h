#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PROXY "127.0.0.1"
#define PROXYPORT 9050
#define USERNAME "toraliz"
#define reqsize sizeof(struct proxy_request)
#define ressize sizeof(struct proxy_response)

typedef unsigned char int8;      // 8 bits
typedef unsigned short int int16; // 16 bits
typedef unsigned int int32;       // 32 bits

/*
   +----+----+----+----+----+----+----+----+----+----+....+----+
   | VN | CD | DSTPORT |      DSTIP        | USERID       |NULL|
   +----+----+----+----+----+----+----+----+----+----+....+----+
   # of bytes:  1    1      2              4           variable       1
*/

struct proxy_request {
    int8 vn;
    int8 cd;
    int16 dstport;
    int32 dstip;
    unsigned char userid[8]; // fixed size: you might consider making this dynamically allocated if USERID is variable
};
typedef struct proxy_request Req;

/*
   +----+----+----+----+----+----+----+----+
   | VN | CD | DSTPORT |      DSTIP        |
   +----+----+----+----+----+----+----+----+
   # of bytes:  1    1      2              4
*/

struct proxy_response {
    int8 vn;
    int8 cd;
    int16 dstport;
    int32 dstip;
};
typedef struct proxy_response Res;

// Corrected function prototype
Req *request(const char*, const int);

int main(int argc, char **argv) {
    // Placeholder main function
    return 0;
}
