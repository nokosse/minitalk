/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:15:10 by kvisouth          #+#    #+#             */
/*   Updated: 2023/03/17 18:43:22 by kvisouth         ###   ########.fr       */
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
	return (1);
}

// This function will convert the string to binary.
// ABC = 011000010110001001100011
// bin = 011000010110001001100011\0
char	*str_to_bin(char *str)
{
	char	*bin;
	int		i;
	int		j;
	int		k;

	bin = malloc(sizeof(char) * (8 * ft_strlen(str)) + 1);
	if (!bin)
		return (NULL);
	i = 0;
	while (*str)
	{
		j = 7;
		while (j >= 0)
		{
			k = *str >> j;
			if (k & 1)
				bin[i] = '1';
			else
				bin[i] = '0';
			i++;
			j--;
		}
		str++;
	}
	bin[i] = '\0';
	return (bin);
}

// This function will send either :
// SIGUSR1 on a '1' in char *bin
// SIGUSR2 on a '0' in char *bin
// SIGUSR2 8 times on a '\0' in char *bin
int send_bit(int pid, char *str) {
	static char *message = NULL;
	static int s_pid = 0;
	static int bits = -1;

	if (str) {
		message = ft_strdup(str);
		bits = -1;
	}
	if (!message)
		handle_error(0);
	if (pid)
		s_pid = pid;
	bits++;
	if (message[bits]) {
		if (message[bits] == '1')
		{
			printf("sent SIGUSR1 (1)\n");
			if (kill(s_pid, SIGUSR1) == -1)
				handle_error(message);
		}
		else
		{
			printf("sent SIGUSR2 (0)\n");
			if (kill(s_pid, SIGUSR2) == -1)
				handle_error(message);
		}
		return (0);
	}
	if (send_null(s_pid, message) == 0)
		return (0);
	return (free(message), 1);
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

	if (ac != 3)
	{
		ft_putstr_fd("client : invalid arguments\n", 2);
		exit(EXIT_FAILURE);
	}
	bin = str_to_bin(av[2]);
	printf("bin = %s\n", bin);
	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);
	send_bit(ft_atoi(av[1]), bin);
	while (1)
		pause();
	return (0);
}
