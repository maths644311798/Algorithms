#pragma comment(lib, "ws2_32.lib")
#include <iostream>
#include <stdio.h>
#include <winsock2.h>
using namespace std;
WSADATA wsaData;
u_short backup_port[] = {135, 139,445,5040,  7680,49664,49665,49666,49667,49668,49669};
const char *des_addr = "10.40.16.98";

int try_to_connect(const char * addr ,int port)
{
    SOCKET s;
    SOCKADDR_IN ServerAddr;

    // Create a new socket to make a client connection.
    s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_port = htons(port);
    ServerAddr.sin_addr.s_addr = inet_addr(addr);

    int res = connect(s, (SOCKADDR *) &ServerAddr, sizeof(ServerAddr));
    closesocket(s);
    return res;//返回0是连接成功，否则是SOCKET_ERROR
}

int main()
{
    WSAStartup(MAKEWORD(2,2), &wsaData);
    FILE *F;
    F = fopen("inf.txt", "w+");
    for(auto &i: backup_port)
    {
        if(try_to_connect(des_addr, i)==0)
        {
            fprintf(F,"%u, ",i);
            printf("%u success\n", i);
        }
        else
        {
            printf("%u fail\n", i);
        }
    }
/*
    for(u_short i=36000; i<=37000; ++i)
    {
        printf("%u ",i);
        if(try_to_connect(des_addr, i)==0)
        {
            fprintf(F,"%u, ",i);
            printf("success\n");
        }
        else
        {
            printf("fail\n");
        }
    }
*/
    fclose(F);
    WSACleanup();
    return 0;
} 