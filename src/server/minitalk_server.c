	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_server.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 09:58:03 by luluzuri          #+#    #+#             */
/*   Updated: 2024/12/10 16:10:16 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_server.h"

char	g_tab[8];

void	gestionnaire(int sig_num, siginfo_t *info, void *rien)
{
	(void)sig_num;
	(void)rien;
	ft_printf("Message Received from PID: %d\n", info->si_pid);
}

void	sigact_checker(struct sigaction *sa)
{
	if (sigaction(SIGUSR1, sa, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	if (sigaction(SIGUSR2, sa, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	if (sigaction(SIGINT, sa, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
}

int	reveice_all_bit(void)
{
	int	i;

	i = 0;
	while (g_tab[i])
		i++;
	if (i == 8)
		return (1);
	return (0);
}

void	convert_and_print(void)
{
	unsigned char	c;
	int				i;

	i = 0;
	c = 0;
	while (i < 8)
	{
		c <<= 1;
		if (g_tab[i] == '1')
			c |= 1;
		i++;
	}
	ft_printf("%c", c);
	i = -1;
	while (g_tab[++i])
		g_tab[i] = 0;
}

int	minitalk_server(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = gestionnaire;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigact_checker(&sa);
	while (1)
	{
		pause();
		if (reveice_all_bit())
		{
			convert_and_print();
			ft_printf("\n");
		}
	}
	return (0);
}

int	main(void)
{
	ft_printf(CYAN"\n\
███╗   ███╗██╗███╗   ██╗██╗████████╗ █████╗ ██╗     ██╗  ██╗    ███████╗███████╗██████╗ ██╗   ██╗███████╗██████╗ \n\
████╗ ████║██║████╗  ██║██║╚══██╔══╝██╔══██╗██║     ██║ ██╔╝    ██╔════╝██╔════╝██╔══██╗██║   ██║██╔════╝██╔══██╗\n\
██╔████╔██║██║██╔██╗ ██║██║   ██║   ███████║██║     █████╔╝     ███████╗█████╗  ██████╔╝██║   ██║█████╗  ██████╔╝\n\
██║╚██╔╝██║██║██║╚██╗██║██║   ██║   ██╔══██║██║     ██╔═██╗     ╚════██║██╔══╝  ██╔══██╗╚██╗ ██╔╝██╔══╝  ██╔══██╗\n\
██║ ╚═╝ ██║██║██║ ╚████║██║   ██║   ██║  ██║███████╗██║  ██╗    ███████║███████╗██║  ██║ ╚████╔╝ ███████╗██║  ██║\n\
╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝   ╚═╝   ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝    ╚══════╝╚══════╝╚═╝  ╚═╝  ╚═══╝  ╚══════╝╚═╝  ╚═╝\n\
"RESET);
	ft_printf("Server PID: %d\n", getpid());
	minitalk_server();
	return (0);
}
