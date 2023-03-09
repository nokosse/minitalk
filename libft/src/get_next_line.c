/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 19:26:38 by kvisouth          #+#    #+#             */
/*   Updated: 2023/02/04 18:56:28 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include "../inc/get_next_line.h"

/*
	ft_strcut is used in one case in GNL.
	When the stash contains a \n, we are cutting the string
	from the \n to the end of the string, so our new stash does not
	longer contain the \n ans the past line.
*/

static char	*ft_strcut(char *str)
{
	char	*cutted_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] != '\n')
		i++;
	cutted_str = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!cutted_str)
		return (NULL);
	i++;
	while (str[i])
		cutted_str[j++] = str[i++];
	cutted_str[j] = '\0';
	free(str);
	return (cutted_str);
}

/*
	check_line is juste a boolean that returns 1 if our string contains a \n.
	Else it returns -1.
*/

static int	check_line(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (-1);
}

/*
	I used this function to make GNL less than 25 lines.
	This block of code was between the variable declaration and the while loop.
	This function is checking the validity of fd, BUFFER_SIZE and the stash.
	And it's initializing our stash for the rest of GNL if the verification passed.
*/

static char	*stash_checking(int fd, char *stash, char *buff, int readed)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	readed = read(fd, buff, BUFFER_SIZE);
	if (readed <= 0 && !stash)
	{
		free(buff);
		return (NULL);
	}
	buff[readed] = '\0';
	if (!stash)
		stash = ft_substr(buff, 0, ft_strlen(buff));
	else
		stash = ft_strjoin_gnl(stash, buff);
	free(buff);
	if (stash[0] == '\0')
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	return (stash);
}

/*
	I also used this function to make GNL less than 25 lines.
	This bllock of code was replaced by the 3 last lines in the while loop.
	This function is handling the 2 cases of GNL.
	1. The last line case.
	2. The line with a \n case.
	It's parameter is **stash and not *stash because of we need to modify the
	original stash, and not a copy of it. It's called a : Pass by reference in C.
*/

char	*cases_handing(char **stash, int readed)
{
	char	*line;

	if (readed < BUFFER_SIZE && check_line(*stash) == -1)
	{
		line = ft_substr(*stash, 0, ft_strlen(*stash));
		free(*stash);
		*stash = NULL;
		return (line);
	}
	else if (check_line(*stash) != -1)
	{
		line = ft_substr(*stash, 0, ft_strchr(*stash, '\n') - *stash + 1);
		*stash = ft_strcut(*stash);
		return (line);
	}
	return (NULL);
}

/*
	GNL is a function that reads a file line by line.
	We read the file until we find a \n or the end of the file.
	And we return the line we just read.
	It returns NULL if there is nothing to read.
	I added bonus here as well.
*/

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*buff;
	char		*line;
	int			readed;

	readed = 0;
	buff = NULL;
	if (fd > 1024)
		return (NULL);
	stash[fd] = stash_checking(fd, stash[fd], buff, readed);
	while (stash[fd])
	{
		buff = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
		if (!buff)
			return (NULL);
		readed = read(fd, buff, BUFFER_SIZE);
		if (readed == -1)
			return (free(buff), NULL);
		stash[fd] = ft_strjoin_gnl(stash[fd], buff);
		free(buff);
		line = cases_handing(&stash[fd], readed);
		if (line)
			return (line);
	}
	return (NULL);
}
