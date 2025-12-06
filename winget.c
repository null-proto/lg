#include "winget.h"
#include <unistd.h>
#include <sys/ioctl.h>

void winget_display() {
  struct winsize term;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &term);
}

void winget_render(struct winsize* ws, struct border* b) {}
