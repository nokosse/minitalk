/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:50:04 by kvisouth          #+#    #+#             */
/*   Updated: 2022/12/08 16:23:12 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static void	free_tab(char **s)
{
	int	i;

	i = 0;
	while (i > 0)
	{
		free(s[i]);
		i--;
	}
	free(s);
}

static int	is_sep(const char s, char c)
{
	if (s == c)
		return (1);
	return (0);
}

static size_t	strcnt(const char *s, char c)
{
	int	i;
	int	cpt;

	i = 0;
	cpt = 0;
	while (s[i] != '\0')
	{
		while (is_sep(s[i], c) == 1 && s[i])
			i++;
		if (s[i] != '\0')
			cpt++;
		while (is_sep(s[i], c) == 0 && s[i])
			i++;
	}
	return (cpt);
}

static char	*put_word(const char *s, char c)
{
	int		wdlen;
	char	*wd;
	int		i;
	int		x;

	i = 0;
	x = 0;
	while (s[x] != '\0' && is_sep(s[x], c) == 0)
		x++;
	wdlen = x;
	wd = malloc (wdlen * sizeof(char) + 1);
	if (!wd)
		return (NULL);
	while (i < wdlen)
	{
		wd[i] = s[i];
		i++;
	}
	wd[i] = '\0';
	return (wd);
}

char	**ft_split(const char *s, char c)
{
	char	**strs;
	int		i;

	strs = malloc ((sizeof(char *) * (strcnt(s, c) + 1)));
	if (!strs)
	{
		free_tab(strs);
		return (NULL);
	}
	i = 0;
	while (*s != '\0')
	{
		while (is_sep(*s, c) == 1 && *s)
			s++;
		if (*s)
			strs[i++] = put_word(s, c);
		while (is_sep(*s, c) == 0 && *s)
			s++;
	}
	strs[i] = NULL;
	return (strs);
}
