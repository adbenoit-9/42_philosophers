/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 17:23:38 by adbenoit          #+#    #+#             */
/*   Updated: 2021/10/15 18:18:36 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

/* Returns 0 if the philosopher has eaten at least the number of times needed.
Otherwise returns 1 (is hungry). */

static int	philo_hungry(t_philo *philo)
{
	if (g_data.nb_meal_min == -1)
		return (1);
	if (philo->nb_meal == g_data.nb_meal_min)
		return (0);
	return (1);
}

/* the philosophers alternately take the left or right fork first. */

void	ft_take_forks(const t_philo philo, int i)
{
	pthread_mutex_lock(&g_data.fork[philo.ifork[0]]);
	print_action(i + 1, TAKE_A_FORK);
	pthread_mutex_lock(&g_data.fork[philo.ifork[1]]);
	print_action(i + 1, TAKE_A_FORK);
}

void	ft_eat(t_philo *philo, int i)
{
	size_t	start_eat;

	pthread_mutex_lock(&philo->mutex);
	philo->last_meal = get_timestamp();
	print_action(i + 1, EAT);
	start_eat = philo->last_meal;
	pthread_mutex_unlock(&philo->mutex);
	while (get_timestamp() - start_eat < g_data.time[EAT]
		&& get_status() == RUN)
		usleep(500);
	++(philo->nb_meal);
	pthread_mutex_unlock(&g_data.fork[i]);
	pthread_mutex_unlock(&g_data.fork[(i + 1) % g_data.nb_philo]);
	pthread_mutex_lock(&g_data.fed);
	if (philo_hungry(philo) == 0)
		++g_data.nb_fed;
	if (g_data.nb_fed == g_data.nb_philo && get_status() == RUN)
	{
		set_status(STOP);
		pthread_mutex_lock(&g_data.display);
		printf("All philosophers ate at least %d times\n", g_data.nb_meal_min);
		pthread_mutex_unlock(&g_data.display);
	}
	pthread_mutex_unlock(&g_data.fed);
}

void	ft_sleep(int i)
{
	size_t	time;

	time = get_timestamp();
	print_action(i + 1, SLEEP);
	while (get_timestamp() - time < g_data.time[SLEEP] && get_status() == RUN)
		usleep(500);
}
