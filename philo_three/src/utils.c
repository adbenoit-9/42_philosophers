/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 18:04:05 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/30 13:56:09 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int		ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

long int		ft_atoli(const char *str)
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

int				ft_isnumber(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		++i;
	}
	return (1);
}

static size_t	ft_size(int n)
{
	size_t	size;

	size = 0;
	if (n < 0)
	{
		++size;
		n *= -1;
	}
	while (n >= 10)
	{
		++size;
		n = n / 10;
	}
	++size;
	if (n == -2147483648)
		size = 11;
	return (size);
}

char			*ft_itoa(int n)
{
	char	*nb;
	size_t	neg;
	size_t	size;
	size_t	num;

	size = ft_size(n);
	neg = 0;
	if (!(nb = malloc(sizeof(char) * (size + 1))))
		return (0);
	if (n < 0)
	{
		nb[0] = '-';
		num = -n;
		neg = 1;
	}
	else
		num = n;
	nb[size] = 0;
	while (size > neg)
	{
		nb[size - 1] = num % 10 + 48;
		num = num / 10;
		--size;
	}
	return (nb);
}

size_t			get_timestamp(void)
{
	size_t			time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000 - g_start_time;
	return (time);
}
