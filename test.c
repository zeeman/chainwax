#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

#include "io.h"
#include "utils.h"


#define print(x) fputs((x), stdout)


struct termios term_settings;


int main(int argc, char** argv)
{
    initialize_tty(&term_settings);

    do {
        while (!kbhit()) { };
        printf("%c", getchar());
    } while (true);

    return 0;
}
