/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 17:02:38 by luluzuri          #+#    #+#             */
/*   Updated: 2024/12/15 08:51:50 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_received_from_server = 0;

void	signal_handler(int sig_num, siginfo_t *info, void *oldact)
{
	(void)oldact;
	(void)info;
	if (sig_num == SIGUSR1)
		g_received_from_server = 1;
	if (sig_num == SIGINT)
	{
		ft_printf(RED"\nClosing client...\n");
		exit(EXIT_SUCCESS);
	}
	return ;
}

void	send_char(int pid, char *str)
{
	int		i;
	int		j;
	char	c;

	i = -1;
	c = 0;
	while (str[++i])
	{
		j = 0;
		ft_printf("[");
		while (j < 8)
		{
			c = (str[i] >> j++) & 1;
			g_received_from_server = 0;
			if (c == 1)
				kill(pid, SIGUSR1);
			if (c == 0)
				kill(pid, SIGUSR2);
			ft_printf("%d", c);
			while (!g_received_from_server)
			{
			}
		}
		ft_printf("] -> %c\n", str[i]);
	}
}

int	main(int ac, char **av)
{
	if (ac != 3)
	{
		ft_printf("Usage: %s <PID_server> <message>\n\
Exemple: %s %d test\n", av[0], av[0], getpid());
		exit(EXIT_FAILURE);
	}
	ft_printf("Client PID: %d\n", getpid());
	set_sigact();
	send_char(ft_atoi(av[1]), av[2]);
	return (0);
}
