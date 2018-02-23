#include <libssh/libssh.h>
#include <libssh/server.h>
#include <libssh/callbacks.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "parse_config.h"

#define PRINT_STATUS_DELAY 15

static int is_pass_auth_msg(ssh_message message) {
  return ssh_message_type(message) == SSH_REQUEST_AUTH
    && ssh_message_subtype(message) == SSH_AUTH_METHOD_PASSWORD;
}

static int is_chan_open_msg(ssh_message message) {
  return ssh_message_type(message) == SSH_REQUEST_CHANNEL_OPEN
    && ssh_message_subtype(message) == SSH_CHANNEL_SESSION;
}

static int is_shell_request_msg(ssh_message message) {
  return ssh_message_type(message) == SSH_REQUEST_CHANNEL
    && (ssh_message_subtype(message) == SSH_CHANNEL_REQUEST_SHELL
     || ssh_message_subtype(message) == SSH_CHANNEL_REQUEST_PTY);
}

static int is_channel_closed_or_eof(ssh_channel chan) {
  return ssh_channel_is_eof(chan) || ssh_channel_is_closed(chan);
}

static int terminal_resize_callback(ssh_session session, ssh_channel channel,
				    int width, int height,
				    int pxwidth, int pxheight,
				    void *userdata) {
  printf("request resize %i %i %i %i\n", width, height, pxwidth, pxheight);
  return -1;
  // return 0; // accept resize
}

static int pty_request_callback(ssh_session session, ssh_channel channel,
				const char *term, int width, int height,
				int pxwidth, int pwheight, void *userdata) {
  printf("pty_request_callback");
}

static void channel_signal_callback(ssh_session session, ssh_channel channel,
				    char const *sig, void *userdata) {
  printf("signal : %s\n", sig);
}

static int channel_data(ssh_session session, ssh_channel channel, void *data,
			 uint32_t len, int is_stderr, void *userdata) {
  printf("channel_data\n");
}

static int packet_rcv_callback(ssh_session session, uint8_t type, ssh_buffer packet, void *user) {
  printf("packet rcv");
}

static void connect_channels(ssh_channel chan1, ssh_channel chan2, int timeout_ms) {
  char buffer[2048];
  int count;

  count = ssh_channel_read_timeout(chan1, buffer, sizeof(buffer), 0, timeout_ms);
  ssh_channel_write(chan2, buffer, count);
  count = ssh_channel_read_timeout(chan1, buffer, sizeof(buffer), 1, timeout_ms);
  ssh_channel_write_stderr(chan2, buffer, count);

  count = ssh_channel_read_timeout(chan2, buffer, sizeof(buffer), 0, timeout_ms);
  ssh_channel_write(chan1, buffer, count);
  count = ssh_channel_read_timeout(chan2, buffer, sizeof(buffer), 1, timeout_ms);
  ssh_channel_write_stderr(chan1, buffer, count);
}

static void connect_to_host(ssh_channel client_chan, const char *user,
			    const char *hostname, int port) {
  const char *error_msg   = NULL;
  ssh_session session     = ssh_new();
  ssh_channel server_chan = NULL;

  ssh_options_set(session, SSH_OPTIONS_HOST, "localhost");
  ssh_options_set(session, SSH_OPTIONS_PORT, &port);

  printf("%s is openning connection to %s:%i\n", user, hostname, port);
  if (ssh_connect(session) != SSH_OK)
    error_msg = "failed to connect to host\r\n";
  else if (ssh_userauth_password(session, "florian", "") != SSH_OK)
    error_msg = "authentication failed\r\n";
  else if ((server_chan = ssh_channel_new(session)) == NULL)
    error_msg = "failed to create channel\r\n";
  else if (ssh_channel_open_session(server_chan) != SSH_OK)
    error_msg = "failed to open remote shell session\r\n";
  else if (ssh_channel_request_pty(server_chan) != SSH_OK)
    error_msg = "pty request failed\r\n";
  else if (ssh_channel_request_shell(server_chan) != SSH_OK)
    error_msg = "failed to open remote shell\r\n";

  // ssh_set_log_level(SSH_LOG_FUNCTIONS); // DEBUG LOG
  struct ssh_channel_callbacks_struct cb = {
    .userdata = NULL,
    // .channel_data_function = channel_data,
    .channel_signal_function = channel_signal_callback,
    .channel_pty_request_function = pty_request_callback,
    .channel_pty_window_change_function = terminal_resize_callback
  };
  ssh_callbacks_init(&cb);
  ssh_set_channel_callbacks(client_chan, &cb);

  ssh_event callback_poll = ssh_event_new();
  ssh_event_add_session(callback_poll, ssh_channel_get_session(client_chan));
  
  time_t print_status_time = time(NULL);

  if (error_msg)
    ssh_channel_write(client_chan, error_msg, strlen(error_msg));
  else {
    ssh_channel_change_pty_size(server_chan, 116, 64);  

    while (!is_channel_closed_or_eof(client_chan)
	   && !is_channel_closed_or_eof(server_chan)) {

      connect_channels(client_chan, server_chan, 10);
      if (time(NULL) >= print_status_time) {
	printf("%s is connected to shell on %s\n", user, hostname);
	print_status_time = time(NULL) + PRINT_STATUS_DELAY;
      }

      ssh_event_dopoll(callback_poll, 10);
    }
  }

  printf("%s is disconnected from %s\n", user, hostname);
  ssh_channel_free(server_chan);
  ssh_free(session);
}

