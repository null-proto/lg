#include "help.h"
#include "screen.h"
#include "widget.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

struct termios *default_terminal;

char **scr_buffer;

struct winsize *term;

void handle_resize(int sig) {
  ioctl(STDOUT_FILENO, TIOCGWINSZ, term);
  if (realloc(scr_buffer, (unsigned long)(term->ws_col * term->ws_row))) {
    // die
  }
}

int main(int argc, char **argv, char **env) {

  struct {
    unsigned allow_all_terminal : 1;
  } flags = {0};

  if (argc > 1)
    for (++argv; *argv; argv++) {
      if ((*argv)[0] == '-' && (*argv)[1] == '-') {

        if (strncmp(*argv, "--help", 6) == 0) {
          help_msg();
          return 0;
        } else if (strncmp(*argv, "--allow-term", 6) == 0) {
          flags.allow_all_terminal = 1;
        } else {
          help_name_wargs(*argv);
        }

      } else if ((*argv)[0] == '-' && (*argv)[1] != '\0') {
        switch ((*argv)[1]) {
        case 'h': {
          help_msg();
          return 0;
        }
        case 'a': {
          flags.allow_all_terminal = 1;
          break;
        }
        default:
          help_name_wargs(*argv);
          return 1;
        }

      } else {
        help_name_wargs(*argv);
      }
    }

  if (!flags.allow_all_terminal && strncmp(getenv("TERM"), "linux", 5)) {
    printf("Unsupported terminal: expected tty [linux]\n");
    return 1;
  }

  term = malloc(sizeof(struct winsize));
  ioctl(STDOUT_FILENO, TIOCGWINSZ, term);

  struct sigaction sa = {0};
  sa.sa_handler = handle_resize;
  sigaction(SIGWINCH, &sa, NULL);

  default_terminal = screen_init();
  // --
  scr_buffer = (char **)malloc((size_t)(term->ws_col * term->ws_row));

  widget_raster(term, scr_buffer);
  winget_render(term, scr_buffer);

  *scr_buffer = "example ";

  int _ = system("sleep 2");
  screen_exit(default_terminal);
  return 0;
}
