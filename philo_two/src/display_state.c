/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_state.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:10:35 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/28 13:27:42 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

size_t		display_state(t_philo *philo, int x, int state)
{
	size_t	time;

	sem_wait(g_data.display);
	if (g_data.simul_state != RUN)
	{
		sem_post(g_data.display);
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
	sem_post(g_data.display);
	return (time);
}
