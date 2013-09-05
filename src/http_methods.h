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

int DecideMethod (char * firstLine, int l);

void GET (int con, char * buffer, int n);
void POST (int con, char * buffer, int n);
void OPTIONS ();
