
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void	handle_signal(int sig)
{
	static int	bit_count = 7;
	static char	current_char = 0;

	// printf("c_0:%d, bit_count:%d\n", (int)current_char,bit_count);
	if (sig == SIGUSR2)
	{
		// printf("\nSIGUSR2\n");
		current_char |= (1 << bit_count);
	}
	// printf("c_r:%d, bit_count:%d\n", (int)current_char,bit_count);
	
	bit_count--;
	if (bit_count < 0)
	{
		// write(1, "\n", 1);
		write(1, &current_char, 1);
		// write(1, "\n", 1);
		bit_count = 7;
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
	// if (sigaction(SIGUSR1, &sa, NULL) == -1)
	// {
	// 	perror("sigaction");
	// 	exit(EXIT_FAILURE);
	// }
	// if (sigaction(SIGUSR2, &sa, NULL) == -1)
	// {
	// 	perror("sigaction");
	// 	exit(EXIT_FAILURE);
	// }
	while (1)
	{
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		pause();
	}
	return (0);

}

