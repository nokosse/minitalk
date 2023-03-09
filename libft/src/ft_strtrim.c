/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:29:29 by kvisouth          #+#    #+#             */
/*   Updated: 2022/12/08 16:24:57 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	is_trim(const char letter, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (letter == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(const char *s, const char *set)
{
	char	*str;
	int		la_taille;
	int		i;
	int		j;
	int		n;

	i = 0;
	j = ft_strlen(s) - 1;
	while (is_trim(s[i], set) == 1 && s[i])
		i++;
	while (is_trim(s[j], set) == 1 && j > i)
		j--;
	la_taille = (j - i) + 1;
	str = malloc(la_taille * sizeof(char) + 1);
	if (!str)
		return (NULL);
	n = 0;
	while (i <= j)
		str[n++] = s[i++];
	str[n] = '\0';
	return (str);
}
