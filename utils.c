/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:06:09 by kvisouth          #+#    #+#             */
/*   Updated: 2023/03/22 17:02:46 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// This function will convert the string to binary.
// ABC = 01000001 01000010 01000011
// bin = 010000010100001001000011
char	*str_to_bin(char *str)
{
	char	*bin;
	int		i;
	int		j;
	int		k;

	bin = malloc(sizeof(char) * (8 * ft_strlen(str)) + 1);
	if (bin == NULL)
		return (NULL);
	i = 0;
	while (*str != '\0')
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
