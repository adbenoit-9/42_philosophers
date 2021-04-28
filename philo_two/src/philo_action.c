/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 17:24:31 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/28 16:12:51 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static int	philo_hungry(t_philo *philo)
{
	if (g_data.min_meal == -1 || philo->state == DIE)
		return (1);
	if (philo->nb_meal == g_data.min_meal)
		return (0);
	return (1);
}

void		ft_take_forks(t_philo *philo, int i)
{
	sem_wait(g_data.his_turn);
	sem_wait(g_data.fork);
	print_state(philo, i + 1, TAKE_A_FORK);
	sem_wait(g_data.fork);
	print_state(philo, i + 1, TAKE_A_FORK);
	sem_post(g_data.his_turn);
}

void		ft_eat(t_philo *philo, int i)
{
	size_t	start_eat;

	philo->state = EAT;
	start_eat = print_state(philo, i + 1, EAT);
	philo->last_meal = get_timestamp();
	while (g_data.simul_state == RUN &&
	get_timestamp() - start_eat < g_data.time[EAT])
		usleep(10);
	++(philo->nb_meal);
	sem_post(g_data.fork);
	sem_post(g_data.fork);
	sem_wait(g_data.display);
	if (philo_hungry(philo) == 0)
		++g_data.nb_fed;
	if (g_data.nb_fed == g_data.nb_philo && g_data.simul_state == RUN)
	{
		g_data.simul_state = END;
		printf("All philosophers ate at least %d times\n", g_data.min_meal);
	}
	sem_post(g_data.display);
}

void		ft_sleep(t_philo *philo, int i)
{
	size_t	time;

	time = print_state(philo, i + 1, SLEEP);
	while (g_data.simul_state == RUN &&
	get_timestamp() - time < g_data.time[SLEEP])
		usleep(10);
	print_state(philo, i + 1, THINK);
}
