#include "io.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <unistd.h>

#include "utils.h"


struct timeval tv;
fd_set fds;


void kbhit_init()
{
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds); // for some reason we only have to do this once
}


int kbhit()
{
    FD_SET(STDIN_FILENO, &fds);
    select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
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

    kbhit_init();
}
