/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:15:10 by kvisouth          #+#    #+#             */
/*   Updated: 2023/03/16 18:24:50 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// This function will send 8 bits of '0' to the server.
// 00000000 (\0), meaning the end of the string.
int	send_end(int pid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (kill(pid, SIGUSR2) == -1)
			return (0);
		i++;
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
	return (bin[i] = '\0', bin);
}

// This function will send the binary to the server.
// It will parse *bin and send SIGUSR1 on 1 and SIGUSR2 on 0.
int	send_signal(int pid, char *bin)
{
	int	i;

	i = 0;
	while (bin[i])
	{
		if (kill(pid, 0) == -1)
			return (0);
		if (bin[i] == '1')
		{
			printf("Sending SIGUSR1 to %d\n", pid);
			if (kill(pid, SIGUSR1) == -1)
				return (0);
		}
		else if (bin[i] == '0')
		{
			printf("Sending SIGUSR2 to %d\n", pid);
			if (kill(pid, SIGUSR2) == -1)
				return (0);
		}
		usleep(200);
		i++;
	}
	// send_end(pid);
	if (kill(pid, 0) == -1)
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	char	*bin;
	int		pid;

	if (ac != 3)
	{
		ft_putstr_fd("client : invalid arguments\n", 2);
		exit(EXIT_FAILURE);
	}
	pid = ft_atoi(av[1]);
	bin = str_to_bin(av[2]);
	send_signal(pid, bin);
	free(bin);
	return (0);
}
