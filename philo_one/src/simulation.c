/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_boring_life.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 13:50:36 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/13 16:59:35 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void		checkup(t_philo *philo)
{
	unsigned int	time;

	time = get_time();
	while ((get_time() - philo->last_eat <= data.time[DIE] || philo->state == EAT)
	&& data.simul_state == RUN)
		usleep(10);
	philo_state(philo, philo->i + 1, DIE);
}

static void		routine(t_philo *philo)
{
	int			i;
	pthread_t	t;

	if (data.simul_state > 0)
		return ;
	i = philo->i;
	pthread_create(&t, NULL, (void *)checkup, philo);
	while (data.simul_state == RUN)
	{
		ft_take_forks(philo, i);
		ft_eat(philo, i);
		ft_sleep(philo, i);
		philo_state(philo, i + 1, THINK);
	}
}

static void	clean_forks(void)
{
	int	i;

	i = 0;
	while (i < data.n)
	{
		pthread_mutex_destroy(&data.fork[i]);
		++i;
	}
}

int			simulation(void)
{
	int 			i;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	i = 0;
	while (i < data.n)
	{
		pthread_create(&data.philo[i].t, NULL, (void *)routine, &data.philo[i]);
		++i;
	}
	i = 0;
	while (i < data.n)
	{
		pthread_join(data.philo[i].t, NULL);
		++i;
	}
	clean_forks();
	pthread_mutex_destroy(&data.mutex);
	return (0);
}
