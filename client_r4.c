
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void	send_bit(pid_t pid, int bit)
{
	if(bit == 0)
		kill(pid, SIGUSR1);
	if(bit == 1)
		kill(pid, SIGUSR2);
}

void send_char(pid_t pid, char c)
{
	int i;
	int bit;
	
	i = 7;
	while(i >= 0)
	{
		bit = (c >> i) & 1;
		send_bit(pid, bit);
		// pause();
	}
}

void send_str(pid_t pid, char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		send_char(pid, str[i]);
	}


}


int main(int argc, char **argv)
{
	pid_t pid;
	const char *str;

	if (argc != 3)
	{
		printf("error\n");
		exit(EXIT_FAILURE);
	}


	pid = atoi(argv[1]);
	str = argv[2];



	return 0;



}




// int main()
// {
// 	//文字を表示
// 	char c = 'a';
// 	int bit;

// 	for(int i = 7; i>= 0; i--)
// 	{
// 		bit = (c >> i) & 1;
// 		printf("%d", bit);
// 	}

// 	printf("\n");

// 	return 0;
// }