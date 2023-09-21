/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 19:38:18 by nwai-kea          #+#    #+#             */
/*   Updated: 2022/10/15 14:38:25 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s != c && *s)
			s++;
	}
	return (count);
}

static int	ft_word_len(char const *s, char c)
{
	int	len;

	len = 0;
	while (*s && *s++ != c)
		len++;
	return (len);
}

static char	**ft_free(char **s, int i)
{
	while (i--)
		free(s[i]);
	free(s);
	return (0);
}

static char	*ft_strndup(const char *s, int n)
{
	int		i;
	char	*result;

	result = (char *)malloc(sizeof(char) * (n + 1));
	if (!result)
		return (0);
	i = -1;
	while (++i < n)
		result[i] = s[i];
	result[i] = 0;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	int		len;
	int		i;
	int		count;
	char	**result;

	if (!s)
		return (0);
	count = ft_count_words(s, c);
	result = (char **)malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (0);
	i = -1;
	while (++i < count)
	{
		while (*s && *s == c)
			s++;
		len = ft_word_len(s, c);
		result[i] = ft_strndup(s, len);
		if (!result[i])
			return (ft_free(result, i - 1));
		s += len;
	}
	result[count] = 0;
	return (result);
}
