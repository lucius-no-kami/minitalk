/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 10:51:30 by luluzuri          #+#    #+#             */
/*   Updated: 2024/12/16 09:43:55 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_pid = 0;

void	signal_handler(int signum, siginfo_t *info, void *oldact)
{
	(void)oldact;
	(void)info;
	if (signum == SIGUSR1)
		g_pid = info->si_pid;
	if (signum == SIGUSR2)
		g_pid = -info->si_pid;
	if (signum == SIGINT)
	{
		ft_printf(RED"\nClosing server...\n"RESET);
		exit(EXIT_SUCCESS);
	}
}

void	init_char(t_pchar *c)
{
	int	i;

	i = -1;
	c->bits = 0;
	c->stored_bits = malloc(8);
	if (!c->stored_bits)
		return ;
	while (++i < 8)
		c->stored_bits[i] = 0;
}

void	print_char(char *str)
{
	char	result;
	int		i;

	result = 0;
	i = 7;
	while (i >= 0)
	{
		result <<= 1;
		if (str[i] == '1')
			result |= 1;
		i--;
	}
	ft_printf("%c", result);
	free(str);
	str = NULL;
}

void	char_maj(t_pchar *c, int checked_pid)
{
	if (g_pid > 0)
	{
		c->stored_bits[c->bits] = '1';
		c->bits++;
		if (c->bits == 8)
		{
			print_char(c->stored_bits);
			init_char(c);
		}
		kill(checked_pid, SIGUSR1);
	}
	else
	{
		c->stored_bits[c->bits] = '0';
		c->bits++;
		if (c->bits == 8)
		{
			print_char(c->stored_bits);
			init_char(c);
		}
		kill(-checked_pid, SIGUSR1);
	}
}

int	main(void)
{
	t_pchar	c;
	int		checked_pid;

	checked_pid = 0;
	set_sigact();
	starting_server();
	while (1)
	{
		if (g_pid)
		{
			if (checked_pid != g_pid && checked_pid != -g_pid)
				init_char(&c);
			checked_pid = g_pid;
			char_maj(&c, checked_pid);
		}
		usleep(10000);
	}
	return (0);
}
