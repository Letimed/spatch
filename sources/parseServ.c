#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/parse.h"

int parseServ()
{
	struct serv server1;
	struct serv server2;
	struct serv server3;

	if (parseFile(1, &server1) != 0)
		return;
	if (parseFile(2, &server2) != 0)
		return;
	if (parseFile(3, &server3) != 0)
		return;

	/*printf("SERVER 1 //// \nHostname : %s \n", server1.adresse);
	printf("Port : %d \n", server1.port);
	printf("USER :\n");
	while (server1.listuser != NULL)
	{
		printf("AUser : %s Password : %s \n", server1.listuser->user.user , server1.listuser->user.password);
		server1.listuser = server1.listuser->next;
	}

	printf("SERVER 2 //// \nHostname : %s \n", server2.adresse);
	printf("Port : %d \n", server2.port);
	printf("USER :\n");
	while (server2.listuser != NULL)
	{
		printf("AUser : %s Password : %s \n", server2.listuser->user.user , server2.listuser->user.password);
		server2.listuser = server2.listuser->next;
	}

	printf("SERVER 3 //// \nHostname : %s \n", server3.adresse);
	printf("Port : %d \n", server3.port);
	printf("USER :\n");
	while (server3.listuser != NULL)
	{
		printf("AUser : %s Password : %s \n", server3.listuser->user.user , server3.listuser->user.password);
		server3.listuser = server3.listuser->next;
	}*/





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
		myServer->listuser = NULL;
     	while ( fgets ( line, sizeof line, fichier ) != NULL ) 
      	{
      	   char *delim = "=";
      	   char *name;
      	   name = strtok(line, delim);
      	   if (strcmp(name, "HOSTNAME") == 0)
      	   	{
      	   		name = strtok(NULL, delim);
      	   		myServer->adresse = malloc(sizeof name);
      	   		delim = "\n";
      	   		name = strtok(name, delim);
      	   		strcpy(myServer->adresse, name);
      	   	}
      	   	else if (strcmp(name, "PORT") == 0)
      	   	{
      	   		name = strtok(NULL, delim);
      	   		myServer->port = atoi(name);
      	   	}
      	   	else
      	   	{
      	   		struct allowed_user* firstuser = NULL;
      	   		struct allowed_user* prevuser = NULL;
      	   		if (myServer->listuser != NULL)
      	   		{	
      	   			firstuser = myServer->listuser;
      	   			prevuser = myServer->listuser;
      	   			while (myServer->listuser->next != NULL)
      	   			{
      	   				prevuser = myServer->listuser->next;
      	   				myServer->listuser = myServer->listuser->next;
      	   			}
      	   		}
      	   	   	delim = ":";
       	   		name = strtok(name, delim);
      	   		if (name == NULL)
      	   		{
      	   			printf("ERROR\n");
      	   			return 1;
      	   		}
      	   		myServer->listuser = malloc(1024 * sizeof(char));
      	   		myServer->listuser->next = NULL;
      	   		myServer->listuser->user.user = malloc(strlen(name) + 1);
      	   		strcpy(myServer->listuser->user.user, name);
      	   		name = strtok(NULL, delim);
      	   		if (name == NULL)
      	   		{
      	   			printf("Error parsing file \n");
      	   			return 1;
      	   		}
      	   		delim ="\n";
      	   		name = strtok(name, delim);
      	   		myServer->listuser->user.password = malloc(sizeof(name));
      	   		strcpy(myServer->listuser->user.password, name);
      	   		if (prevuser != NULL)
      	   		{
      	   			prevuser->next = myServer->listuser;
      	   		}
      	   		if (firstuser != NULL)
      	   			myServer->listuser = firstuser;
      	   	}
      	}
		fclose(fichier);
	}
	else
	{
		printf("Impossible d'ouvrir le fichier");
		return 1;
	}

	return 0;
}