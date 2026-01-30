#include "minitalk.h"

void	ft_putnbr(int nb);
void	ft_putnbr(int nb);




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

    write(1, "PID: ", 5);
    ft_putnbr(pid);
    write(1, "\n", 1);
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


void	ft_putchar(char c)
{
	write (1, &c, 1);
}

void	ft_putnbr(int nb)
{
	if (nb < 0)
	{
		nb = -nb;
	}
	if (nb >= 10)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	else
		ft_putchar(nb + '0');
}