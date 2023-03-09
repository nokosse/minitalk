/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 14:05:52 by kvisouth          #+#    #+#             */
/*   Updated: 2023/02/04 18:09:59 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include "../inc/get_next_line.h"

/*
	ft_strjoin that works exactly like libft's ft_strjoin.
	The only difference is that it frees s1.
	It concatenates s2 to s1 in a new string (str).
	It is used in GNL to concatenate the stash and the buffer.
*/

char	*ft_strjoin_gnl(const char *s1, const char *s2)
{
	char	*str;
	size_t	size;
	int		i;
	int		j;

	size = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	free((char *)s1);
	return (str);
}
