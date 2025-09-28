#include <security/pam_appl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "main.hpp"

struct pam_conv_data {
  const char *password;
};

int conv_auth(int num_msg, const struct pam_message **msg,
            struct pam_response **resp, void *appdata_ptr) {

  struct pam_response *aresp = (struct pam_response *) calloc(num_msg, sizeof(struct pam_response));
  struct pam_conv_data *data = (pam_conv_data *) appdata_ptr;

  for (int i = 0; i < num_msg; i++) {

    switch (msg[i]->msg_style) {
    case PAM_PROMPT_ECHO_OFF: // password prompt
      aresp[i].resp = strdup(data->password);
      aresp[i].resp_retcode = 0;
      break;
    case PAM_PROMPT_ECHO_ON: // normal input
    case PAM_ERROR_MSG:
    case PAM_TEXT_INFO:
      aresp[i].resp = NULL;
      aresp[i].resp_retcode = 0;
      break;
    }
  }

  *resp = aresp;
  return PAM_SUCCESS;
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(stderr, "Usage: %s <username> <password>\n", argv[0]);
    return 1;
  }

  const char *username = argv[1];
  const char *password = argv[2];
  pam_conv_data conv_p = { .password = password };

  struct pam_conv conv = { conv_auth , &conv_p};
  pam_handle_t *pamh = NULL;

  if (pam_start("login", username, &conv, &pamh) != PAM_SUCCESS)
    return 1;

  if (pam_authenticate(pamh, 0) != PAM_SUCCESS) {
    printf("Authentication failed\n");
    pam_end(pamh, PAM_AUTH_ERR);
    return 1;
  }

  printf("Authentication successful\n");

  pam_end(pamh, PAM_SUCCESS);
  return 0;
}
