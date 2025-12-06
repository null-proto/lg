#pragma once

#include <security/pam_appl.h>
// #include <pam_appl.h>

struct pam_conv_data { const char *password; };

int conv_auth(int num_msg, const struct pam_message **msg,
            struct pam_response **resp, void *appdata_ptr);

/// returns PAM_* enum
int pam_auth(char* user , char* passwd);
