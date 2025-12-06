#include "help.h"
#include "screen.h"
#include "termios.h"
#include <stdlib.h>
#include <string.h>


int main(int argc, char **argv) {

  for (++argv; *argv; argv++) {
    if ((*argv)[0] == '-' && (*argv)[1] == '-') {

      if (strncmp(*argv, "--help", 6) == 0) {
        help_msg();
        return 0;
      } else {
        help_name_wargs(*argv);
      }

    } else if ((*argv)[0] == '-' && (*argv)[1] != '\0') {
      switch ((*argv)[1]) {
      case 'h': {
        help_msg();
        return 0;
      }
      default:
        help_name_wargs(*argv);
        return 1;
      }

    } else {
      help_name_wargs(*argv);
    }
  }

	struct termios* default_terminal = screen_init();


	screen_exit(default_terminal);
	free(default_terminal);
  return 0;
}
