/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 17:23:38 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/28 13:47:17 by adbenoit         ###   ########.fr       */
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

void		ft_eat(t_philo *philo, int i)
{
	size_t	start_eat;

	philo->state = EAT;
	philo->last_meal = display_state(philo, i + 1, EAT);
	start_eat = philo->last_meal;
	while (g_data.simul_state == RUN &&
	get_timestamp() - start_eat < g_data.time[EAT])
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

void		ft_sleep(t_philo *philo, int i)
{
	size_t	time;

	time = display_state(philo, i + 1, SLEEP);
	while (g_data.simul_state == RUN &&
	get_timestamp() - time < g_data.time[SLEEP])
		usleep(10);
}
