#include "io.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <unistd.h>

#include "utils.h"


struct timeval tv;


void kbhit_init()
{
    tv.tv_sec = 0;
    tv.tv_usec = 0;
}


int kbhit()
{
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds); //STDIN_FILENO is 0
    select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &fds);
}


void initialize_tty(struct termios* term_settings)
{
    if (!isatty(STDOUT_FILENO)) {
        fputs("Output is not a tty. Dying.\n", stderr);
        die();
    };

    tcgetattr(STDOUT_FILENO, term_settings);

    term_settings->c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDOUT_FILENO, TCSADRAIN, term_settings);

    setvbuf(stdin, NULL, _IONBF, BUFSIZ);
    setvbuf(stdout, NULL, _IONBF, BUFSIZ);
}
