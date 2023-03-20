/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:20:56 by kvisouth          #+#    #+#             */
/*   Updated: 2023/03/20 19:53:35 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_error(int pid, char *str)
{
	if (str)
		free(str);
	write(2, "server: unexpected error.\n", 26);
	kill(pid, SIGUSR2);
	exit(EXIT_FAILURE);
}

char	*print_msg(char *message)
{
	write(1, message, ft_strlen(message));
	return (free(message), NULL);
}

// This function will handle the signal. Converting the sequence of signals
// and translating it from binary to ASCII.
// c is the character that will be printed.
// 
void	handle_signal(int signum, siginfo_t *info, void *context)
{
	static char	c = 0xFF;
	static int	bits = 0;
	static int	pid = 0;
	static char	*message = 0;

	(void)context;
	if (info->si_pid)
		pid = info->si_pid;
	if (signum == SIGUSR1)
		c ^= 0x80 >> bits;
	else if (signum == SIGUSR2)
		c |= 0x80 >> bits;
	if (++bits == 8)
	{
		if (c)
			message = str_append_c(message, c);
		else
			message = print_msg(message);
		bits = 0;
		c = 0xFF;
	}
	if (kill(pid, SIGUSR1) == -1)
		handle_error (pid, message);
}

// struct sigaction is a structure that contains the information
// about the signal handler.
// sigset_t is a set of signals.
int	main(void)
{
	struct sigaction	sa_signal;
	sigset_t			block_mask;

	sigemptyset(&block_mask);
	sigaddset(&block_mask, SIGINT);
	sigaddset(&block_mask, SIGQUIT);
	sa_signal.sa_handler = 0;
	sa_signal.sa_flags = SA_SIGINFO;
	sa_signal.sa_mask = block_mask;
	sa_signal.sa_sigaction = handle_signal;
	sigaction(SIGUSR1, &sa_signal, NULL);
	sigaction(SIGUSR2, &sa_signal, NULL);
	write(1, "PID: \n", 6);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	while (1)
		pause();
}
