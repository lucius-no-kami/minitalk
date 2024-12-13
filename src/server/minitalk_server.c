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

int	g_pid;

void	show_char(char *tab)
{
	int		i;
	char	c;

	i = 0;
	c = 0;
	while (i < 8)
	{
		c <<= 1;
		if (tab[i] == 1)
			c |= 1;
		i++;
	}
	ft_printf("%c", c);
}

void	check_pid(int entring_pid)
{
	static char	tab[8];
	static int	i = 0;

	if (entring_pid != g_pid)
	{
		kill(g_pid, SIGINT);
	}
	g_pid = entring_pid;
	if (g_pid > 0)
		tab[i] = 1;
	else
		tab[i] = 0;
	i++;
	if (i == 8)
		show_char(tab);
}

void	gestionnaire(int sig_num, siginfo_t *info, void *rien)
{
	(void)rien;
	ft_printf("\nMessage Received from PID: %d\n", info->si_pid);
	if (sig_num == SIGUSR1)
		check_pid(info->si_pid);
	else if (sig_num == SIGUSR2)
		check_pid(-info->si_pid);
	if (sig_num == SIGINT)
	{
		ft_printf("Exciting signal recieved...\n");
		exit(EXIT_SUCCESS);
	}
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
