/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:15:10 by kvisouth          #+#    #+#             */
/*   Updated: 2023/03/10 15:05:38 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// Minitalk explained :
// - client will send a signal (the first BIT of the string (av) ) to the server
// - server will recieve the signal and will start creating the first character
//   of the string
// - server will send SIGUSR1 to client to confirm it has received the signal
// - When client revieves the SIGUSR1 signal, it will send the next BIT of the
//   string to the server
// - This will happen until the client sent 8 signals to server (8 bits).
// - After receiving 8 signals, the server will have the first character of the
//   string (av). And this will happen until the server has the whole string.
// - When the string is complete, the server will recieve a '0' signal 8 times.
//   00000000 represents the end of the string. (it's '\0' in binary)
// - The server will send SIGUSR1 to client to confirm that the whole string
//   has been received. And will wait for the another string to be sent.
// - Client process will finish.
// - If an error occurs, the server will send SIGUSR2 and terminate the process.

int main(int ac, char **av)
{
	int	pid;

	if (ac != 2)
	{
		ft_printf("CLIENT : Invalid arguments\n");
		exit(EXIT_FAILURE);
	}
	pid = ft_atoi(av[1]);
	kill (pid, SIGUSR1);
	return (0);
}