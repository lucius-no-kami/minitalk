/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_client.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 17:02:38 by luluzuri          #+#    #+#             */
/*   Updated: 2024/12/13 08:51:48 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_client.h"

void	handle_signal(int sig)
{
	ft_printf("\nSignal %d handled.\n", sig);
}

void	send_bit(int server_pid, char c)
{
	int		i;

	i = 8;
	while (i--)
	{
		if ((c >> i) & 1)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		usleep(500);
	}
}

int	minitalk(int server_pid, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		send_bit(server_pid, str[i]);
		usleep(5);
		i++;
	}
	return (0);
}

int	mod_atoi(char *str)
{
	unsigned int	pid;
	int				i;

	pid = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		pid = pid * 10 + (str[i] - 48);
		i++;
	}
	return (pid);
}

int	main(int ac, char **av)
{
	ft_printf("Client PID: %d\n", getpid());
	if (ac != 3)
	{
		ft_printf("Usage: %s <PID_server> <message>", av[0]);
		exit(EXIT_FAILURE);
	}
	minitalk(mod_atoi(av[1]), av[2]);
	return (0);
}
