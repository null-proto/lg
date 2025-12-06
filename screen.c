#include <termios.h>
#include <unistd.h>

struct termios scr;

void screen_init() { tcsetattr(STDIN_FILENO, TCIFLUSH, &scr); }

void screen_exit() {
  tcgetattr(STDIN_FILENO, &scr);
  struct termios raw = scr;

  raw.c_lflag &= ~(ICANON | ECHO); // raw-ish
  raw.c_cc[VMIN] = 1;
  raw.c_cc[VTIME] = 0;

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
