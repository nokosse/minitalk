/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 14:59:42 by kvisouth          #+#    #+#             */
/*   Updated: 2023/01/13 18:44:27 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

static int	ft_convert(const char letter, va_list args)
{
	int	count;

	count = 0;
	if (letter == 'c')
		count += ft_pf_putchar(va_arg(args, int));
	else if (letter == 's')
		count += ft_pf_putstr(va_arg(args, char *));
	else if (letter == 'p')
		count += ft_pf_putptr(va_arg(args, unsigned long));
	else if (letter == 'd' || letter == 'i')
		count += ft_pf_putnbr(va_arg(args, int));
	else if (letter == 'u')
		count += ft_pf_putnbr(va_arg(args, unsigned int));
	else if (letter == 'x')
		count += ft_pf_puthex(va_arg(args, unsigned int), 'x');
	else if (letter == 'X')
		count += ft_pf_puthex(va_arg(args, unsigned int), 'X');
	else if (letter == '%')
		count += ft_pf_putchar(letter);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	int			index;
	int			count;
	va_list		args;

	va_start (args, format);
	count = 0;
	index = 0;
	while (format[index])
	{
		if (format[index] == '%')
		{
			count += ft_convert(format[index + 1], args);
			index++;
		}
		else
			count += ft_pf_putchar(format[index]);
		index++;
	}
	va_end(args);
	return (count);
}
