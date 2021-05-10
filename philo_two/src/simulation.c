/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 20:00:30 by adbenoit          #+#    #+#             */
/*   Updated: 2021/05/05 19:50:18 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

size_t		get_timestamp(void)
{
	size_t			time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000 - g_start_time;
	return (time);
}

static void	ft_isalive(t_philo *philo)
{
	long int	time;

	while (1)
	{
		if (ft_stop() != 0)
			return ;
		sem_wait(philo->sem);
		time = get_timestamp() - philo->last_meal;
		if (time > (long int)g_data.time[DIED])
		{
			if (g_data.nb_philo == 1)
				sem_post(g_data.fork);
			print_action(philo->i + 1, DIED);
			sem_post(philo->sem);
			return ;
		}
		sem_post(philo->sem);
		usleep(10);
	}
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
	while (ft_stop() == 0)
	{
		ft_take_forks(i);
		ft_eat(philo, i);
		ft_sleep(i);
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
	int ret;

	sem_wait(g_data.state);
	if (g_data.simul_state == RUN)
		ret = 0;
	else
		ret = 1;
	sem_post(g_data.state);
	return (ret);
}
