#include "http_methods.h"

int DecideMethod (char * firstLine, int l)
{
	int method; /*1: GET; 2: POST, 3: OPTIONS*/
	int i = 0;
	char *p, *g, *o;

	p = "POST";
	g = "GET";
	o = "OPTIONS";

	while(firstLine[i] != ' ' && i < l)
	{
		if(i == 0)
		{
			if(firstLine[i] == 'G')
			{
				method = 1;
			}
			else
				if(firstLine[i] == 'P')
				{
					method = 2;
				}
			else
				if(firstLine[i] == 'O')
				{
					method = 3;
				}
			else
			{
				printf("Non-recognized method\n");				
				return -1;
			}
		}
		else
		{
			if(method == 1 && firstLine[i] != g[i])
			{
				printf("Non-recognized method\n");				
				return -1;				
			}
			if(method == 2 && firstLine[i] != p[i])
			{
				printf("Non-recognized method\n");				
				return -1;				
			}
			if(method == 3 && firstLine[i] != o[i])
			{
				printf("Non-recognized method\n");				
				return -1;				
			}
		}

		i++;
	}

	if (i > 7)
	{
		printf("Non-recognized method\n");				
		return -1;		
	}

	return method;
}

char * GetExt (char * file, int l)
{
	int i, j;
	char ext[16];

	for(i = l-1; i > 0 && file[i] != '.'; i--) ;

	if(i == 0)
		return NULL;

	for(j = 0; j < l - i - 1; j++)
	{
		ext[j] = file[i+j+1];
	}

	return ext;
}

void GET (int con, char * buffer, int n)
{
	int i;
	char * path/*, * ext*/;
	FILE * pFile;

	path = malloc(n*sizeof(char));

	printf("Tratando metodo GET\n");
	i = 4;

	path[0] = '.';

	while (buffer[i] != ' ' && i < n)
	{
		path[i-3] = buffer[i];
		i++;
	}

	printf("%s\n", path);
	pFile = fopen (path , "r");
	if (pFile == NULL) 
	{
		printf("%s\n", "Error opening file");
		write(con, "Page not found", 14);
	}
	else
	{
		printf("%s\n", "Trying to send stuff");
		buffer = malloc(128*sizeof(char));
		while ( ! feof (pFile) )
		{
			if ( fgets (buffer , 100 , pFile) == NULL ) break;
			fputs (buffer , stdout);
			write(con, buffer, strlen(buffer));
		}
		fclose (pFile);
	}

}