/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 17:24:02 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/27 17:24:03 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	philo_hungry(t_philo *philo)
{
	if (g_data.min_meal == -1)
		return (1);
	if (philo->nb_meal == g_data.min_meal)
		return (0);
	return (1);
}

void		ft_eat(t_philo *philo, int i)
{
	size_t	start_eat;

	philo->state = EAT;
	philo->last_meal = display_state(philo, i + 1, EAT);
	start_eat = philo->last_meal;
	while (get_timestamp() - start_eat < g_data.time[EAT])
		usleep(10);
	++(philo->nb_meal);
	pthread_mutex_unlock(&g_data.fork[i]);
	pthread_mutex_unlock(&g_data.fork[(i + 1) % g_data.nb_philo]);
	pthread_mutex_lock(&g_data.display);
	if (philo_hungry(philo) == 0 && philo->state != DIE)
		++g_data.nb_fed;
	if (g_data.nb_fed == g_data.nb_philo && g_data.simul_state == RUN)
	{
		g_data.simul_state = END;
		printf("All philosophers ate at least %d times\n", g_data.min_meal);
	}
	pthread_mutex_unlock(&g_data.display);
}

void		ft_take_forks(t_philo *philo, int i)
{
	int first;
	int second;

	first = i;
	second = (i + 1) % g_data.nb_philo;
	if (i % 2 == 0)
	{
		first = (i + 1) % g_data.nb_philo;
		second = i;
	}
	pthread_mutex_lock(&g_data.fork[first]);
	display_state(philo, i + 1, TAKE_A_FORK);
	pthread_mutex_lock(&g_data.fork[second]);
	display_state(philo, i + 1, TAKE_A_FORK);
}

void		ft_sleep(t_philo *philo, int i)
{
	size_t	time;

	time = display_state(philo, i + 1, SLEEP);
	while (get_timestamp() - time < g_data.time[SLEEP])
		usleep(10);
}

size_t		display_state(t_philo *philo, int x, int state)
{
	size_t	time;

	pthread_mutex_lock(&g_data.display);
	if (g_data.simul_state != RUN)
	{
		pthread_mutex_unlock(&g_data.display);
		return (0);
	}
	philo->state = state;
	time = get_timestamp();
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
		g_data.simul_state = STOP;
	}
	pthread_mutex_unlock(&g_data.display);
	return (time);
}
