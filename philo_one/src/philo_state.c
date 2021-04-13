/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 01:59:58 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/13 15:49:56 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	ft_eat(t_philo *philo, int i)
{
	unsigned int	start_eat;
	
	philo->state = EAT;
	philo->last_eat = display_message(&data.mutex, i + 1, EAT, philo);
	start_eat = philo->last_eat;
	while (get_time() - start_eat < data.time[EAT])
		usleep(10);
	++(philo->n_eat);
	pthread_mutex_unlock(&data.fork[i]);
	pthread_mutex_unlock(&data.fork[(i + 1) % data.n]);
	if (philo_hungry(philo) == 0)
		++data.done;
	if (data.done == data.n)
	{
		printf("All the philosophers ate %d times\n", data.n_eat);
		data.stop = 1;
	}
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
	display_message(&data.mutex, i + 1, TAKE_A_FORK, philo);
	pthread_mutex_lock(&data.fork[second]);
	display_message(&data.mutex, i + 1, TAKE_A_FORK, philo);
}

void	ft_sleep(t_philo *philo, int i)
{
	unsigned int	time;

	philo->state = SLEEP;
	time = display_message(&data.mutex, i + 1, SLEEP, philo);
	while (get_time() - time < data.time[SLEEP])
		usleep(10);
}
