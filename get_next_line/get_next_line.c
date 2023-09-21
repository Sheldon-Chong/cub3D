/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 15:52:08 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/09/20 17:56:25 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "stdio.h"
#include "fcntl.h"

char	*ft_read(int fd, char *s)
{
	char	*string;
	int		r;

	string = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!string)
		return (0);
	r = 1;
	while (r != 0 && !ft_strchr_gnl(s, '\n'))
	{
		r = read(fd, string, BUFFER_SIZE);
		if (r == -1)
		{
			free(string);
			return (0);
		}
		string[r] = '\0';
		s = ft_strjoin_gnl(s, string);
	}
	free(string);
	return (s);
}

char	*ft_get(char *s)
{
	int		i;
	char	*str;

	i = 0;
	if (!s[i])
		return (0);
	while (s[i] && s[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (0);
	ft_strlcpy_gnl(str, s, i + 1);
	return (str);
}

char	*ft_nextline(char *s)
{
	int		i;
	int		j;
	int		len;
	char	*str;

	i = 0;
	j = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (!s[i])
	{
		free(s);
		return (0);
	}
	len = ft_strlen_gnl(&s[i]);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	i++;
	while (s[i])
		str[j++] = s[i++];
	str[j] = '\0';
	free(s);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	str = ft_read(fd, str);
	if (!str)
		return (0);
	line = ft_get(str);
	str = ft_nextline(str);
	return (line);
}
