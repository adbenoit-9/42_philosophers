/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 01:59:58 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/13 03:22:48 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	ft_eat(t_philo *philo, int i)
{
	int time;

	philo->state = EAT;
	philo->last_eat = get_time();
	display_message(&data.mutex, i + 1, EAT);
	time = data.time[EAT] - get_time() + philo->last_eat;
	usleep(time * 1000);
	++(philo->n_eat);
	pthread_mutex_unlock(&data.fork[i]);
	pthread_mutex_unlock(&data.fork[(i + 1) % data.n]);
	usleep(100);
}

void	ft_take_forks(t_philo *philo, int i)
{
	int first;
	int second;
	
	first = i;
	second = (i + 1) % data.n;
	if (i % 2 == 0)
	{
		first = (i + 1) % data.n;
		second = i;
	}
	pthread_mutex_lock(&data.fork[first]);
	philo->state = TAKE_A_FORK;
	display_message(&data.mutex, i + 1, TAKE_A_FORK);
	pthread_mutex_lock(&data.fork[second]);
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
