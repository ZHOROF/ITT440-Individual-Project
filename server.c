#include <stdio.h>
#include <string.h>     //strlen
#include <sys/socket.h>
#include <arpa/inet.h>  //inet_addr
#include <unistd.h>     //write
#include <netinet/in.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
        int socket_desc, new_socket, c;
        struct sockaddr_in server, client;
        char message[2000], client_reply[2000];
        int optval;
        socklen_t optlen = sizeof(optval);

        //Create socket
        socket_desc = socket(AF_INET, SOCK_STREAM, 0);
        if(socket_desc == -1)
        {
                printf("\n* Tidak dapat membuat soket");
        }


        //Prepare the sockaddr_in structure
	int n_client = 0;
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in serverAddress;
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_port = htons(8888);

        //Bind
        if(bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
        {
                puts("\n* gagal mengikat");
                return 1;
        }

        puts("\n# selesai mengikat");

        //Listen
        listen(socket_desc, 3);


        //Accept and incoming connection
        puts("\n# Menunggu sambungan masuk...");
        c = sizeof(struct sockaddr_in);


        while(1)
        {
               new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);

                puts("\n# Sambungan diterima");


                //printf("Waiting for message from client..\n");

                recv(new_socket, client_reply, 2000, 0);
                printf("\n# Pesanan daripada Client: %s",client_reply);


                printf("\n# Balas pesanan: ");
                fgets(message, 2000, stdin);
                send(new_socket, message, 2000, 0);


		/*int client_socket = accept(sockfd, NULL, NULL);*/
		n_client++;
		time_t currentTime;
		time(&currentTime);
		printf("\n# Client %d meminta masa pada %s ",n_client, ctime(&currentTime));
		send(new_socket, ctime(&currentTime), 30, 0);

        }


	if(new_socket < 0)
        {
                perror("\n* Gagal terima");
                return 1;
        }

        return 0;

}
