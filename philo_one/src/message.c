/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 02:07:52 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/13 04:23:26 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

unsigned int	display_message(pthread_mutex_t *m, int x, int state)
{
	unsigned int	time;

	m = NULL;
	if (data.stop == 1)
		return (0);
	time = get_time();
	// pthread_mutex_lock(m);
	if (state == TAKE_A_FORK)
		printf("%ums %d has taken a fork\n", time, x);
	else if (state == EAT)
		printf("%ums %d is eating\n", time, x);
	else if (state == SLEEP)
		printf("%ums %d is sleeping\n", time, x);
	else if (state == THINK)
		printf("%ums %d is thinking\n", time, x);
	else if (state == DIE)
		printf("%ums %d die\n", time, x);
	// pthread_mutex_unlock(m);
	return (time);
}
