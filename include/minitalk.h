/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 08:21:30 by luluzuri          #+#    #+#             */
/*   Updated: 2024/12/16 08:48:58 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include "../libft/libft.h"
/* #include "mlx.h" */

/* colors */
# define RED			"\033[0;31m"
# define WHITE			"\x1B[37m"
# define BLACK          "\033[0;30m"
# define GREEN          "\033[0;32m"
# define MAGENTA        "\033[0;35m"
# define CYAN           "\033[0;36m"
# define RESET          "\033[0m"

typedef struct s_pchar
{
	int		bits;
	char	*stored_bits;
}	t_pchar;

void	set_sigact(void);
void	starting_server(void);
void	signal_handler(int signum, siginfo_t *info, void *oldact);

#endif