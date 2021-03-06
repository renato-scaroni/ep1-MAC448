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
				method = get;
			}
			else
				if(firstLine[i] == 'P')
				{
					method = post;
				}
			else
				if(firstLine[i] == 'O')
				{
					method = options;
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

void GetExt (char * file, char * ext, int l)
{
	int i, j;


	printf("Getting file extension\n");
	for(i = l-1; i > 0 && file[i] != '.'; i--) ;

	if(i == 0)
	{
		printf("Getting file extension failed\n");
		return;
	}

	for(j = 0; j <= l - i + 1; j++)
	{
		ext[j] = file[i+j];
	}
	ext[j] = '\0';
	printf("Getting file extension succeded: %s\n", ext);
}

void SendFile (FILE * pFile, int con)
{
	char *buffer;
	int size;
	printf("%s\n", "Trying to send stuff");
	
	size = ftell(pFile);

	buffer = malloc(size*sizeof(char));

	while ( !feof (pFile) )
	{
		fread(buffer, 1, sizeof(buffer), pFile);
		write(con, buffer, sizeof(buffer));
		memset(buffer, 0,  sizeof(buffer));
	}

	free(buffer);
	fclose (pFile);
}

char * GetReturnStatusString(int status)
{
	switch (status){
		case OK: return " 200 OK";
				 break;
		case NF: return " 404 Not Found";
				 break;
	};

	return NULL;
}

char * GetContentTypeLine (char * ext)
{
	if(strcmp(ext, ".html") == 0 || strcmp(ext, ".htm") == 0)
	{
		return "Content-Type: text/html\n";
	}
	if(strcmp(ext, ".png") == 0)
	{
		return "Content-Type: image/png\n";
	}

	return "Content-Type: text/plain\n";
}

void SendResp (struct Response resp, int con)
{
	char lineBuffer [1024];
	time_t agora;
	struct tm tm;
	char tmp[1024];
	struct stat infos;
	int readInfos;

	/*Monta e envia primeira linha da response*/
	strcpy(lineBuffer, resp.httpVer);
	strcat(lineBuffer, GetReturnStatusString(resp.status));
	printf("%s\n", lineBuffer);
	write(con, lineBuffer, strlen(lineBuffer));

	/*Monte e envia header geral*/
	agora = time(0);
	tm = *gmtime(&agora);
	strftime(lineBuffer, 1024, "Date: %a, %d %b %Y %H:%M:%S %Z\r\n", &tm);
	strcat(lineBuffer, "Connection: close");
	printf("%s\n", lineBuffer);
	write(con, lineBuffer, strlen(lineBuffer));

	/*Response headers*/
	strcpy(lineBuffer, "Server: ");
	strcat(lineBuffer, "Melhor server do mundo\n");
	strcat(lineBuffer, "Accept-Ranges: bytes");
	printf("%s\n", lineBuffer);
	write(con, lineBuffer, strlen(lineBuffer));

	/*Entity header*/
	readInfos = stat(resp.filePath, &infos) == 0 ? 1 : 0;
	if (resp.method == get && resp.status == 200 && readInfos) 
	{
		strcpy(lineBuffer, GetContentTypeLine(resp.fileExt));
		/*Content-Length*/
		sprintf(tmp, "Content-Length: %d\r\n", (int) infos.st_size);
		strcat(lineBuffer, tmp);
		/*Last-Modified*/
		strftime(tmp, 1024, "Last-Modified: %a, %d %b %Y %H:%M:%S %Z\r\n", localtime( &infos.st_mtime));
		strcat(lineBuffer, tmp);
		printf("%s", lineBuffer);
		write(con, lineBuffer, strlen(lineBuffer));
	}

	/*Pula uma linha*/
	printf("\n");
	write(con, "\n", 1);

	if(resp.file != NULL)
	{
		SendFile(resp.file, con);	
	}

}

/*int i eh o primeiro caracter do buffer que recebe dados do cliente
	que contem um caracter que nao espaco depois do caminho do arquivo*/
char * GetHTTPVer (char * buffer, int n, int i)
{
	buffer = &buffer[i+1];
	buffer[8] = '\0';

	return buffer;
}

void GET (int con, char * buffer, int n)
{
	int i, status;
	char * path, ext[16];
	FILE * pFile;
	struct Response resp;

	path = malloc(n*sizeof(char));

	printf("Tratando metodo GET\n");
	i = 4;

	path[0] = '.';

	while (buffer[i] != ' ' && i < n)
	{
		path[i-3] = buffer[i];
		i++;
	}

	GetExt(path, ext, i-4);
	/*printf("%s\n", GetHTTPVer(buffer, n, i));*/
	status = 200;
	pFile = fopen (path , "r");
	if (pFile == NULL) 
	{
		printf("%s\n", "Error opening file");
		status = 404;
	}
	resp.method = get;
	resp.httpVer = GetHTTPVer(buffer, n, i);
	resp.status = status;
	resp.fileExt = ext;
	resp.file = pFile;
	resp.filePath = path;
	SendResp(resp, con);
}

void POST(int con, char * buffer, int n)
{
	int i;
	char * path;
	FILE * pFile;

	path = malloc(n*sizeof(char));

	printf("Tratando metodo POST\n");
	i = 5;

	path[0] = '.';

	while (buffer[i] != ' ' && i < n)
	{
		path[i-4] = buffer[i];
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

void OPTIONS(int con)
{
	char lineBuffer [1024];
	char tmp[1024];
	time_t now;
	struct tm tm;
	
	now = time(0);
	tm = *gmtime(&now);
	strftime(tmp, 1024, "Date: %a, %d %b %Y %H:%M:%S %Z\r\n", &tm);
	
	strcat(lineBuffer, "HTTP/1.1 200 OK\n");
	strcat(lineBuffer, tmp);
	strcat(lineBuffer, "Server: Melhor server do mundo\n");
	strcat(lineBuffer, "Content-Length: 0\n");
	strcat(lineBuffer, "Connection: close\n");
	
	write(con, lineBuffer, strlen(lineBuffer));
}
