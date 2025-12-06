#pragma once

#include <security/pam_appl.h>

struct pam_conv_data { const char *password; };

/// returns PAM_* enum
int pam_auth(char* user , char* passwd);
