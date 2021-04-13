/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 01:59:58 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/13 02:22:01 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	ft_eat(t_philo *philo, int i)
{
	int time;

	if (i != data.n - 1)
		pthread_mutex_lock(&data.fork[i + 1]);
	else
		pthread_mutex_lock(&data.fork[0]);
	philo->state = EAT;
	philo->last_eat = get_time();
	display_message(&data.mutex, i + 1, EAT);
	time = data.time[EAT] - get_time() + philo->last_eat;
	usleep(time * 1000);
	++(philo->n_eat);
	pthread_mutex_unlock(&data.fork[i]);
	if (i != data.n - 1)
		pthread_mutex_unlock(&data.fork[i + 1]);
	else
		pthread_mutex_unlock(&data.fork[0]);
}

void	ft_take_a_fork(t_philo *philo, int i)
{
	pthread_mutex_lock(&data.fork[i]);
	philo->state = TAKE_A_FORK;
	display_message(&data.mutex, i + 1, TAKE_A_FORK);
}

void	ft_sleep(t_philo *philo, int i)
{
	unsigned int	time;

	philo->state = SLEEP;
	time = display_message(&data.mutex, i + 1, SLEEP);
	time = data.time[SLEEP] - get_time() + time;
	usleep(time * 1000);
}
