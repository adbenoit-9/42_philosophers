/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 01:59:58 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/13 04:51:34 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	ft_eat(t_philo *philo, int i)
{
	unsigned int	need;
	unsigned int	time;
	
	philo->state = EAT;
	philo->last_eat = display_message(&data.mutex, i + 1, EAT);
	need = data.time[EAT] * 1000;
	time = philo->last_eat;
	while (get_time() - time < need)
	{
		// printf("time = %u\tneed = %u\n", get_time() - time, need);
		usleep(10); //ca marche pas wttttf
	}
	++(philo->n_eat);
	pthread_mutex_unlock(&data.fork[i]);
	pthread_mutex_unlock(&data.fork[(i + 1) % data.n]);
	// usleep(100);
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
	philo->state = SLEEP;
	display_message(&data.mutex, i + 1, SLEEP);
	usleep(data.time[SLEEP] * 1000);
}
