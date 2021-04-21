/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 01:59:58 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/20 15:29:22 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

// static int	philo_hungry(t_philo *philo)
// {
// 	if (g_data.n_eat == -1)
// 		return (1);
// 	if (philo->n_eat == g_data.n_eat)
// 		return (0);
// 	return (1);
// }

void		ft_take_forks(t_philo *philo, int i)
{
	sem_wait(g_data.fork);
	philo_state(philo, i + 1, TAKE_A_FORK);
	philo_state(philo, i + 1, TAKE_A_FORK);
}

void		ft_eat(t_philo *philo, int i)
{
	size_t	start_eat;

	philo->state = EAT;
	philo->last_eat = philo_state(philo, i + 1, EAT);
	start_eat = philo->last_eat;
	while (get_time() - start_eat < g_data.time[EAT])
		usleep(10);
	++(philo->n_eat);
	if (philo->n_eat == g_data.n_eat)
	{
		sem_wait(g_data.done_eat);
		g_data.simul_state = END;
	}
	sem_post(g_data.fork);
}

void		ft_sleep(t_philo *philo, int i)
{
	size_t	time;

	time = philo_state(philo, i + 1, SLEEP);
	while (get_time() - time < g_data.time[SLEEP])
		usleep(10);
}

size_t		philo_state(t_philo *philo, int x, int state)
{
	size_t	time;

	sem_wait(g_data.sem);
	if (g_data.simul_state == STOP)
	{
		sem_post(g_data.sem);
		return (0);
	}
	philo->state = state;
	time = get_time();
	if (state == TAKE_A_FORK)
		printf("%zums %d has taken a fork\n", time, x);
	else if (state == EAT)
		printf("%zums %d is eating\n", time, x);
	else if (state == SLEEP)
		printf("%zums %d is sleeping\n", time, x);
	else if (state == THINK)
		printf("%zums %d is thinking\n", time, x);
	else if (state == DIE)
	{
		// sem_wait(g_data.done);
		// test = 90;
		// sem_post(g_data.done);
		printf("%zums %d die\n", time, x);
		// sem_wait(g_data.dead);
		g_data.simul_state = STOP;
	}
	sem_post(g_data.sem);
	return (time);
}
