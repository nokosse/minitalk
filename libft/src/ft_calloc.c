/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 12:01:59 by kvisouth          #+#    #+#             */
/*   Updated: 2023/01/13 18:51:06 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;
	int		len;
	int		i;
	char	*str;

	if (size && SIZE_MAX / size < nmemb)
		return (NULL);
	len = nmemb * size;
	p = malloc(len);
	if (!p)
		return (NULL);
	i = 0;
	str = p;
	while (i < len)
	{
		str[i] = '\0';
		i++;
	}
	return (p);
}
