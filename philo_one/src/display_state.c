/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_state.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:08:46 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/27 17:22:50 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

size_t		display_state(t_philo *philo, int x, int state)
{
	size_t	time;

	pthread_mutex_lock(&g_data.display);
	if (g_data.simul_state != RUN)
	{
		pthread_mutex_unlock(&g_data.display);
		return (0);
	}
	philo->state = state;
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
		g_data.simul_state = STOP;
	}
	pthread_mutex_unlock(&g_data.display);
	return (time);
}
