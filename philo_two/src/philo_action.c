/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 17:24:31 by adbenoit          #+#    #+#             */
/*   Updated: 2021/10/15 18:31:20 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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

/* The philosophers take their forks in turn. */

void	ft_take_forks(int i)
{
	sem_wait(g_data.his_turn);
	sem_wait(g_data.fork);
	print_action(i + 1, TAKE_A_FORK);
	sem_wait(g_data.fork);
	print_action(i + 1, TAKE_A_FORK);
	sem_post(g_data.his_turn);
}

void	ft_eat(t_philo *philo, int i)
{
	size_t	start_eat;

	sem_wait(philo->sem);
	start_eat = get_timestamp();
	print_action(i + 1, EAT);
	philo->last_meal = start_eat;
	sem_post(philo->sem);
	while (get_timestamp() - start_eat < g_data.time[EAT]
		&& get_status() == RUN)
		usleep(10);
	++(philo->nb_meal);
	sem_post(g_data.fork);
	sem_post(g_data.fork);
	sem_wait(g_data.fed);
	if (philo_hungry(philo) == 0)
		++g_data.nb_fed;
	if (g_data.nb_fed == g_data.nb_philo && get_status() == 0)
	{
		set_status(STOP);
		sem_wait(g_data.display);
		printf("All philosophers ate at least %d times\n", g_data.nb_meal_min);
		sem_post(g_data.display);
	}
	sem_post(g_data.fed);
}

void	ft_sleep(int i)
{
	size_t	time;

	time = get_timestamp();
	print_action(i + 1, SLEEP);
	while (get_timestamp() - time < g_data.time[SLEEP] && get_status() == RUN)
		usleep(10);
}
