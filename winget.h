#pragma once
#include <sys/ioctl.h>

void winget_display();

struct border {
  char rt;
  char lt;
  char rb;
  char lb;
  char f;
};

void winget_render(struct winsize* ws, struct border* b);
