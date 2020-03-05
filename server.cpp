/*
CHAT APPLICATION IN C++
This is the Server Code.
=======================================================
*/
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <pthread.h>
#include <malloc.h>

#include <netinet/tcp.h>
#include "queue.h"

#define serverLimit 100
int in[serverLimit];
int connList[serverLimit],connCounter=0;
char *connNames[serverLimit];


class user
{
public:
    #define limit 10
    int id;
    char *name;
    int activeConn;
    int allConn[limit],counter;
    char * allNames[limit];

    char sendd[200];
    struct Queue *recvQ;

public:
    user(){
        name="";    activeConn=-1;  counter=0;
        recvQ = createQueue();
    }
    user(char *username){
        name = (char*) malloc (sizeof(char) * strlen(username));
        strcpy(name, username);

        activeConn = -1;        counter=0;
    }

    void setName(char *username)
    {
        name = (char*) malloc (sizeof(char) * strlen(username));
        strcpy(name, username);
        strcpy(connNames[id],username);

        bzero(sendd,200);
        sprintf(sendd,"Name Changed to - %s\n", name);
    }

    void myID()
    {
        bzero(sendd,200);
        sprintf(sendd, "Your ID = %d\n",connList[id]);
    }

    int addConn(int conn)
    {
        bzero(sendd,200);

        for(int i=0; i<counter; i++)
        {
            if(conn == connList[allConn[i]] || conn==connList[id])
            {
                sprintf(sendd,"Invalid ID\n");
                return -1;

            }
        }

        if(counter <limit){

            for(int i=0;i<connCounter;i++)
            {
                if(conn == connList[i])
                {
                    allNames[counter] = (char*) malloc ( sizeof(char)* strlen(connNames[i]));
                    strcpy( allNames[counter] , connNames[i] );
                    allConn[counter]= connList[i];
                    sprintf(sendd,"Added:%d\n", allConn[counter]);

                    counter++;
                    int otherGuy = i;
                    return otherGuy;
                    //break;
                }
                else
                {
                    sprintf(sendd,"Invalid ID\n");
                    //send(id,sendd,strlen(sendd)+1,0);
                }
            }
        }
        else
        {
            sprintf(sendd,"Cant Add more people.\n");
        }

    }
    void removeConn(int conn)
    {
        bzero(sendd,200);
        if( conn<counter)
        {
            if(conn == activeConn){
                activeConn = -1;
            }
            for(int i=conn;i<counter-1;i++)
            {
                allConn[i] = allConn[i+1];
            }
            counter--;
            sprintf(sendd,"Successfully Removed Connection\n");
        }
        else
        {
            sprintf(sendd,"No such connection made.\n");
        }
    }

    void showAvailableConn()
    {
        bzero(sendd,200);
        for(int i=0;i<counter;i++)
        {
            if(activeConn == allConn[i]){
                sprintf(sendd,"%s%d : %s --- ACTIVE CONNECTION\n" ,sendd, i, allNames[i]);
            }
            else{
                sprintf(sendd,"%s%d : %s\n" ,sendd, i, allNames[i]);
            }
        }

        if(strcmp(sendd,"")==0)
        {
            strcpy(sendd,"List is Empty\n");
        }
        //sprintf(sendd,"%s\n",sendd);
    }

    void setActiveConn(int conn)
    {
        if(conn >=0 && conn < counter )
        {
            activeConn = allConn[conn];
            sprintf(sendd,"Active = %d\n", activeConn);
        }
        else
        {
            sprintf(sendd,"Enter a valid number upto %d\n", counter-1);
        }
    }

    void help()
    {
        bzero(sendd,200);
        strcpy(sendd,"COMMANDS:\n./list \t./add \t./remove \t./active \t./name \t./myID \nUSAGE:\n./list\n./add uniqueID\n./remove IDfromList\n./active IDtoSendMessagesTo\n./name NewName\n./myID\n");
    }

};


user u[serverLimit];

void *User(void* oldArgs);
void *SendTower (void *oldArgs);
void *SendMessage(void *oldArgs);

int main()
{
	int fd = 0;

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
	server.sin_port = htons(10011);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(fd, (struct sockaddr*)&server, sizeof(server));

	listen(fd, serverLimit);

	//*******************************************************
    pthread_t threads[serverLimit];
    int i=0,id[serverLimit];


	while(	in[i] = accept(fd, (struct sockaddr*)NULL, NULL))
	{
		id[i]=i;
        	pthread_create(&threads[i], NULL, User, &id[i]);
		i++;
	}

	for(int i=0;i<connCounter;i++)
	{
		pthread_join( threads[i],NULL);
	}

}

