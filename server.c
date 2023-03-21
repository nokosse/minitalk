/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:20:56 by kvisouth          #+#    #+#             */
/*   Updated: 2023/03/21 18:12:59 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// There should be no errors, but if there is, we will send SIGUSR2 to client.
// The client code will handle the SIGUSR2 as an error and will exit.
void	handle_error(int pid, char *str)
{
	if (str)
		free(str);
	write(2, "server: unexpected error.\n", 26);
	kill(pid, SIGUSR2);
	exit(EXIT_FAILURE);
}

// It's not a void but a char * because we need to return NULL.
// So in handle_signal, the message, once printed becomes NULL.
char	*print_msg(char *message)
{
	write(1, message, ft_strlen(message));
	return (free(message), NULL);
}

// This function basically convert the binary to a char.
// If we recieve SIGUSR1 (0) :
// We shift the '0x80' to the right by 'bits' times.
// Note : 0x80 is equal to 10000000 in binary.
// Then we modify the bit at the index 'bits' to '0' if it's '1'
// or keep it to '1' if the bit is already '0'. That's XOR. (^=)
// If we recieve SIGUSR2 (1) :
// We do the same but with OR and not XOR.
// We modify the bit at the index 'bits' to '1' if it's '0'
// or keep it to '1' if the bit is already '1'. That's OR. (|=)
//
// When the counter 'bits' is equal to 8, it means that we have
// a full char. (ASCII) We can then print it.
// Then reset the counter 'bits' to 0 and the char 'c' to 0xFF.
// So we can start again.
//
// It knows when the message is over because the client will send
// 8 times SIGUSR2 which is equal to '\0' in binary.
// c is equal to '\0' when we recieves 8 times SIGUSR2.
void	handle_signal(int signal, siginfo_t *info, void *context)
{
	static int	pid = 0;
	static int	bits = 0;
	static char	c = 0xFF;
	static char	*message = 0;

	if (info->si_pid)
		pid = info->si_pid;
	if (signal == SIGUSR1)
		c ^= 0x80 >> bits;
	else if (signal == SIGUSR2)
		c |= 0x80 >> bits;
	bits++;
	if (bits == 8)
	{
		if (c != '\0')
			message = str_append_c(message, c);
		else
			message = print_msg(message);
		bits = 0;
		c = 0xFF;
	}
	if (kill(pid, SIGUSR1) == -1)
		handle_error (pid, message);
	(void)context;
}

// block_mask is used to specify a set of signals to be blocked.
//	sigemptyset() initializes the signal set given by 'set' to empty.
//	sigaddset() adds the individual signal specified by the value of 'signum'
//	Here we are blocking the SIGINT and SIGQUIT signals. Because they are
//	forbidden by the subject.
//	They can be called without any code mentionning them.
//	For example, SIGINT (interrupt signal) can be called by pressing CTRL+C.
//	Same for SIGQUIT (quit signal) which can be called by pressing CTRL+\.
//
// sa_handler = 0, the signal handler is set to the default behavior.
// sa_flags = SA_SIGINFO, indicates that handler has a third argument.
//	which will be a pointer to a siginfo_t structure. (info in handle_signal)
// sa_mask = block_mask, specifies a set of signals to be blocked during the
//	execution of the signal handling function.
// sa_sigaction = handle_signal, specifies the signal handler function.
//
// Now that we have set up the sigaction struct, we can use sigaction() to
//	change the action taken by a process on receipt of a specific signal.
int	main(void)
{
	struct sigaction	sa_signal;
	sigset_t			block_mask;
	int					pid;

	sigemptyset(&block_mask);
	sigaddset(&block_mask, SIGINT);
	sigaddset(&block_mask, SIGQUIT);
	sa_signal.sa_handler = 0;
	sa_signal.sa_flags = SA_SIGINFO;
	sa_signal.sa_mask = block_mask;
	sa_signal.sa_sigaction = handle_signal;
	sigaction(SIGUSR1, &sa_signal, NULL);
	sigaction(SIGUSR2, &sa_signal, NULL);
	pid = getpid();
	ft_printf("Server PID : %d\n", pid);
	while (1)
		pause();
}
