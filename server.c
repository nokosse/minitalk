/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:20:56 by kvisouth          #+#    #+#             */
/*   Updated: 2023/03/16 19:20:22 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// How does minitalk (server) will work ?
// It will 

// This function will convert a number to binary.
char	*get_bin(int num)
{
	static char	bin[9] = {'\0'};
	int			i;

	i = 7;
	while (i >= 0)
	{
		bin[i] = ((num & 1) ^ 1) + '0';
		num >>= 1;
		i--;
	}
	return (bin);
}

// This function will convert a 8bits binary to a char.
char	bin_to_char(char *bin)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (i < 8)
	{
		num <<= 1;
		if (bin[i] == '1')
			num |= 1;
		i++;
	}
	return (num);
}

// This function will handle the signal.
void	handle_signal(int sig)
{
	static int	count = 0;
	static int	num = 0;

	if (sig == SIGUSR1)
	{
		num <<= 1;
		count++;
	}
	else if (sig == SIGUSR2)
	{
		num <<= 1;
		num |= 1;
		count++;
	}
	if (count == 8)
	{
		printf("%s\n", get_bin(num));
		printf("%c", bin_to_char(get_bin(num)));
		count = 0;
		num = 0;
	}
}

int	main(void)
{
	pid_t				pid;
	struct	sigaction	sa;

	pid = getpid();
	printf("PID: %d\n", pid);
	
	sa.sa_handler = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	
	while (1)
		pause();
	return (0);
}