void initializeConn(int x)
{
/* RECIEVE USER NAME FROM CLIENT   */
    connNames[x]= (char*) malloc (sizeof(char)*50);     // Assign Memory
    recv(in[x], connNames[x], 49,0);                    // Receive User-name from Client
    u[x].setName(connNames[x]);                         // Store in "User" Structure
	//printf("Recieved : %s", connNames[x] );


/* GENERATE A UNIQUE NUMBER OF 6 DIGITS  */
    srand(time(NULL));
    connList[x] = -1;
    while(connList[x] == -1)
    {
        int temp= rand() % 100000+10000;
        if(x==0)
        {
            connList[x] = temp;
            break;
        }

        for(int i=0; i<connCounter; i++)
        {
            if(connList[i] == temp)
            {
                break;
            }
            if(i == connCounter-1) // every value checked
            {
                    connList[connCounter] = temp;
            }
        }
    }

/* SEND THE UNIQUE ID TO CLIENT  */
    char buff[10];
        bzero(buff,10);
        sprintf(buff,"%d", connList[connCounter]);
        send(in[x], buff, strlen(buff)+1, 0);
        //printf("\nBuff is: %s",buff);


/* INCREASE NUMBER OF CONNECTIONS COUNTER */
    connCounter++;

}
void *User(void* oldArgs)
{
    printf ("\nOne Client Connected !!");
/* STORE ID in - "user" structure AND id(FOR EASY ACCESS)  */
    int id =  *( (int*)oldArgs );
    u[id].id = id;                      // User stores its ID


/* Start a Central Function for SENDING Messages to client */
    pthread_t SendTowerTID;
    char iStr[10];
    sprintf(iStr,"%d",id);
    char *sendArgs[]={iStr,NULL};
    pthread_create(&SendTowerTID, NULL, SendTower, (void*)sendArgs);

/* INITIALIZE REQUIRED ATTRIBUTRES FOR CONNECTION - USERNAME and ASSIGN UNIQUE ID to user */
    initializeConn(id);

/* START RECIEVING MESSAGES FROM USER(CLIENT)  */
    char buff[201]="";                  // Used to store - Client Message Recieved
    int n;
    while ( (n = recv(in[id], buff, 200,0)) > 0)
    {
    /*DIVIDE THE RECEIVED CLIENT (MESSAGE) INTO (WORDS)  */
        //printf("Buff before:%s\n",buff);
        char * temp,*args[10],*buffnew;
            buffnew= new char[strlen(buff)];
            strcpy(buffnew,buff);

        int c=0;
        temp = strtok (buffnew," ");
        while (temp != NULL)
        {
            //printf ("%s\n",temp);
            args[c]= new char[ strlen(temp)];
            strcpy(args[c] , temp);
            //printf("args[%d] = %s\n", c,args[c]);
            c++;
            if(c>=10)
            {
                break;
            }
            temp = strtok (NULL, " ");

        }
        //printf("Buffnew after:%s\n",buffnew);


    /* ANALYZE THE FIRST WORD TO SEE IF ITS A - COMMAND OR NOT  */
        int cmd=0;

        if (strcmp(args[0],"./help")==0)
        {
            u[id].help();
            //printf("Send=%s\n",u[i].sendd);
            cmd=1;
        }
        else if(strcmp(args[0],"./list")==0)
        {
            u[id].showAvailableConn();
            cmd=1;
        }
        else if (strcmp(args[0],"./add")==0)
        {
            int otherGuy = u[id].addConn(atoi(args[1]));
            /*Also add ur ID in the other User Structure */
            u[otherGuy].addConn( connList[id]);
            cmd=1;
        }
        else if (strcmp(args[0],"./remove")==0)
        {
            u[id].removeConn(atoi(args[1]));
            //printf("Send=%s\n",u[i].sendd);
            cmd=1;
        }
        else if (strcmp(args[0],"./active")==0)
        {
            u[id].setActiveConn(atoi(args[1]));
            //printf("Active:%d\n",u[i].activeConn);
            cmd=1;
        }
        else if (strcmp(args[0],"./name")==0)
        {
            u[id].setName(args[1]);
            cmd=1;
        }
        else if (strcmp(args[0],"./myID")==0)
        {
            u[id].myID();
            cmd=1;
        }

        if(cmd == 1 )
        {
            /* IF THE MESSAGE WAS COMMAND - "SENDD" BUFFER WILL BE SENT WHICH CONTAINS RESPONSE OF COMMAND */
            if(strcmp(u[id].sendd,"")!=0 )
            {
                sprintf(buff, "-----SERVER-----\n%s-----/SERVER-----\n\n", u[id].sendd);
                enQueue(u[id].recvQ , in[id], buff );
                //send(in[id], buff, strlen(buff)+1, 0);
            }
            bzero(u[id].sendd,200);
        }
        else
        {
            /* IF THE MESSAGE WAS NOT COMMAND - SEND THE MESSAGE TO AN ACTIVE CONNECTION */
            pthread_t tid;
            char iStr[10];
            char threadBuff[200];
                bzero(threadBuff,200);
                sprintf(iStr,"%d",id);
                strcpy(threadBuff,buff);

            char *args[]={iStr, threadBuff,NULL};
            pthread_create(&tid, NULL, SendMessage, (void*)args);

        }
        strcpy(buff, "");
        bzero(buff, 200);

    }
    printf("\nClosed");
    close(in[id]);

   pthread_exit(NULL);
}


void *SendTower (void *oldArgs)
{
    char **args;
    args= (char**) oldArgs;
        int id= atoi(args[0]) ;
        char *buff= args[1];

    struct QNode *target;
    while(1)
    {
        target = deQueue(u[id].recvQ);
        if( target==NULL ){
            continue;
        }
        else
        {
            send(target->id, target->buff, strlen(target->buff)+1, 0);
        }
    }

}
void *SendMessage(void *oldArgs)
{
    char **args;
    args=  (char**)oldArgs;
        int id= atoi( args[0] );
        char *buff = args[1];


            if(u[id].activeConn != -1)
            {
                for(int k=0;k<connCounter;k++)
                {
                    if(connList[k] == u[id].activeConn)
                    {
                        char sendbuff[200];
                        sprintf(sendbuff, "%s:%s\n", connNames[id] , buff );

                        enQueue( u[k].recvQ, in[k], sendbuff);
                        //int len=0;
                        //len=send(in[k], sendbuff, strlen(sendbuff)+1, 0);
                        //printf("Sent=%s\n",sendbuff);
                    }
                }
            }


        pthread_exit(NULL);
}
