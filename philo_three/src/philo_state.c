/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 14:54:43 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/27 17:43:32 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	ft_isalive(t_philo *philo)
{
	long int time;

	time = get_timestamp() - philo->last_meal;
	while ((time < (long int)g_data.time[DIE] || philo->state == EAT)
	&& g_data.simul_state != STOP)
	{
		usleep(10);
		time = get_timestamp() - philo->last_meal;
	}
	g_data.simul_state = STOP;
	display_state(philo, philo->i + 1, DIE);
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
			g_data.simul_state = END;
			ft_quit(END, NULL);
			return ;
		}
	}
}
