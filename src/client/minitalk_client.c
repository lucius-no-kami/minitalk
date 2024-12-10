/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_client.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 17:02:38 by luluzuri          #+#    #+#             */
/*   Updated: 2024/12/10 11:41:41 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_client.h"

void	handle_signal(int sig)
{
	ft_printf("\nSignal %d handled.\n", sig);
}

int	minitalk(int server_pid)
{
	struct sigaction	sa;

	sa.sa_handler = handle_signal;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		perror("Erreur sigaction");
		exit(EXIT_FAILURE);
	}
	if (kill(server_pid, SIGUSR1) == -1)
	{
		perror("Erreur kill");
		exit(EXIT_FAILURE);
	}
	return (0);
}

int	main(int ac, char **av)
{
	ft_printf("Test\n");
	if (ac != 3)
	{
		ft_printf("Usage: %s <PID_server> <message>", av[0]);
		exit(EXIT_FAILURE);
	}
	minitalk(atoi(av[1]));
	return (0);
}
