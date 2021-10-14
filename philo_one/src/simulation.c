/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 20:00:30 by adbenoit          #+#    #+#             */
/*   Updated: 2021/10/14 12:15:22 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

/* Returns 1 if all philosophers threads has been created.
Otherwise returns 0. */

static int	ft_isallcreate(void)
{
	int	ret;

	ret = 1;
	pthread_mutex_lock(&g_data.create);
	if (g_data.nb_run <= g_data.nb_philo)
		ret = 0;
	pthread_mutex_unlock(&g_data.create);
	return (ret);
}

/* Check simultaneously if the philosopher is alive  */

static void	ft_isalive(t_philo *philo)
{
	long int	time;

	while (1)
	{
		if (ft_stop() != 0)
			return ;
		pthread_mutex_lock(&philo->mutex);
		time = get_timestamp() - philo->last_meal;
		if (time > (long int)g_data.time[DIED])
		{
			if (g_data.nb_philo == 1)
				pthread_mutex_unlock(&g_data.fork[0]);
			print_action(philo->i + 1, DIED);
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

	while (ft_isallcreate() == 0)
		usleep(10);
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

/* Handle the simulation: creates one thread for each philo */

int	simulation(void)
{
	int				i;
	struct timeval	tv;

	i = -1;
	while (++i < g_data.nb_philo)
	{
		if (pthread_create(&g_data.philo[i].t, NULL, (void *)routine,
				&g_data.philo[i]) != 0)
			return (print_in_thread("Thread Error.\n"));
		pthread_mutex_lock(&g_data.create);
		++g_data.nb_run;
		pthread_mutex_unlock(&g_data.create);
	}
	if (gettimeofday(&tv, NULL) == -1)
		return (print_in_thread("Get Time Error.\n"));
	g_start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	pthread_mutex_lock(&g_data.create);
	++g_data.nb_run;
	pthread_mutex_unlock(&g_data.create);
	i = -1;
	while (++i < g_data.nb_philo)
		pthread_join(g_data.philo[i].t, NULL);
	return (0);
}

int	ft_stop(void)
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
