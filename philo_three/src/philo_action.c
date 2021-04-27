/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 17:25:21 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/27 17:25:22 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void		ft_take_forks(t_philo *philo, int i)
{
	sem_wait(g_data.his_turn);
	sem_wait(g_data.fork);
	display_state(philo, i + 1, TAKE_A_FORK);
	sem_wait(g_data.fork);
	sem_post(g_data.his_turn);
	display_state(philo, i + 1, TAKE_A_FORK);
}

void		ft_eat(t_philo *philo, int i)
{
	size_t	start_eat;

	philo->state = EAT;
	philo->last_meal = display_state(philo, i + 1, EAT);
	start_eat = philo->last_meal;
	while (g_data.simul_state != STOP &&
	get_timestamp() - start_eat < g_data.time[EAT])
		usleep(10);
	++(philo->nb_meal);
	if (g_data.simul_state != STOP && philo->nb_meal == g_data.min_meal)
		sem_post(g_data.is_fed);
	sem_post(g_data.fork);
	sem_post(g_data.fork);
}

void		ft_sleep(t_philo *philo, int i)
{
	size_t	time;

	time = display_state(philo, i + 1, SLEEP);
	while (g_data.simul_state != STOP &&
	get_timestamp() - time < g_data.time[SLEEP])
		usleep(10);
	display_state(philo, i + 1, THINK);
}