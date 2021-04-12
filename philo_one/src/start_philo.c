/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 13:50:36 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/12 22:13:10 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		philo_hungry(t_philo *philo)
{
	if (data.n_eat == -1)
		return (1);
	if (philo->n_eat < data.n_eat)
		return (1);
	return (0);
}

int		eat(t_philo *philo, int i)
{
	unsigned int	time;

	pthread_mutex_lock(&data.fork[i + 1]);
	time = get_time();
	if (time - philo->last_eat > data.time[DIE])
	{
		philo->is_dead = 1;
		display_message(&data.mutex, i + 1, DIE);
		pthread_mutex_unlock(&data.fork[i]);
		pthread_mutex_unlock(&data.fork[i + 1]);
		return (DIE);
	}
	philo->last_eat = time;
	display_message(&data.mutex, i + 1, EAT);
	usleep(data.time[EAT]);
	++(philo->n_eat);
	pthread_mutex_unlock(&data.fork[i]);
	pthread_mutex_unlock(&data.fork[i + 1]);
	return (1);
}

void	routine(t_philo *philo)
{
	int				i;

	i = philo->i;
	while (philo->is_dead == 0 && philo_hungry(philo) == 1)
	{
		pthread_mutex_lock(&data.fork[i]);
		display_message(&data.mutex, i + 1, -1);
		if (eat(philo, i) == DIE)
			return ;
		display_message(&data.mutex, i + 1, SLEEP);
		usleep(data.time[SLEEP]);
		display_message(&data.mutex, i + 1, THINK);
	}
}

void		handle_philo(void)
{
	int 		i;
	pthread_t	t;

	i = 0;
	while (i < data.n)
	{
		data.philo[i].i = i;
		data.philo[i].last_eat = 0;
		pthread_create(&t, NULL, (void *)routine, &data.philo[i]);
		++i;
	}
	i = 0;
	while (i < data.n)
	{
		pthread_join(t, NULL);
		++i;
	}
}

int		start_philo(void)
{
	int 			i;
	struct timeval	tv;

	tv.tv_sec = 0;
	tv.tv_usec = 0;
	gettimeofday(&tv, NULL);
	start_time = tv.tv_usec / 1000;
	handle_philo();
	i = 0;
	while (i < data.n)
	{
		pthread_mutex_destroy(&data.fork[i]);
		++i;
	}
	pthread_mutex_destroy(&data.mutex);
	return (0);
}
