/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_health.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 14:54:43 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/27 14:07:34 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	ft_isalive(t_philo *philo)
{
	long int time;

	time = current_timestamp() - philo->last_meal;
	while ((time <= (long int)g_data.time[DIE] || philo->state == EAT)
	&& g_data.simul_state != STOP)
	{
		usleep(10);
		time = current_timestamp() - philo->last_meal;
	}
	g_data.simul_state = STOP;
	philo_state(philo, philo->i + 1, DIE);
}

void	handle_death(void)
{
	sem_wait(g_data.is_dead);
	ft_quit_simul(STOP, NULL);
}

void	handle_meal(void)
{
	while (1)
	{
		sem_wait(g_data.is_fed);
		++g_data.nb_fed;
		if (g_data.nb_fed == g_data.nb_philo)
		{
			sem_wait(g_data.display);
			g_data.simul_state = END;
			ft_quit_simul(END, NULL);
			return ;
		}
	}
}
