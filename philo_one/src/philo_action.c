/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 17:23:38 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/30 15:30:23 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	philo_hungry(t_philo *philo)
{
	if (g_data.nb_meal_min == -1)
		return (1);
	if (philo->nb_meal == g_data.nb_meal_min)
		return (0);
	return (1);
}

void		ft_take_forks(int i)
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
	print_state(i + 1, TAKE_A_FORK);
	pthread_mutex_lock(&g_data.fork[second]);
	print_state(i + 1, TAKE_A_FORK);
}

void		ft_eat(t_philo *philo, int i)
{
	size_t	start_eat;

	pthread_mutex_lock(&philo->mutex);
	philo->last_meal = print_state(i + 1, EAT);
	start_eat = philo->last_meal;
	pthread_mutex_unlock(&philo->mutex);
	while (get_timestamp() - start_eat < g_data.time[EAT])
		usleep(10);
	++(philo->nb_meal);
	pthread_mutex_unlock(&g_data.fork[i]);
	pthread_mutex_unlock(&g_data.fork[(i + 1) % g_data.nb_philo]);
	pthread_mutex_lock(&g_data.fed);
	if (philo_hungry(philo) == 0)
		++g_data.nb_fed;
	if (g_data.nb_fed == g_data.nb_philo && end_simul() == 0)
	{
		pthread_mutex_lock(&g_data.state);
		g_data.simul_state = STOP;
		pthread_mutex_unlock(&g_data.state);
		pthread_mutex_lock(&g_data.display);
		printf("All philosophers ate at least %d times\n", g_data.nb_meal_min);
		pthread_mutex_unlock(&g_data.display);
	}
	pthread_mutex_unlock(&g_data.fed);
}

void		ft_sleep(int i)
{
	size_t	time;

	time = print_state(i + 1, SLEEP);
	while (get_timestamp() - time < g_data.time[SLEEP])
		usleep(10);
	print_state(i + 1, THINK);
}
