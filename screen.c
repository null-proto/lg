#include "screen.h"
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

struct termios *screen_init() {
  struct termios *default_terminal = malloc(sizeof(struct termios));

  tcgetattr(STDIN_FILENO, default_terminal);
  struct termios raw;

  // raw.c_lflag &= ~(ICANON | ECHO); // raw-ish
	//
	raw.c_lflag &= ~(ICANON);
  raw.c_cc[VMIN] = 1;
  raw.c_cc[VTIME] = 0;

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
  return default_terminal;
}

void screen_exit(struct termios *default_terminal) {
  tcsetattr(STDIN_FILENO, TCIFLUSH, default_terminal);
}
