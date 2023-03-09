/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 18:40:09 by kvisouth          #+#    #+#             */
/*   Updated: 2023/01/13 18:40:14 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdint.h>
# include <stdarg.h>

int		ft_pf_putstr(char *s);
int		ft_pf_putptr(unsigned long ptr);
int		ft_pf_putnbr(long int nb);
int		ft_pf_puthex(unsigned long nbr, char caps);
int		ft_pf_putchar(char c);
size_t	ft_pf_strlen(const char *s);
int		ft_printf(const char *format, ...);

#endif