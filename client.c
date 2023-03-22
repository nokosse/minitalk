/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:15:10 by kvisouth          #+#    #+#             */
/*   Updated: 2023/03/22 16:43:59 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// This function will handle the error.
void	handle_error(char *msg, char **str)
{
	if (msg != NULL)
		free(msg);
	free(*str);
	write(2, "client : error\n", 15);
	exit(EXIT_FAILURE);
}

// This function will send the '\0' to the server.
// By sending 8 times SIGUSR2 we will tell the server that the message is over.
// 8 times SIGUSR2 is equal to '\0' in binary.
int	send_null(int pid, char *str)
{
	static int	i = 0;

	if (i++ != 8)
	{
		if (kill(pid, SIGUSR1) == -1)
			handle_error(str, NULL);
		return (0);
	}
	free(str);
	return (1);
}

// This function will send the message to the server.
// It duplicates 'bit' to 'message' which is a static because
// we need to keep the message in memory until the end.
// Same for 's_pid' which is the server pid.
// 'i' is the index of the message. It is also static because
// we need to keep the index in memory until the end.
//
// When we send the '\0' we call the function 'send_null'.
// It will send 8 times SIGUSR2 to the server.
// It will be used to tell the server that the message is over.
//
// When we are on '1' we send SIGUSR2 to the server.
// When we are on '0' we send SIGUSR1 to the server.
// SIGUSR1 can be represented by '0' and SIGUSR2 by '1' in binary.
int	send_bit(int pid, char *str)
{
	static char	*message = NULL;
	static int	s_pid = 0;
	static int	i = 0;

	if (str)
		message = ft_strdup(str);
	if (!message)
		handle_error(0, 0);
	if (pid)
		s_pid = pid;
	if (message[i] == '\0')
		return (send_null(s_pid, message));
	if (message[i] == '1')
	{
		if (kill(s_pid, SIGUSR2) == -1)
			handle_error(message, &str);
	}
	else if (message[i] == '0')
	{
		if (kill(s_pid, SIGUSR1) == -1)
			handle_error(message, &str);
	}
	i++;
	return (0);
}

// This function will handle the SIGUSR signal.
// When we recieve SIGUSR1 from the server it means that the message was sent.
// When we recieve SIGUSR2 from the server it means 'error' from the server.
//
// end takes the value of 1 when the message was sent.
// being able to exit the program with success.
// The value '1' for 'end' is set in the function 'send_bit'.
// when we send the '\0' to the server.
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
	if (end == 1)
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
	if (is_empty(av[2]) == 1)
	{
		ft_putstr_fd("client : empty message\n", 2);
		exit(EXIT_FAILURE);
	}
	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);
	bin = str_to_bin(av[2]);
	if (bin == NULL)
		handle_error(0, 0);
	send_bit(ft_atoi(av[1]), bin);
	free(bin);
	while (1)
		pause();
}

// How do my minitalk works ?
//
// Client side :
// 1. The client takes string as an argument to send to the server.
// 2. The client converts that string to binary in a char *.
// 3. The client sends the binary to the server.
//		- The client sends '1' as SIGUSR2.
//		- The client sends '0' as SIGUSR1.
// 4. The client sends a SIGUSR and waits for the server to respond
//		- The server sends SIGUSR1 when the message has been received.
//		- The server sends SIGUSR2 if there is an unexpected error.
// 5. The client wait for the server to respond.
//
// Server side :
// 1. The server recieves SIGUSR1 or 2 from the client representing '1' or '0'.
// 2. It wait to recieve 8 bits (8 signals) to convert it to a char.
// 4. The server append the letter to the message.
// 5. Once the client sent '\0' (8 times SIGUSR2) the server will print the message.
