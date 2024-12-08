/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 17:02:31 by luluzuri          #+#    #+#             */
/*   Updated: 2024/12/08 17:27:18 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	main(int ac, char **av)
{
	ft_printf("Test\n");
	if (ac != 3)
	{
		ft_printf("Usage: %s <PID_server> <message>", av[0]);
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		minitalk();
	}
	return (0);
}
