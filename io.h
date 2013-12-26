#ifndef IO_H
#define IO_H


#include <termios.h>


void initialize_tty(struct termios* term_settings);

void kbhit_init();
int kbhit();


#endif // IO_H
