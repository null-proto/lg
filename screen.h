#pragma once

struct termios* screen_init();

void screen_exit(struct termios* default_terminal);
