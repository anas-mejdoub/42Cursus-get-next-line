/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:35:28 by amejdoub          #+#    #+#             */
/*   Updated: 2024/01/16 15:46:58 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	helper_func(char *buffer, int fd)
{
	int	read_byt;

	read_byt = read(fd, buffer, BUFFER_SIZE);
	buffer[read_byt] = '\0';
	return (read_byt);
}

void	helper_2(char **res, char **line)
{
	*line = ft_substr(*res, 0, nl_(*res) + 1, 'n');
	*res = ft_substr(*res, nl_(*res) + 1, ft_strlen(*res), 'f');
}

char	*get_next_line(int fd)
{
	static char	*res[OPEN_MAX];
	char		*line;
	char		*buffer;
	int			a;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE < 0 || read(fd, 0, 0) < 0)
		return (free(res[fd]), res[fd] = NULL, NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free(res[fd]), res[fd] = NULL, NULL);
	a = 1;
	while (a > 0)
	{
		a = helper_func(buffer, fd);
		res[fd] = ft_strjoin(res[fd], buffer);
		if (!res[fd])
			return (free(buffer), NULL);
		if (nl_(res[fd]) != -1)
			return (helper_2(&res[fd], &line), free(buffer), line);
	}
	if (res[fd] && res[fd][0])
		return (line = res[fd], free(buffer), res[fd] = NULL, line);
	return (free(res[fd]), res[fd] = NULL, free(buffer), NULL);
}
