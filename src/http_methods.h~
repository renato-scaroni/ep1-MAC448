#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>

#define get 1 
#define post 2
#define options 3

#define OK 200
#define NF 404

struct Response {
	int method; /*segue padrao da funcao*/
	char * httpVer;
	int status;
	FILE * file;
	char * fileExt;
	char * filePath;
};

int DecideMethod (char * firstLine, int l);

void GET (int con, char * buffer, int n);
void POST (int con, char * buffer, int n);
void OPTIONS ();
