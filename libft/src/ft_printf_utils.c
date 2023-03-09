/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 18:43:10 by kvisouth          #+#    #+#             */
/*   Updated: 2023/01/13 18:43:13 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	ft_pf_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_pf_puthex(unsigned long nbr, char caps)
{
	int	len;

	len = 0;
	if (nbr >= 16)
	{
		len += ft_pf_puthex((nbr / 16), caps);
		len += ft_pf_puthex((nbr % 16), caps);
	}
	else
	{
		if (nbr < 10)
			len += ft_pf_putnbr(nbr);
		else
			len += ft_pf_putchar(nbr - 10 + 'a' + caps - 'x');
	}
	return (len);
}

int	ft_pf_putnbr(long int nb)
{
	int	len;

	len = 0;
	if (nb < 0)
	{
		len += ft_pf_putchar('-');
		nb *= -1;
	}
	if (nb >= 10)
	{
		len += ft_pf_putnbr(nb / 10);
		len += ft_pf_putnbr(nb % 10);
	}
	else
		len += ft_pf_putchar(nb + 48);
	return (len);
}

int	ft_pf_putptr(unsigned long ptr)
{
	int	count;

	count = 0;
	if (!ptr)
		return (ft_pf_putstr("(nil)"));
	count += ft_pf_putstr("0x");
	count += ft_pf_puthex(ptr, 'x');
	return (count);
}

int	ft_pf_putstr(char *s)
{
	int	i;

	i = 0;
	if (s != NULL)
	{
		while (s[i])
		{
			write (1, &s[i], 1);
			i++;
		}
		return (i);
	}
	return (ft_pf_putstr("(null)"));
}
