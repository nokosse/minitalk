/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:03:25 by kvisouth          #+#    #+#             */
/*   Updated: 2022/12/08 16:24:47 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last_occur;

	last_occur = 0;
	while (*s != '\0')
	{
		if ((unsigned char)*s == (unsigned char)c)
			last_occur = (char *)s;
		s++;
	}
	if (c == 0)
		return ((char *)s);
	return (last_occur);
}
