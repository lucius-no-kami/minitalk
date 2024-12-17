/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:55:17 by luluzuri          #+#    #+#             */
/*   Updated: 2024/11/24 14:02:48 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *format, ...);
int		pf_putchar(char c);
int		pf_putstr(char *str);
int		pf_putnbr(long n);
void	pf_puthex(char c, int *count, unsigned long n);
void	pf_putadr(void *adr, int *count);

#endif