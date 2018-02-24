#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"

struct loginserv * fillstruct(char* category, char* name, char* password, struct loginserv *myloginserv)
{
  if (strcmp(category, "USER") == 0)
  {
    // cree spatch
    struct loginserv *mynewloginserv = malloc (sizeof (struct loginserv));
    myloginserv->next = mynewloginserv;
    mynewloginserv->next = NULL;
    struct login *spatch = malloc(sizeof(struct login));
    spatch->user = malloc(strlen(name));
    strcpy(spatch->user, name);
    spatch->password = malloc(strlen(password));
    strcpy(spatch->password, password);
    mynewloginserv->spatch = *spatch;
    return (mynewloginserv);
  }
  else if (strcmp(category, "SERV1") == 0)
  {
    struct login *serv1 = malloc(sizeof(struct login));
    if (strcmp(name, "null") == 0)
    {
      serv1->user = NULL;
      serv1->password = NULL;
    }
    else
    {
      serv1->user = malloc(strlen(name));
      strcpy(serv1->user, name);
    }
    if (serv1->user != NULL)
    {
      serv1->password = malloc(strlen(password));
      strcpy(serv1->password, password);
    }
    myloginserv->serv1 = *serv1;
  }
  else if (strcmp(category, "SERV2") == 0)
  {
    struct login *serv2 = malloc(sizeof(struct login));
    if (strcmp(name, "null\n") == 0)
    {
      serv2->user = NULL;
      serv2->password = NULL;
    }
    else
    {
      serv2->user = malloc(strlen(name));
      strcpy(serv2->user, name);
      serv2->password = malloc(strlen(password));
      strcpy(serv2->password, password);
      myloginserv->serv2 = *serv2;
    }
  }
   else if (strcmp(category, "SERV3") == 0)
  {
    struct login *serv3 = malloc(sizeof(struct login));
    if (strcmp(name, "null") == 0)
    {
      serv3->user = NULL;
      serv3->password = NULL;
    }
    else
    {
      serv3->user = malloc(strlen(name));
      strcpy(serv3->user, name);
    }
    if (serv3->user != NULL)
    {
      serv3->password = malloc(strlen(password));
      strcpy(serv3->password, password);
    }
    myloginserv->serv3 = *serv3;
  }
  return (myloginserv);
}

struct loginserv *parse_config() {
  char buffer[1024];
  FILE *fichier = NULL;
  struct loginserv *myloginserv = malloc (sizeof (struct loginserv));
  struct loginserv *HEAD = myloginserv;

      fichier = fopen("../config/userdatabase.conf", "r+");
      if (fichier != NULL)
        {
            char name[1024];
            char password[1024];
            char category[1024];
          while (fgets(buffer, 1024, fichier) != NULL)
          {
            int i = 0;
            int indice = 0;
            while (buffer[i] != '=')
            {
                category[indice] = buffer[i];
                i++;
                indice++;
            }
            category[indice] = '\0';
            i++;
            indice = 0;
            while (buffer[i] != ':')
            {
              name[indice] = buffer[i];
              i++;
              indice++;
            }
            name[indice] = '\0';
            indice = 0;
            i++;
            while (buffer[i] != '\n')
              {
                password[indice] = buffer[i];
                i++;
                indice++;
              }
              password[indice] = '\0';
              if (strcmp(name, "null") == 0)
                myloginserv = fillstruct(category, name, NULL, myloginserv);
              else  
                myloginserv = fillstruct(category, name, password, myloginserv);
          }
          fclose(fichier);
        }
      else
          printf("cannot open userdatabase.conf\n");
      return HEAD->next;
}
