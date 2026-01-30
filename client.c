#include "minitalk.h"

static int g_ack = 0;
static int	ft_atoi(char *str);

void ack_handler(int sig)
{
    (void)sig;
    g_ack = 1;
}

void send_bit(pid_t pid, int bit)
{
    g_ack = 0;
    if (bit)
        kill(pid, SIGUSR2);
    else
        kill(pid, SIGUSR1);
    while (!g_ack)
        pause();
}

void send_char(pid_t pid, unsigned char c)
{
    int bit = 7;

    while (bit >= 0)
        send_bit(pid, (c >> bit--) & 1);
}

int main(int argc, char **argv)
{
    pid_t pid;
    int   i;
    struct sigaction sa;

    if (argc != 3)
        return (write(1, "Uso: ./client <PID> <msg>\n", 26), 1);

    pid = (pid_t)ft_atoi(argv[1]);
    sa.sa_handler = ack_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGUSR1, &sa, NULL);

    i = 0;
    while (argv[2][i])
        send_char(pid, argv[2][i++]);
    send_char(pid, '\0');
}


static int	ft_atoi(char *str)
{
	int	sum;
	int	sign;
	int	found;

	sum = 0;
	sign = 1;
	found = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str && found)
	{
		if (*str >= '0' && *str <= '9')
			sum = sum * 10 + *str - '0';
		else
			found = 0;
		str++;
	}
	return (sign * sum);
}