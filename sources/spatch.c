/* This is a sample implementation of a libssh based SSH proxy */
/*
Copyright 2003-2013 Aris Adamantiadis
                          
This file is part of the SSH Library

You are free to copy this file, modify it in any way, consider it being public
domain. This does not apply to the rest of the library though, but it is
allowed to cut-and-paste working code from this file to any license of
program.
The goal is to show the API in action. It's not a reference on how terminal
clients must be made or how a client should react.
*/


#include <libssh/libssh.h>
#include <libssh/server.h>
#include <libssh/callbacks.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
//#include "spatch.h"

#define USER "myuser"
#define PASSWORD "mypassword"

static int authenticated=0;
static int tries = 0;
static int error = 0;
static ssh_channel chan=NULL;
static char *username;

static int auth_password(ssh_session session, const char *user,
        const char *password, void *userdata){

    (void)userdata;

    printf("Authenticating user %s pwd %s\n",user, password);
    if(strcmp(user,USER) == 0 && strcmp(password, PASSWORD) == 0){
        authenticated = 1;
        printf("Authenticated\n");
	username = user;
        return SSH_AUTH_SUCCESS;
    }
    if (tries >= 3){
        printf("Too many authentication tries\n");
        ssh_disconnect(session);
        error = 1;
        return SSH_AUTH_DENIED;
    }
    tries++;
    return SSH_AUTH_DENIED;
}


static int pty_request(ssh_session session, ssh_channel channel, const char *term,
        int x,int y, int px, int py, void *userdata){
    (void) session;
    (void) channel;
    (void) term;
    (void) x;
    (void) y;
    (void) px;
    (void) py;
    (void) userdata;
    printf("Allocated terminal\n");
    return 0;
}

static int shell_request(ssh_session session, ssh_channel channel, void *userdata){
    (void)session;
    (void)channel;
    (void)userdata;
    printf("Allocated shell\n");
    return 0;
}
struct ssh_channel_callbacks_struct channel_cb = {
    .channel_pty_request_function = pty_request,
    .channel_shell_request_function = shell_request
};

static ssh_channel new_session_channel(ssh_session session, void *userdata){
    (void) session;
    (void) userdata;
    if(chan != NULL)
        return NULL;
    printf("Allocated session channel\n");
    chan = ssh_channel_new(session);
    ssh_callbacks_init(&channel_cb);
    ssh_set_channel_callbacks(chan, &channel_cb);
    return chan;
}



int main(int argc, char **argv){
    ssh_session session;
    ssh_bind sshbind;
    ssh_event mainloop;
    ssh_session client_session;

    struct ssh_server_callbacks_struct cb = {
        .userdata = NULL,
        .auth_password_function = auth_password,
        .channel_open_request_session_function = new_session_channel
    };

    char buf[2048];
    char host[128]="";
    char *ptr;
    int i,r, rc;

    sshbind=ssh_bind_new();
    session=ssh_new();

    ssh_bind_options_set(sshbind, SSH_BIND_OPTIONS_RSAKEY, "/etc/ssh/ssh_host_rsa_key");

    (void) argc;
    (void) argv;

    if(ssh_bind_listen(sshbind)<0){
        printf("Error listening to socket: %s\n",ssh_get_error(sshbind));
        return 1;
    }
    r=ssh_bind_accept(sshbind,session);
    if(r==SSH_ERROR){
        printf("error accepting a connection : %s\n",ssh_get_error(sshbind));
        return 1;
    }
    ssh_callbacks_init(&cb);
    ssh_set_server_callbacks(session, &cb);

    if (ssh_handle_key_exchange(session)) {
        printf("ssh_handle_key_exchange: %s\n", ssh_get_error(session));
        return 1;
    }
    ssh_set_auth_methods(session,SSH_AUTH_METHOD_PASSWORD);
    mainloop = ssh_event_new();
    ssh_event_add_session(mainloop, session);

    while (!(authenticated && chan != NULL)){
        if(error)
            break;
        r = ssh_event_dopoll(mainloop, -1);
        if (r == SSH_ERROR){
            printf("Error : %s\n",ssh_get_error(session));
            ssh_disconnect(session);
            return 1;
        }
    }
    if(error){
        printf("Error, exiting loop\n");
        return 1;
    } else
        printf("Authenticated and got a channel\n");
    snprintf(buf,sizeof(buf), "Hello %s, welcome to the Sample SSH proxy.\r\nPlease select your destination: ", username);
    ssh_channel_write(chan, buf, strlen(buf));
    do{
        i=ssh_channel_read(chan,buf, 2048, 0);
        if(i>0) {
            ssh_channel_write(chan, buf, i);
            if(strlen(host) + i < sizeof(host)){
                strncat(host, buf, i);
            }
            if (strchr(host, '\x0d')) {
                *strchr(host, '\x0d')='\0';
                ssh_channel_write(chan, "\n", 1);
                break;
            }
        } else {
            printf ("Error: %s\n", ssh_get_error(session) );
            return 1;
        }
    } while (i>0);
    snprintf(buf,sizeof(buf),"Trying to connect to \"%s\"\r\n", host);
    ssh_channel_write(chan, buf, strlen(buf));
    printf("%s",buf);

    client_session = ssh_new();

    /* ssh servers expect username without realm */
    ptr = strchr(username,'@');
    if(ptr)
        *ptr= '\0';
    ssh_options_set(client_session, SSH_OPTIONS_HOST, host);
    ssh_options_set(client_session, SSH_OPTIONS_USER, username);
    rc = ssh_connect(client_session);
    if (rc != SSH_OK){
        printf("Error connecting to %s: %s", host, ssh_get_error(client_session));
        return 1;
    }
    rc = ssh_userauth_none(client_session, NULL);
    if(rc == SSH_AUTH_SUCCESS){
        printf("Authenticated using method none\n");
    } else {
        rc = ssh_userauth_gssapi(client_session);
        if(rc != SSH_AUTH_SUCCESS){
            printf("GSSAPI Authentication failed: %s\n",ssh_get_error(client_session));
            return 1;
        }
    }
    snprintf(buf,sizeof(buf), "Authentication success\r\n");
    printf("%s",buf);
    ssh_channel_write(chan,buf,strlen(buf));
    ssh_disconnect(client_session);
    ssh_disconnect(session);
    ssh_bind_free(sshbind);
    ssh_finalize();
    return 0;
}
