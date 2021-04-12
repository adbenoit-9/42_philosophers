/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 13:50:36 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/12 18:33:31 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		eat(t_philo *philo, int i)
{
	unsigned int	time;

	pthread_mutex_lock(&data.fork[i + 1]);
	time = get_time();
	printf("time = %u\tlast = %u\ndiff", time, philo->last_eat);
	if (time - philo->last_eat > data.time[DIE])
	{
		philo->dead = 1;
		display_message(&data.mutex, i + 1, DIE);
		pthread_mutex_lock(&philo->mutex);
		pthread_mutex_unlock(&data.fork[i]);
		pthread_mutex_unlock(&data.fork[i + 1]);
		++data.n_dead;
		return (-1);
	}
	philo->last_eat = time;
	display_message(&data.mutex, i + 1, EAT);
	usleep(data.time[EAT]);
	++(philo->n_eat);
	pthread_mutex_unlock(&data.fork[i]);
	pthread_mutex_unlock(&data.fork[i + 1]);
	return (0);
}

void	routine(t_philo *philo)
{
	int				i;

	i = philo->i;
	pthread_mutex_lock(&philo->mutex);
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_lock(&data.fork[i]);
	display_message(&data.mutex, i + 1, -1);
	if (eat(philo, i) == -1)
		return ;
	display_message(&data.mutex, i + 1, SLEEP);
	usleep(data.time[SLEEP]);
	display_message(&data.mutex, i + 1, THINK);
}

void		handle_philo(void)
{
	int 		i;
	pthread_t	t;

	i = 0;
	while (i < data.n)
	{
		data.philo[i].i = i;
		data.philo[i].last_eat = start_time;
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