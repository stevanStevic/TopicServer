/* 
    ********************************************************************
    Odsek:          Elektrotehnika i racunarstvo
    Departman:      Racunarstvo i automatika
    Katedra:        Racunarska tehnika i racunarske komunikacije (RT-RK)
    Predmet:        Osnovi Racunarskih Mreza 1
    Godina studija: Treca (III)
    Skolska godina: 2016/2017
    Semestar:       Zimski (V)

	Autori:			Marko Dragojevic, Stevan Stevic
    
    Ime fajla:      subscriber.c
    Opis:           Subscriber for topic based TCP/IP server
    ********************************************************************
*/

#include<stdio.h>      //printf
#include<stdlib.h>
#include<string.h>     //strlen
#include<sys/socket.h> //socket
#include<arpa/inet.h>  //inet_addr
#include<fcntl.h>     //for open
#include<unistd.h>    //for close
#include<ctype.h>
#include<unistd.h>

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT   27015

int ParseArguments(int argc, char** argv);

int main(int argc , char *argv[])
{
    int sock;
    struct sockaddr_in server;
    char *message;
	int messLen = 0;
	//int i = 0;
	//int iflag = 0;
	//int pflag = 0;
	char *iValue = NULL;
	char *pValue = NULL;
	int c;

	/*for(i < 0; i < argc; i++){
		printf("Argument %d: %s\n", i, argv[i]);
	} */

	opterr = 0;

	while((c = getopt(argc, argv, "i:p:")) != -1) {
		switch(c) {
			case 'i':
				iValue = optarg;
				optind--;
				break;
			case 'p':
				pValue = optarg;
				optind--;
				break;
		}
	}

	puts("IP Address You Entered: ");
	puts(iValue);
	fflush(stdout);
	puts("Desired Port: ");
	puts(pValue);
	fflush(stdout);




    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(DEFAULT_PORT);

    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }

    puts("Connected\n");
	
	while(1) {
		puts("Enter a message:");
		char *c = (char *)malloc(1);

		message = (char *)malloc(1);
		memset(message, '\0', 1);
		messLen = 0;

		while( read(0, c, 1) > 0) {
			if( *c == '\n') break;
			message = (char *)realloc(message, messLen + 1);
			messLen++;
			strcat(message, c);
		}
		
		//Send some data
		if( send(sock , message , strlen(message), 0) < 0)
		{
			puts("Send failed");
			return 1;
		}

		puts("Client message:");
		puts(message);

		free(message);
	}
    close(sock);

    return 0;
}

int ParseArguments(int argc, char** argv){


		return 0;
}
