/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 20:00:30 by adbenoit          #+#    #+#             */
/*   Updated: 2021/10/15 18:24:13 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

/* Returns the status of the simulation */

int	get_status(void)
{
	int	ret;

	pthread_mutex_lock(&g_data.state);
	ret = g_data.status;
	pthread_mutex_unlock(&g_data.state);
	return (ret);
}

/* Changes the status of the simulation */

void	set_status(int status)
{
	pthread_mutex_lock(&g_data.state);
	g_data.status = status;
	pthread_mutex_unlock(&g_data.state);
}

/* Check simultaneously if all philosophers steel alive  */

static void	philo_life(t_data *data)
{
	long int	time;
	int			i;

	while (1)
	{
		i = -1;
		while (++i < data->nb_philo)
		{
			if (get_status() != RUN)
				return ;
			pthread_mutex_lock(&data->philo[i].mutex);
			time = get_timestamp() - data->philo[i].last_meal;
			if (time > (long int)data->time[DIED])
			{
				if (data->nb_philo == 1)
					pthread_mutex_unlock(&data->fork[0]);
				print_action(data->philo[i].i + 1, DIED);
				pthread_mutex_unlock(&data->philo[i].mutex);
				return ;
			}
			pthread_mutex_unlock(&data->philo[i].mutex);
			usleep(10);
		}
	}
}

/* While the simulation is running, the philosopher continues his routine */

static void	routine(t_philo *philo)
{
	if (philo->i % 2 == 0)
		usleep(5);
	while (get_status() == RUN)
	{
		ft_take_forks(*philo, philo->i);
		ft_eat(philo, philo->i);
		ft_sleep(philo->i);
		print_action(philo->i + 1, THINK);
	}
}
/* Handle the simulation: creates one thread for each philo */

int	simulation(void)
{
	int				i;
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (print_in_thread("Get Time Error.\n"));
	g_start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	i = -1;
	while (++i < g_data.nb_philo)
	{
		if (pthread_create(&g_data.philo[i].t, NULL, (void *)routine,
				&g_data.philo[i]) != 0)
			return (print_in_thread("Thread Error.\n"));
	}
	philo_life(&g_data);
	i = -1;
	while (++i < g_data.nb_philo)
		pthread_join(g_data.philo[i].t, NULL);
	return (0);
}
