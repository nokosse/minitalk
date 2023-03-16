/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:20:56 by kvisouth          #+#    #+#             */
/*   Updated: 2023/03/16 18:57:43 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// How does minitalk (server) will work ?
// It will 

// This function 
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
