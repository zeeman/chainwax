#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "io.h"
#include "utils.h"


#define print(x) fputs((x), stdout)


struct termios term_settings;


void initialize_tty()
{
    if (!isatty(STDOUT_FILENO)) {
        fputs("Output is not a tty. Dying.\n", stderr);
        die();
    };

    tcgetattr(STDOUT_FILENO, &term_settings);

    term_settings.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDOUT_FILENO, TCSADRAIN, &term_settings);

    setvbuf(stdin, NULL, _IONBF, BUFSIZ);
    setvbuf(stdout, NULL, _IONBF, BUFSIZ);
}


int main(int argc, char** argv)
{
    initialize_tty();
    kbhit_init();

    do {
        while (!kbhit()) { };
        printf("%c", getchar());
        fflush(stdout);
    } while (true);

    return 0;
}
