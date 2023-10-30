/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shechong <shechong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:23:02 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/10/30 14:34:11 by shechong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(long int n)
{
	int	count;

	count = 0;
	if (n == 0)
		count = 1;
	if (n < 0)
		count += 1;
	while (n)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*result;
	long	nbr;
	int		len;

	nbr = (long)n;
	len = ft_count(nbr);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (0);
	result[len--] = '\0';
	if (nbr == 0)
		result[0] = '0';
	else if (nbr < 0)
	{
		nbr = -nbr;
		result[0] = '-';
	}
	while (nbr > 0)
	{
		result[len--] = nbr % 10 + '0';
		nbr /= 10;
	}
	return (result);
}
