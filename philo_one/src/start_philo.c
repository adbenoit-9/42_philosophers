/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 13:50:36 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/13 15:49:54 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		philo_hungry(t_philo *philo)
{
	if (data.n_eat == -1)
		return (1);
	if (philo->n_eat < data.n_eat)
		return (1);
	return (0);
}

void	check_state(t_philo *philo)
{
	unsigned int	time;

	time = get_time();
	while (time - philo->last_eat <= data.time[DIE] || philo->state == EAT)
		time = get_time();
	philo->state = DIE;
	display_message(&data.mutex, philo->i + 1, DIE, philo);
	data.stop = 1;
}

void	routine(t_philo *philo)
{
	int			i;
	pthread_t	t;

	if (data.stop == 1)
		return ;
	i = philo->i;
	pthread_create(&t, NULL, (void *)check_state, philo);
	while (philo->state != DIE && philo_hungry(philo) == 1 && data.stop == 0)
	{
		ft_take_forks(philo, i);
		ft_eat(philo, i);
		ft_sleep(philo, i);
		philo->state = THINK;
		display_message(&data.mutex, i + 1, THINK, philo);
	}
}

void		handle_philo(void)
{
	int 		i;

	i = 0;
	while (i < data.n)
	{
		data.philo[i].i = i;
		data.philo[i].last_eat = 0;
		pthread_create(&data.philo[i].t, NULL, (void *)routine, &data.philo[i]);
		++i;
	}
	i = 0;
	while (i < data.n)
	{
		pthread_join(data.philo[i].t, NULL);
		++i;
	}
}

int		start_philo(void)
{
	int 			i;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
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
