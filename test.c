#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "kb.h"


#define print(x) fputs((x), stdout)


struct termios term_settings;


void die()
{
    exit(1);
}


void initialize_tty()
{
    if (!isatty(STDOUT_FILENO)) {
        fputs("Output is not a tty. Dying.\n", stderr);
        die();
    };

    tcgetattr(STDOUT_FILENO, &term_settings);

    term_settings.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDOUT_FILENO, TCSADRAIN, &term_settings);
}


int main(int argc, char** argv)
{
    initialize_tty();
    kbhit_init();

    /*while ((c = getchar_nb()) < 0) { };*/
    while (!kbhit()) { };

    printf("%c\n", getchar());

    return 0;
}
