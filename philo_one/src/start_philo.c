/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 13:50:36 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/09 17:15:16 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

pthread_mutex_t mutex;

int		eat(t_data *data, struct timeval *tv, int i)
{
	unsigned int	time;

	pthread_mutex_lock(&data->fork[i + 1]);
	data->philo[i].eat = 1;
	gettimeofday(tv, NULL);
	time = tv->tv_usec - data->tv->tv_usec;
	if (time - data->philo[i].timestamp[EAT] > data->time[DIE])
	{
		data->philo[i].dead = 1;
		data->philo[i].eat = 0;
		++data->n_dead;
	}
	data->philo[i].timestamp[EAT] = time;
	printf("%ldms %d is eating\n", data->philo[i].timestamp[EAT], i + 1);
	usleep(data->time[EAT]);
	++(data->philo[i].n_eat);
	data->philo[i].eat = 0;
	pthread_mutex_unlock(&data->fork[i]);
	pthread_mutex_unlock(&data->fork[i + 1]);
	return (0);
}

void	process(t_data *data)
{
	int				i;
	struct timeval	*tv;

	i = data->i;
	tv = malloc(sizeof(struct timeval));
	pthread_mutex_lock(&data->fork[i]);
	gettimeofday(tv, NULL);
	printf("%ums %d has taken a fork\n",
	tv->tv_usec - data->tv->tv_usec, i + 1);
	eat(data, tv, i);
	gettimeofday(tv, NULL);
	data->philo[i].timestamp[SLEEP] = tv->tv_usec - data->tv->tv_usec;
	printf("%ldms %d is sleeping\n", data->philo[i].timestamp[SLEEP], i + 1);
	usleep(data->time[SLEEP]);
	gettimeofday(tv, NULL);
	data->philo[i].timestamp[THINK] = tv->tv_usec - data->tv->tv_usec;
	printf("%ldms %d is thinking\n", data->philo[i].timestamp[THINK], i + 1);
}

int		start_philo(t_data *data)
{
	int i;

	i = 0;
	while (i < data->n)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		++i;
	}
	data->tv = malloc(sizeof(struct timeval));
	gettimeofday(data->tv, NULL);
	i = 0;
	while (i < data->n)
	{
		data->i = i;
		pthread_create(&data->philo[i].t, NULL, (void *)process,
		data);
		++i;
	}
	i = 0;
	while (i < data->n)
	{
		pthread_join(data->philo[i].t, NULL);
		++i;
	}
	i = 0;
	while (i < data->n)
	{
		pthread_mutex_destroy(&mutex);
		++i;
	}
	
	return (0);
}