/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 19:46:59 by nwai-kea          #+#    #+#             */
/*   Updated: 2022/10/05 15:54:59 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*result;

	len = ft_strlen(s1);
	result = malloc(sizeof(char) * len + 1);
	if (!result)
		return (0);
	len = 0;
	while (s1[len])
	{
		result[len] = s1[len];
		len++;
	}
	result[len] = '\0';
	return (result);
}
