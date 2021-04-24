/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 01:59:58 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/24 16:29:16 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void		ft_take_forks(t_philo *philo, int i)
{
	if (g_data.simul_state == RUN)
		sem_wait(g_data.fork);
	philo_state(philo, i + 1, TAKE_A_FORK);
	philo_state(philo, i + 1, TAKE_A_FORK);
}

void		ft_eat(t_philo *philo, int i)
{
	size_t	start_eat;

	philo->state = EAT;
	philo->last_meal = philo_state(philo, i + 1, EAT);
	start_eat = philo->last_meal;
	while (g_data.simul_state != STOP &&
	current_timestamp() - start_eat < g_data.time[EAT])
		usleep(10);
	++(philo->nb_meal);
	if (g_data.simul_state != STOP && philo->nb_meal == g_data.min_meal)
		sem_post(g_data.is_fed);
	sem_post(g_data.fork);
}

void		ft_sleep(t_philo *philo, int i)
{
	size_t	time;

	time = philo_state(philo, i + 1, SLEEP);
	while (g_data.simul_state != STOP &&
	current_timestamp() - time < g_data.time[SLEEP])
		usleep(10);
	philo_state(philo, i + 1, THINK);
}

size_t		philo_state(t_philo *philo, int x, int state)
{
	size_t	time;

	sem_wait(g_data.display);
	philo->state = state;
	time = current_timestamp();
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
		printf("%zums %d die\n", time, x);
		sem_post(g_data.is_dead);
		return (0);
	}
	sem_post(g_data.display);
	return (time);
}
