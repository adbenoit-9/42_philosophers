/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 17:00:15 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/30 17:00:16 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int	ft_kill_process(char *error)
{
	int i;

	if (error)
	{
		sem_wait(g_data.display);
		printf("%s\n", error);
		sem_wait(g_data.display);
	}
	i = 0;
	while (i < g_data.nb_philo)
	{
		if (g_data.philo[i].pid != 0)
			kill(g_data.philo[i].pid, SIGINT);
		++i;
	}
	return (0);
}

static void	ft_sem_clean(void)
{
	int	i;

	sem_close(g_data.fork);
	sem_close(g_data.display);
	sem_close(g_data.is_fed);
	sem_close(g_data.is_dead);
	sem_close(g_data.wait_all);
	sem_close(g_data.his_turn);
	i = 0;
	while (i < g_data.nb_philo)
	{
		sem_close(g_data.philo[i].sem);
		++i;
	}
}

void		ft_quit(int status, char *error)
{
	ft_kill_process(error);
	if (status == END)
		printf("All philosophers ate at least %d times\n", g_data.nb_meal_min);
	ft_sem_clean();
	free(g_data.philo);
	kill(0, SIGINT);
}
