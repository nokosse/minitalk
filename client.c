/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:15:10 by kvisouth          #+#    #+#             */
/*   Updated: 2023/03/20 18:02:37 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// This function will handle the error.
void	handle_error(char *msg)
{
	if (msg)
		free(msg);
	write(2, "client : error\n", 15);
	exit(EXIT_FAILURE);
}

// This function will send 8 times SIGUSR2 to the server.
// It will be used to tell the server that the message is over.
// When we send the '\0'.
int	send_null(int pid, char *str)
{
	static int	i = 0;

	if (i++ != 8)
	{
		if (kill(pid, SIGUSR1) == -1)
			handle_error(str);
		return (0);
	}
	free(str);
	return (1);
}

int	send_bit(int pid, char *str)
{
	static char	*message = NULL;
	static int	s_pid = 0;
	static int	i = 0;

	if (str)
		message = ft_strdup(str);
	if (!message)
		handle_error(0);
	if (pid)
		s_pid = pid;
	if (message[i] == '\0')
		return (send_null(s_pid, message));
	if (message[i] == '1')
	{
		if (kill(s_pid, SIGUSR2) == -1)
			handle_error(message);
	}
	else if (message[i] == '0')
	{
		if (kill(s_pid, SIGUSR1) == -1)
			handle_error(message);
	}
	i++;
	return (0);
}

// This function will handle the SIGUSR signal.
void	handle_signal(int sig)
{
	int	end;

	end = 0;
	if (sig == SIGUSR1)
		end = send_bit(0, NULL);
	else if (sig == SIGUSR2)
	{
		write(2, "client : server ended unexpectedly\n", 35);
		exit(EXIT_FAILURE);
	}
	if (end)
	{
		write (1, "client : message sent\n", 22);
		exit(EXIT_SUCCESS);
	}
}

int	main(int ac, char **av)
{
	char	*bin;

	if (ac != 3 || ft_atoi(av[1]) <= 0)
	{
		ft_putstr_fd("client : invalid arguments\n", 2);
		exit(EXIT_FAILURE);
	}
	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);
	bin = str_to_bin(av[2]);
	send_bit(ft_atoi(av[1]), bin);
	free(bin);
	while (1)
		pause();
	return (0);
}
