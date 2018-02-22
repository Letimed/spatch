#include <libssh/libssh.h>
#include <libssh/server.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "parse_config.h"

static int is_pass_auth_msg(ssh_message message) {
  return ssh_message_type(message) == SSH_REQUEST_AUTH
    && ssh_message_subtype(message) == SSH_AUTH_METHOD_PASSWORD;
}

static int is_chan_open_msg(ssh_message message) {
  return ssh_message_type(message) == SSH_REQUEST_CHANNEL_OPEN
    && ssh_message_subtype(message) == SSH_CHANNEL_SESSION;
}

static int is_shell_request_msg(ssh_message message) {
  return ssh_message_type(message) == SSH_REQUEST_CHANNEL &&
    (ssh_message_subtype(message) == SSH_CHANNEL_REQUEST_SHELL
     || ssh_message_subtype(message) == SSH_CHANNEL_REQUEST_PTY);
}

static int is_channel_closed_or_eof(ssh_channel chan) {
  return ssh_channel_is_eof(chan) || ssh_channel_is_closed(chan);
}

static void connect_to_host(ssh_channel client_chan, char *hostname, int port) {
  const char *error_msg = NULL;
  ssh_session session = ssh_new();
  ssh_channel server_chan;
  char buffer[2048];
  // int rc;

  ssh_options_set(session, SSH_OPTIONS_HOST, "localhost");
  ssh_options_set(session, SSH_OPTIONS_PORT, &port);

  printf("connecting to %s:%i\n", hostname, port);
  if (ssh_connect(session) != SSH_OK)
    error_msg = "failed to connect to host\n";
  else if (ssh_userauth_password(session, "florian", "") != SSH_OK)
    error_msg = "authentication failed\n";
  else if ((server_chan = ssh_channel_new(session)) == NULL)
    error_msg = "failed to create channel\n";
  else if (ssh_channel_open_session(server_chan) != SSH_OK)
    error_msg = "failed to open remote shell session\n";
  else if (ssh_channel_request_pty(server_chan) != SSH_OK)
    error_msg = "pty request failed\n";
  else if (ssh_channel_request_shell(server_chan) != SSH_OK)
    error_msg = "failed to open remote shell";
  
  // ssh_channel_change_pty_size(server_chan, 116, 64);
  printf("done\n");
  //printf("openning shell\n");
  //interactive_shell_session(channel, session);

  if (error_msg)
    ssh_channel_write(client_chan, error_msg, strlen(error_msg));
  else {
    const char const *connect_msg = "connected to server\n";
    ssh_channel_write(client_chan, connect_msg, strlen(connect_msg));

    while (!is_channel_closed_or_eof(client_chan)
	   && !is_channel_closed_or_eof(server_chan)) {
      // TODO check write error
      int count;

      count = ssh_channel_read_timeout(client_chan, buffer, sizeof(buffer), 0, 10);
      ssh_channel_write(server_chan, buffer, count);
      count = ssh_channel_read_timeout(client_chan, buffer, sizeof(buffer), 1, 10);
      ssh_channel_write_stderr(server_chan, buffer, count);

      count = ssh_channel_read_timeout(server_chan, buffer, sizeof(buffer), 0, 10);
      ssh_channel_write(client_chan, buffer, count);
      count = ssh_channel_read_timeout(server_chan, buffer, sizeof(buffer), 1, 10);
      ssh_channel_write_stderr(client_chan, buffer, count);
      // printf("eof %i %i\n", ssh_channel_is_eof(client_chan), ssh_channel_is_eof(server_chan));
      // printf("closed %i %i\n", ssh_channel_is_closed(client_chan), ssh_channel_is_closed(server_chan));
    }
  }
  
  ssh_channel_close(server_chan);
  ssh_channel_free(server_chan);
  ssh_free(session);
}

static void select_host(ssh_channel chan) {
  // TODO loop/choose server
  char buf[2048];

  int i = ssh_channel_write(chan, "hello\n", strlen("hello\n"));
  //ssh_channel_read(chan, buf, 2048, 0);
  //ssh_channel_write(chan, buf, strlen(buf));

  //char *hostname = "localhost";
  printf("connect to host\n");
  connect_to_host(chan, "localhost", 4242);
}

static void handle_session(ssh_session session) {
  if (ssh_handle_key_exchange(session) != SSH_OK) {
    fprintf(stderr, "key echange failed\n");
    return;
  }

  ssh_channel chan;
  ssh_message message;
  int auth = 0;
  int shell = 0;
  const char *user;

  // authenticate user and open channel
  do {
    message = ssh_message_get(session);
    if (message == NULL)
      break;

    printf("message received\n"); // DEBUG
    if (is_pass_auth_msg(message)) {
      user = ssh_message_auth_user(message);
      const char *pass = ssh_message_auth_password(message);
      // TODO check user/password
      printf("user %s %s\n", user, pass);
      auth = 1;
      ssh_message_auth_reply_success(message, 0);
    }
    else if (is_chan_open_msg(message)) {
      chan = ssh_message_channel_request_open_reply_accept(message);
    }
    else if (is_shell_request_msg(message)) {
      shell = 1;
      ssh_message_channel_request_reply_success(message);
    }
    else {
      ssh_message_reply_default(message);
    }

    ssh_message_free(message);
  } while (!auth || !chan || !shell);

  if (!auth) {
    fprintf(stderr, "authentication failed\n");
    return;
  }
  if (!chan) {
    fprintf(stderr, "failed to open channel\n");
    return;
  }
  if (!shell) {
    fprintf(stderr, "channel type not supported\n");
    return;
  }

  printf("auth and chan ok\n");
  select_host(chan);

  ssh_channel_close(chan);
  ssh_channel_free(chan);
}

int main() {
  // parse_endpoints("../test/endpoints");
  ssh_bind bind;
  ssh_session session;
  
  bind = ssh_bind_new();

  ssh_bind_options_set(bind, SSH_BIND_OPTIONS_RSAKEY, "/etc/ssh/ssh_host_rsa_key");
  // set to non blocking to reload the configuration
  // ssh_bind_set_blocking(bind, 0);
  
  if (ssh_bind_listen(bind) < 0) {
    fprintf(stderr, "%s\n", ssh_get_error(bind));
    return 1;
  }

  // loop to accept new connections
  while (1) {
    session = ssh_new();
    ssh_set_auth_methods(session, SSH_AUTH_METHOD_PASSWORD);
    
    if (session == NULL) {
      fprintf(stderr, "failed to create new ssh session\n");
      return 1;
    }

    if (ssh_bind_accept(bind, session) != SSH_ERROR) {
      int pid = fork();

      if (pid == 0) {
	handle_session(session);
	ssh_disconnect(session);
	printf("client disconnected\n");
	ssh_free(session);
	break;
      }
      else if (pid > 0) {
	printf("fork ok\n");
      } else {
	fprintf(stderr, "fork error\n");
      }
    } else {
      fprintf(stderr, "accept failed : %s\n", ssh_get_error(bind));
      return 1;
    }

    ssh_free(session);
  }
  
  ssh_bind_free(bind);
  return 0;
}
