/*
CHAT APPLICATION IN C++
This is the Client Code.
=======================================================
*/

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include <netinet/tcp.h>

using namespace std;
void *RecieveMessage(void *oldArgs);

//static volatile int waitForServer = 0;

int main(int argc, char *argv[])
{
	int fd = 0;
	char buff[200];

	if(argc<2)
	{
		printf("Less no of arguments !!");
		return 0;
	}

	//Setup Buffer Array
	memset(buff, '0',sizeof(buff));

	//Create Socket
	fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd<0)
	{
		perror("Client Error: Socket not created succesfully");
		return 0;
	}
    int flag = 1;
    int result = setsockopt(fd,            /* socket affected */
                            IPPROTO_TCP,     /* set option at TCP level */
                            TCP_NODELAY,     /* name of option */
                            (char *) &flag,  /* the cast is historical cruft */
                            sizeof(int));

	//Structure to store details
	struct sockaddr_in server;
	memset(&server, '0', sizeof(server));

	//Initialize
	server.sin_family = AF_INET;
	//server.sin_port =  htons(atoi(argv[2]));
	server.sin_port =  htons(10011);

	int in = inet_pton(AF_INET, argv[1], &server.sin_addr);
	if(in<0)
	{
		perror("Client Error: IP not initialized succesfully");
		return 0;
	}

	//Connect to given server
	in = connect(fd, (struct sockaddr *)&server, sizeof(server));
	if(in<0)
	{
		perror("Client Error: Connection Failed.");
		return 0;
	}

    char name[50];
	do{
            printf("Enter your username: ");
            bzero(name,50);
    		//fgets(name,50,stdin);
    		cin.getline(name,50);
    		cin.clear();


    }while(strcmp(name,"") == 0);

     send(fd,name,strlen(name)+1,0);
     //printf("Name sent:%s",name);

	char numStr[10];
        int rBytes=recv(fd,numStr,9,0);
        printf("\nYou are assigned the Number : %.*s\n",rBytes, numStr);



    pthread_t tid;
    pthread_create(&tid, NULL, RecieveMessage, &fd);


	while(1)
	{
            printf("Please enter the message: ");
            fflush(stdout);
    		bzero(buff,200);
    		//fgets(buff,255,stdin);
    		cin.getline(buff,200-1);
    		cin.clear();

		/* Send message to the server */
            if( strcmp(buff,"")!=0)
            {
                in = send(fd,buff,strlen(buff),0);

                if(buff[0]=='.' && buff[1]=='/'){
                    int usec = 0.1*(1000000);
                    usleep(usec);
                }

            }
            else
            {
                continue;
            }

		    if (in < 0){
                perror("\nClient Error: Writing to Server");
		    	return 0;
		    }
	}
	close(fd);
	return 0;
}


void *RecieveMessage(void *oldArgs)
{

    int *ii =  (int*)oldArgs;
    int fd= *ii;

    char buff[200];
	bzero(buff,200-1);
	int in;
	//printf("Inside thread.\n");

        while( (in = recv(fd,buff,200-1,0)) > 0)
        {
            //in = recv(fd,buff,5,0);
            //int sizee=atoi(buff);
            //printf("\tSize:%d_\n", sizee);
            //in = recv(fd,buff,sizee,0);
            //in = recv(fd,buff,99,0);

            printf("\n%.*s", in, buff);
            fflush(stdout);
            bzero(buff,100);

            if (in < 0){
                perror("\nClient Error: Reading from Server");
                return 0;
		    }
        }

        pthread_exit(NULL);
}
