#pragma once

#include <sys/ioctl.h>


struct border {
  char rt;
  char lt;
  char rb;
  char lb;
  char f;
};

void widget_raster(struct winsize *ws, char **scr_buffer);

void widget_auth( struct winsize *ws,char **scr_buffer);

void winget_render(struct winsize *ws, char **scr_buffer);
