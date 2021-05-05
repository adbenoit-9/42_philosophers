/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 15:39:28 by adbenoit          #+#    #+#             */
/*   Updated: 2021/05/05 16:33:24 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

size_t	ft_strcat(char *dest, char *src)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dest[j])
		++j;
	while (src[i])
	{
		dest[j] = src[i];
		++i;
		++j;
	}
	dest[j] = 0;
	return (j);
}

void	ft_putmess(int x, size_t time, char *str)
{
	char	buffer[4096];
	size_t		n;

	buffer[0] = 0;
	ft_strcat(buffer, ft_uitoa(time));
	ft_strcat(buffer, "ms ");
	ft_strcat(buffer, ft_uitoa(x));
	ft_strcat(buffer, " ");
	n = ft_strcat(buffer, str);
	write(1, buffer, n);
}

size_t	print_state(int x, int state)
{
	size_t	time;

	pthread_mutex_lock(&g_data.display);
	if (ft_stop() == 1)
		return (pthread_mutex_unlock(&g_data.display));
	time = get_timestamp();
	if (state == TAKE_A_FORK)
		printf("%zums %d has taken a fork\n", time, x);
	else if (state == EAT)
		printf("%zums %d is eating\n", time, x);
	else if (state == SLEEP)
		printf("%zums %d is sleeping\n", time, x);
	else if (state == THINK)
		printf("%zums %d is thinking\n", time, x);
	else if (state == DIE)
	{
		pthread_mutex_lock(&g_data.state);
		g_data.simul_state = STOP;
		pthread_mutex_unlock(&g_data.state);
		ft_putmess(x, time, "died\n");
	}
	pthread_mutex_unlock(&g_data.display);
	return (time);
}

int		print_in_thread(char *str)
{
	pthread_mutex_lock(&g_data.display);
	printf("%s", str);
	pthread_mutex_unlock(&g_data.display);
	return (0);
}
