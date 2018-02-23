#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/parse.h"

int main()
{
	parseServ();
    return 0;
}


int parseServ()
{
	struct serv server1;
	struct serv server2;
	struct serv server3;

	parseFile(1, &server1);
	parseFile(2, &server2);
	parseFile(3, &server3);


	return 0;
}

int parseFile(int number, struct serv *myServer)
{
	FILE* fichier = NULL;

	if (number == 1)
	    fichier = fopen("../config/serv1.conf", "r+");
	else if (number == 2)
		fichier = fopen("../config/serv2.conf", "r+");
	else if (number == 3)
		fichier = fopen("../config/serv3.conf", "r+");
	else
	{
		printf("Error parsing config files");
		return 1;
	}


	if (fichier != NULL)
	{
		char line [1024];
     	while ( fgets ( line, sizeof line, fichier ) != NULL ) 
      	{
      	   fputs ( line, stdout );
      	   char delim = '=';
      	   char *name;
      	   name = malloc(1024 * sizeof(char));
      	   name = strtok(line, &delim);
      	   if (strcmp(name, "HOSTNAME") == 0)
      	   	{
      	   		name = strtok(NULL, &delim);
      	   		myServer->listuser = NULL;
      	   		myServer->adresse = malloc(sizeof name);
      	   		delim = '\n';
      	   		name = strtok(name, &delim);
      	   		strcpy(myServer->adresse, name);
      	   	}
      	   	else if (strcmp(name, "PORT") == 0)
      	   	{
      	   		name = strtok(NULL, &delim);
      	   		myServer->port = atoi(name);
      	   	}
      	   	else
      	   	{
      	   		struct allowed_user* firstuser = NULL;
      	   		if (myServer->listuser != NULL)
      	   		{	
      	   			firstuser = myServer->listuser;
      	   			while (myServer->listuser->next != NULL)
      	   				myServer->listuser->next = myServer->listuser->next;
      	   		}
      	   	   	delim = ':';
       	   		name = strtok(name, &delim);
      	   		if (name == NULL)
      	   		{
      	   			printf("ERROR\n");
      	   			return ;
      	   		}
      	   		myServer->listuser = malloc(1024);
      	   		myServer->listuser->next = NULL;
      	   		myServer->listuser->user.user = malloc(sizeof(name));
      	   		strcpy(myServer->listuser->user.user, name);
      	   		name = strtok(NULL, &delim);
      	   		delim='\n';
      	   		name = strtok(name, &delim);
      	   		myServer->listuser->user.password = malloc(sizeof(name));
      	   		strcpy(myServer->listuser->user.password, name);
      	   		if (firstuser != NULL)
      	   			myServer->listuser = firstuser;

      	   	}
      	}
		fclose(fichier);
	}
	else
	{
		printf("Impossible d'ouvrir le fichier");
	}

	return 0;
}