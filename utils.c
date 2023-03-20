/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:06:09 by kvisouth          #+#    #+#             */
/*   Updated: 2023/03/20 16:24:56 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// This function will convert the string to binary.
// ABC = 011000010110001001100011
// bin = 0110000101	10001001100011\0
char	*str_to_bin(char *str)
{
	char	*bin;
	int		i;
	int		j;
	int		k;

	bin = malloc(sizeof(char) * (8 * ft_strlen(str)) + 1);
	if (!bin)
		return (NULL);
	i = 0;
	while (*str)
	{
		j = 7;
		while (j >= 0)
		{
			k = *str >> j;
			if (k & 1)
				bin[i] = '1';
			else
				bin[i] = '0';
			i++;
			j--;
		}
		str++;
	}
	return (bin[i] = '\0', bin);
}

char	*str_append_empty(char c)
{
	char	*add;

	add = malloc(sizeof(char) * 2);
	if (!add)
		return (NULL);
	add[0] = c;
	add[1] = '\0';
	return (add);
}

// This function will append a char to a string.
char	*str_append_c(char *str, char c)
{
	char	*add;
	int		i;

	if (!c)
		return (NULL);
	if (!str)
		return (str_append_empty(c));
	add = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!add)
		return (free(str), NULL);
	i = 0;
	while (str[i])
	{
		add[i] = str[i];
		i++;
	}
	free(str);
	add[i++] = c;
	add[i] = '\0';
	return (add);
}
