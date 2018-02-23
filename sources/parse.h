typedef struct loginserv { 
	login spatch; 
	login serv1; 
	login serv2; 
	login serv3; 
	struct loginserv *next; 
} 

struct login { 
	char* user; 
	char* password; 
} 

struct allowed_user 
{ 
	struct login user; 
	struct allowed_user *next; 
} 

struct serv 
{ 
	char* adresse; 
	int port; 
	struct allowed_user* listuser; 
};

#endif