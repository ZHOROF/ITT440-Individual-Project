#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h> //inet_addr
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>

int main(int argc, char*argv[])
{
        int socket_desc;

        struct sockaddr_in server;
        char message[100], server_reply[100];


        //Create socket
        socket_desc = socket(AF_INET,SOCK_STREAM,0);
        char response[30];
        if(socket_desc == -1)
        {
                printf("\n* Tidak dapat membuat soket");
        }

        server.sin_addr.s_addr = inet_addr("10.0.2.16");
        server.sin_family = AF_INET;
        server.sin_port = htons(8888);


        //connect to remote server

        if(connect(socket_desc,(struct sockaddr*)&server, sizeof(server))<0)
        {
                puts("\n* Ralat pada sambungan");
                return 1;
        }

        puts("\n# Bersambung");


        int num = 1;
                while(num == 1)
                {
			printf("\n# Tulis pesanan anda: ");
                        fgets(message, 2000, stdin);
                        send(socket_desc, message, 2000, 0);


                        //Receive a reply from the server
                        if(recv(socket_desc, server_reply, 2000, 0)<0)
                        {
                                puts("\n* Gagal terima pesanan balas");
                        }

                        printf("\n# Pesanan balas: %s ", server_reply);
                        recv(socket_desc, response, 29, 0);
                        printf("\n# Masa dari Server: %s", response);

                }

                return 0;
}

