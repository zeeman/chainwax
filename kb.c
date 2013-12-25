#include "kb.h"


#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>


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
