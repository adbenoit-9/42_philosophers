/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 20:00:30 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/28 17:22:42 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	ft_isalive(t_philo *philo)
{
	long int	time;

	time = get_timestamp() - philo->last_meal;
	while ((time <= (long int)g_data.time[DIE] || philo->state == EAT)
	&& g_data.simul_state != STOP)
	{
		usleep(10);
		time = get_timestamp() - philo->last_meal;
	}
	pthread_mutex_lock(&g_data.display);
	pthread_mutex_unlock(&g_data.fork[(philo->i + 1) % g_data.nb_philo]);
	pthread_mutex_unlock(&g_data.fork[philo->i]);
	pthread_mutex_unlock(&g_data.display);
	print_state(philo, philo->i + 1, DIE);
}

static void	routine(t_philo *philo)
{
	int			i;
	pthread_t	t;

	if (g_data.simul_state > 0)
		return ;
	i = philo->i;
	if (pthread_create(&t, NULL, (void *)ft_isalive, philo) != 0)
		return ((void)print_in_thread("Thread Error.\n"));
	while (g_data.simul_state == RUN)
	{
		ft_take_forks(philo, i);
		ft_eat(philo, i);
		ft_sleep(philo, i);
		print_state(philo, i + 1, THINK);
	}
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
