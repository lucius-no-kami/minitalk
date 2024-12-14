/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 10:51:30 by luluzuri          #+#    #+#             */
/*   Updated: 2024/12/14 16:37:57 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_pid = 0;

void	signal_handler(int signum, siginfo_t *info, void *oldact)
{
	(void)oldact;
	(void)info;
	g_pid = info->si_pid;
	if (signum == SIGUSR1)
		g_pid = info->si_pid;
	if (signum == SIGUSR2)
		g_pid = -info->si_pid;
	if (signum == SIGINT)
		exit(EXIT_SUCCESS);
}

void	init_char(t_pchar *c)
{
	c->bits = 0;
	c->stored_bits = malloc(8);
	if (!c->stored_bits)
		return ;
	ft_bzero(c->stored_bits, 8);
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
		sleep(1);
	}
	return (0);
}
