/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_client.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 17:02:38 by luluzuri          #+#    #+#             */
/*   Updated: 2024/12/09 10:01:59 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_client.h"

void	handle_signal(int sig)
{
	ft_printf("\nSignal %d handled.\n", sig);
}

int	minitalk(char **args)
{
	(void)args;
	ft_printf("PID: %d\n", getpid());
	signal(SIGINT, handle_signal);
	pause();
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
	minitalk(av);
	return (0);
}
