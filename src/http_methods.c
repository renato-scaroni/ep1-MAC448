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
				printf("get\n");
				method = 1;
			}
			else
				if(firstLine[i] == 'P')
				{
					printf("post\n");
					method = 2;
				}
			else
				if(firstLine[i] == 'O')
				{
					printf("options\n");
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

void GET ()
{
	printf("Tratando metodo POST\n");
	
}