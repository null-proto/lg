
typedef struct pam_conv_data pam_conv_data;

int conv_auth(int num_msg, const struct pam_message **msg,
              struct pam_response **resp, void *appdata_ptr);
