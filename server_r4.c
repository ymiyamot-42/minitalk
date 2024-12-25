
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void	handle_signal(int sig)
{
	static int	bit_count = 0;
	static char	current_char = 0;

	if (sig == SIGUSR1)
		current_char |= (1 << bit_count);
	bit_count++;
	if (bit_count == 8)
	{
		write(1, &current_char, 1);
		bit_count = 0;
		current_char = 0;
	}
}


int main(void)
{
	pid_t pid;
	struct sigaction	sa;
	
	pid = getpid();
	printf("server PID = %d\n", pid);

	sa.sa_handler = handle_signal;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		pause();
	}
	return (0);

}

