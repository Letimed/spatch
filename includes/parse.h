#ifndef PARSE_H
#define PARSE_H     

struct login { 
	char* user; 
	char* password; 
};

struct loginserv { 
	struct login spatch; 
    struct login serv1; 
	struct login serv2; 
	struct login serv3; 
	struct loginserv *next; 
};


struct allowed_user 
{ 
	struct login user; 
	struct allowed_user *next; 
};

struct serv 
{ 
	char* adresse; 
	int port; 
	struct allowed_user* listuser; 
};

struct loginserv *parse_config();
int parseFile(int number, struct serv *myServer);

#endif
