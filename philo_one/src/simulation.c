/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 20:00:30 by adbenoit          #+#    #+#             */
/*   Updated: 2021/05/02 12:12:58 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	ft_isalive(t_philo *philo)
{
	long int	time;

	while (1)
	{
		if (ft_stop() != 0)
			return ;
		pthread_mutex_lock(&philo->mutex);
		time = get_timestamp() - philo->last_meal;
		if (time > (long int)g_data.time[DIE])
		{
			pthread_mutex_unlock(&g_data.fork[(philo->i + 1) %
			g_data.nb_philo]);
			pthread_mutex_unlock(&g_data.fork[philo->i]);
			print_state(philo->i + 1, DIE);
			pthread_mutex_unlock(&philo->mutex);
			return ;
		}
		pthread_mutex_unlock(&philo->mutex);
		usleep(10);
	}
}

static void	routine(t_philo *philo)
{
	pthread_t	t;

	if (ft_stop() == 1)
		return ;
	if (pthread_create(&t, NULL, (void *)ft_isalive, philo) != 0)
		return ((void)print_in_thread("Thread Error.\n"));
	while (ft_stop() == 0)
	{
		ft_take_forks(philo->i);
		ft_eat(philo, philo->i);
		ft_sleep(philo->i);
	}
	pthread_join(t, NULL);
}

int			simulation(void)
{
	int				i;
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (print_in_thread("Get Time Error.\n"));
	g_start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	i = 0;
	while (i < g_data.nb_philo)
	{
		if (pthread_create(&g_data.philo[i].t, NULL, (void *)routine,
		&g_data.philo[i]) != 0)
			return (print_in_thread("Thread Error.\n"));
		++i;
	}
	i = 0;
	while (i < g_data.nb_philo)
	{
		pthread_join(g_data.philo[i].t, NULL);
		++i;
	}
	return (0);
}

int			ft_stop(void)
{
	pthread_mutex_lock(&g_data.state);
	if (g_data.simul_state == RUN)
	{
		pthread_mutex_unlock(&g_data.state);
		return (0);
	}
	pthread_mutex_unlock(&g_data.state);
	return (1);
}
