/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 13:50:36 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/13 02:17:22 by adbenoit         ###   ########.fr       */
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
	// pthread_mutex_lock(&philo->mutex);
	while (get_time() - philo->last_eat < data.time[DIE] || philo->state == EAT)
		usleep(10);
	philo->state = DIE;
	display_message(&data.mutex, philo->i + 1, DIE);
	if (philo->state == TAKE_A_FORK)
		pthread_mutex_lock(&data.fork[philo->i]);
	if (data.n_eat != -1)
		return ;
	data.stop = 1;
	// pthread_mutex_unlock(&philo->mutex);
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
		ft_take_a_fork(philo, i);
		ft_eat(philo, i);
		ft_sleep(philo, i);
		philo->state = THINK;
		display_message(&data.mutex, i + 1, THINK);
	}
}

void		handle_philo(void)
{
	int 		i;
	pthread_t	t;

	i = 0;
	while (i < data.n)
	{
		data.philo[i].i = i;
		data.philo[i].last_eat = 0;
		pthread_create(&t, NULL, (void *)routine, &data.philo[i]);
		++i;
	}
	i = 0;
	while (i < data.n)
	{
		pthread_join(t, NULL);
		++i;
	}
}

int		start_philo(void)
{
	int 			i;
	struct timeval	tv;

	tv.tv_sec = 0;
	tv.tv_usec = 0;
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
