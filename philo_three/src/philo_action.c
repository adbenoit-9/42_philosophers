/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 17:25:21 by adbenoit          #+#    #+#             */
/*   Updated: 2021/05/05 19:47:41 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void		ft_take_forks(int i)
{
	sem_wait(g_data.his_turn);
	sem_wait(g_data.fork);
	print_action(i + 1, TAKE_A_FORK);
	sem_wait(g_data.fork);
	sem_post(g_data.his_turn);
	print_action(i + 1, TAKE_A_FORK);
}

void		ft_eat(t_philo *philo, int i)
{
	size_t	start_eat;

	start_eat = get_timestamp();
	sem_wait(philo->sem);
	philo->last_meal = start_eat;
	sem_post(philo->sem);
	print_action(i + 1, EAT);
	while (get_timestamp() - start_eat < g_data.time[EAT])
		usleep(10);
	++(philo->nb_meal);
	if (g_data.simul_state == RUN && philo->nb_meal == g_data.nb_meal_min)
		sem_post(g_data.is_fed);
	sem_post(g_data.fork);
	sem_post(g_data.fork);
}

void		ft_sleep(int i)
{
	size_t	time;

	time = get_timestamp();
	print_action(i + 1, SLEEP);
	while (get_timestamp() - time < g_data.time[SLEEP])
		usleep(10);
	print_action(i + 1, THINK);
}
