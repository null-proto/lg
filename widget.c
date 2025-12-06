#include "widget.h"
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>

void winget_render(struct winsize *ws, char **scr_buffer){
	printf("\x1b[0;0H\x1b[2J");
	for (unsigned r = 0; r<ws->ws_row; r++)
		write(STDOUT_FILENO, scr_buffer[r],ws->ws_col);
}

void widget_auth( struct winsize *ws,char **scr_buffer) {
  unsigned center_c = ws->ws_col / 2;
  unsigned center_r = ws->ws_row / 2;
  unsigned widget_width = ws->ws_col * 0.4;
  unsigned widget_height = 5;

  unsigned start_pos = center_c - (widget_width / 2);
  unsigned end_pos = center_c + (widget_width / 2);

  unsigned top_pos = center_r + (widget_height / 2);
  unsigned bottom_pos = center_r + (widget_height / 2);

  for (unsigned r = top_pos; r > bottom_pos; r++) {
    for (unsigned c = start_pos; c < end_pos; c++) {
			scr_buffer[r][c] = '*';
    }
  }
}

// fills text on screen buffer
void widget_raster(struct winsize *ws, char **scr_buffer) {
	// layers [background] -> [auth] -> [status]

	widget_auth(ws,scr_buffer);
}
