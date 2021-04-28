/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:08:46 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/28 16:11:27 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

size_t		print_state(int x, int state)
{
	size_t	time;

	pthread_mutex_lock(&g_data.display);
	if (end_simul() == 1)
	{
		pthread_mutex_unlock(&g_data.display);
		return (0);
	}
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
		printf("%zums %d die\n", time, x);
		pthread_mutex_lock(&g_data.state);
		g_data.simul_state = STOP;
		pthread_mutex_unlock(&g_data.state);
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
