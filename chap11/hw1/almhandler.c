#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void (*my_signal(int signo, void (*handler)(int)))(int);

void alarmHandler(int signo)
{
    printf("Wake up\n");
    exit(0);
}

int main()
{
    my_signal(SIGALRM, alarmHandler);
    alarm(5);

    short i = 0;
    while (1) {
        sleep(1);
        i++;
        printf("%d second\n", i);
    }

    printf("end\n");
}

void (*my_signal(int signo, void (*handler)(int)))(int)
{
    struct sigaction act, oldact;

    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    if (sigaction(signo, &act, &oldact) < 0)
        return SIG_ERR;

    return oldact.sa_handler;
}

