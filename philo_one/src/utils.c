/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 18:04:05 by adbenoit          #+#    #+#             */
/*   Updated: 2021/10/14 12:16:53 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

size_t	ft_strlen(char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		++len;
	return (len);
}

long int	ft_atoli(const char *str)
{
	int			i;
	long int	num;
	int			neg;

	i = 0;
	neg = 1;
	num = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		++i;
	if (str[i] == '-')
		neg = -1;
	if (str[i] == '-' || str[i] == '+')
		++i;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - 48);
		++i;
	}
	num = num * neg;
	return (num);
}

int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		++i;
	}
	return (1);
}

char	*ft_strcat(char *dest, const char *src)
{
	size_t	i;
	size_t	j;

	if (!src || !dest)
		return (dest);
	i = 0;
	while (dest[i])
		++i;
	j = 0;
	while (src[j])
	{
		dest[i] = src[j];
		++i;
		++j;
	}
	dest[i] = 0;
	return (dest);
}

char	*ft_uitoa(size_t n)
{
	char	*nb;
	size_t	size;
	size_t	num;

	size = 0;
	num = n;
	while (n >= 10)
	{
		++size;
		n = n / 10;
	}
	++size;
	nb = malloc(sizeof(char) * (size + 1));
	if (!nb)
		return (0);
	nb[size] = 0;
	while (size > 0)
	{
		nb[size - 1] = num % 10 + 48;
		num = num / 10;
		--size;
	}
	return (nb);
}
