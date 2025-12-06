#include "help.h"
#include "screen.h"
#include "widget.h"

#include <termios.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>

struct termios* default_terminal;

char** scr_buffer;

struct winsize* term;


void handle_resize(int sig) {
  ioctl(STDOUT_FILENO, TIOCGWINSZ, term);
  if (realloc(scr_buffer, (unsigned long)(term->ws_col * term->ws_row))) {
		// die
	}
}


int main(int argc, char **argv) {

	if (argc>1)
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

	struct sigaction sa = {0};
	sa.sa_handler = handle_resize;
	sigaction(SIGWINCH,&sa,NULL);

	term = malloc(sizeof(struct winsize));
	default_terminal = screen_init();
	// --
  ioctl(STDOUT_FILENO, TIOCGWINSZ, term);
  scr_buffer = (char**) malloc((size_t)(term->ws_col * term->ws_row));

	widget_raster(term, scr_buffer);
	winget_render(term,scr_buffer);

	int _ = system("sleep 2");
	screen_exit(default_terminal);
  return 0;
}