static void channel_get_line(ssh_channel chan, char *buffer, int bufflen) {
  bzero(buffer, bufflen);
  int pos = 0;
  char c;

  while (1) {
    if (ssh_channel_read(chan, &c, 1, 0) != 1)
      break;
    if (c > 31)
      buffer[pos] = c;
    ssh_channel_write(chan, &c, 1);
    if (c == 127) {
      ssh_channel_write(chan, "\r", 1);
      for (int i = 0; i < pos; i++)
	ssh_channel_write(chan, " ", 1);
      if (pos > 0) {
	buffer[pos - 1] = 0;
	pos--;
      }
      ssh_channel_write(chan, "\r", 1);
      ssh_channel_write(chan, buffer, strlen(buffer));
    }
    else if (c == '\r') {
      ssh_channel_write(chan, "\r\n", 2);
      return;
    }
    else if (pos < bufflen-1)
      pos++;
  }
}

static void select_host(ssh_channel chan, const char *user) {
  const char *welcome_msg = "welcome to spatch\r\n";
  const char *select_msg  = "select an endpoint\r\n";
  char        buffer[1024];
  time_t      print_status_time = time(NULL);

  ssh_channel_write(chan, welcome_msg, strlen(welcome_msg));
  do {
    if (time(NULL) >= print_status_time) {
      printf("%s is connected to spatch\n", user);
      print_status_time = time(NULL) + PRINT_STATUS_DELAY;
    }

    ssh_channel_write(chan, select_msg, strlen(select_msg));
    channel_get_line(chan, buffer, sizeof(buffer));
    if (!strcmp(buffer, "localhost")) {
      connect_to_host(chan, user, "localhost", 4242); // check server
      break;
    }
  } while (strcmp(buffer, "exit") && !is_channel_closed_or_eof(chan));

  printf("%s disconnected\n", user);
}

static void handle_session(ssh_session session) {
  if (ssh_handle_key_exchange(session) != SSH_OK) {
    fprintf(stderr, "key echange failed\n");
    return;
  }

  ssh_channel chan    = NULL;
  ssh_message message = NULL;
  int         auth    = 0;
  int         shell   = 0;
  char        user[64];

  // authenticate user and open channel
  do {
    message = ssh_message_get(session);
    //if (message == NULL)
    //  break;

    if (is_pass_auth_msg(message)) {
      const char *user_tmp = strdup(ssh_message_auth_user(message));
      const char *pass     = ssh_message_auth_password(message);
      strncpy(user, user_tmp, sizeof(user));
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

  select_host(chan, user);

  ssh_channel_close(chan);
  ssh_channel_free(chan);
}

int main() {
  // parse_endpoints("../test/endpoints");
  ssh_bind    bind;
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
    // ssh_set_auth_methods(session, SSH_AUTH_METHOD_PASSWORD);
    
    if (session == NULL) {
      fprintf(stderr, "failed to create new ssh session\n");
      return 1;
    }

    if (ssh_bind_accept(bind, session) != SSH_ERROR) {
      int pid = fork();

      if (pid == 0) {
	handle_session(session);
	ssh_disconnect(session);
	ssh_free(session);
	break;
      }
      else if (pid < 1)
	fprintf(stderr, "fork error\n");
    }
    else {
      fprintf(stderr, "accept failed : %s\n", ssh_get_error(bind));
      return 1;
    }

    ssh_free(session);
  }
  
  ssh_bind_free(bind);
  return 0;
}
