/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 20:00:30 by adbenoit          #+#    #+#             */
/*   Updated: 2021/05/01 21:29:07 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static void	ft_isalive(t_philo *philo)
{
	long int	time;

	while (1)
	{
		if (end_simul() != 0)
			return ;
		sem_wait(philo->sem);
		time = get_timestamp() - philo->last_meal;
		sem_post(philo->sem);
		if (time > (long int)g_data.time[DIE])
		{
			sem_post(g_data.fork);
			sem_post(g_data.his_turn);
			print_state(philo->i + 1, DIE);
			return ;
		}
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
	while (end_simul() == 0)
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

int			end_simul(void)
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
