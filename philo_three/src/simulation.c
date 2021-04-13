/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 20:00:30 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/14 00:50:53 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void	checkup(t_philo *philo)
{
	size_t	time;

	time = get_time();
	while ((get_time() - philo->last_eat <= g_data.time[DIE] ||
	philo->state == EAT) && g_data.simul_state == RUN)
		usleep(10);
	philo_state(philo, philo->i + 1, DIE);
}

static void	routine(t_philo *philo)
{
	int			i;
	pthread_t	t;

	if (g_data.simul_state > 0)
		return ;
	i = philo->i;
	if (pthread_create(&t, NULL, (void *)checkup, philo) != 0)
		return ((void)printf("Thread Error.\n"));
	while (g_data.simul_state == RUN)
	{
		ft_take_forks(philo, i);
		ft_eat(philo, i);
		ft_sleep(philo, i);
		philo_state(philo, i + 1, THINK);
	}
}

int			simulation(void)
{
	int				i;
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (printf("Get Time Error.\n"));
	g_start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	i = 0;
	while (i < g_data.n)
	{
		if (pthread_create(&g_data.philo[i].t, NULL, (void *)routine,
		&g_data.philo[i]) != 0)
			return (printf("Thread Error.\n"));
		++i;
	}
	i = 0;
	while (i < g_data.n)
	{
		pthread_join(g_data.philo[i].t, NULL);
		++i;
	}
	return (0);
}
