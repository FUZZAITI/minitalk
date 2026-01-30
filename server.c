#include "minitalk.h"

void handler(int sig, siginfo_t *info, void *context)
{
    static int  bit = 0;
    static char c = 0;

    (void)context;
    if (sig == SIGUSR2)
        c |= (1 << (7 - bit));
    bit++;

    if (bit == 8)
    {
        if (c == '\0')
            write(1, "\n", 1);
        else
            write(1, &c, 1);
        bit = 0;
        c = 0;
    }
    kill(info->si_pid, SIGUSR1); 
}

void print_pid(void)
{
    char buf[12];
    int  i = 11;
    pid_t pid = getpid();

    buf[i--] = '\n';
    if (pid == 0)
        buf[i--] = '0';
    while (pid > 0)
    {
        buf[i--] = (pid % 10) + '0';
        pid /= 10;
    }
    write(1, "PID: ", 5);
    write(1, &buf[i + 1], 11 - i);
}

int main(void)
{
    struct sigaction sa;

    print_pid();
    sa.sa_sigaction = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO | SA_RESTART;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    while (1)
        pause();
}