/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:20:56 by kvisouth          #+#    #+#             */
/*   Updated: 2023/03/09 14:51:35 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handler_sigusr1(int sig)
{
	(void)sig;
	ft_printf("SERVER : Received signal SIGUSR1\n");
}

int main(void)
{
	pid_t	pid;

	pid = getpid();
	ft_printf("SERVER : PID = %d\n", pid);
	signal(SIGUSR1, handler_sigusr1);
	while (1)
		pause();
}