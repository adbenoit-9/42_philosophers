/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 14:54:43 by adbenoit          #+#    #+#             */
/*   Updated: 2021/05/05 19:47:41 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	ft_isalive(t_philo *philo)
{
	long int time;

	while (1)
	{
		sem_wait(philo->sem);
		time = get_timestamp() - philo->last_meal;
		if (time > (long int)g_data.time[DIED])
			print_action(philo->i + 1, DIED);
		sem_post(philo->sem);
		usleep(10);
	}
}

void	is_someone_dead(void)
{
	sem_wait(g_data.is_dead);
	ft_quit(STOP, NULL);
}

void	is_someone_hungry(void)
{
	while (1)
	{
		sem_wait(g_data.is_fed);
		++g_data.nb_fed;
		if (g_data.nb_fed == g_data.nb_philo)
		{
			g_data.simul_state = STOP;
			ft_quit(END, NULL);
			return ;
		}
	}
}
