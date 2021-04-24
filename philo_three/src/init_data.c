/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 19:58:25 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/24 16:24:43 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static t_philo	*init_philo(int n)
{
	t_philo	*philo;
	int		i;

	if (n == 0)
		return (NULL);
	philo = (t_philo *)malloc(sizeof(t_philo) * n);
	if (!philo)
		return (NULL);
	i = 0;
	while (i < n)
	{
		philo[i].i = i;
		philo[i].state = -1;
		philo[i].nb_meal = 0;
		philo[i].last_meal = 0;
		philo[i].pid = 0;
		++i;
	}
	return (philo);
}

static int		init_sem(void)
{
	sem_unlink("wait");
	sem_unlink("fork");
	sem_unlink("display");
	sem_unlink("eat");
	sem_unlink("dead");
	g_data.fork = sem_open("fork", O_CREAT, 0, g_data.nb_philo / 2);
	if (!g_data.fork)
		return (-2);
	g_data.display = sem_open("display", O_CREAT, 0, 1);
	g_data.wait_all = sem_open("wait", O_CREAT, 0, 0);
	g_data.is_fed = sem_open("eat", O_CREAT, 0, 0);
	g_data.is_dead = sem_open("dead", O_CREAT, 0, 0);
	if (!g_data.display)
	{
		sem_close(g_data.fork);
		return (-2);
	}
	return (0);
}

int				init_data(int ac, char **av)
{
	int i;

	g_data.fork = NULL;
	g_data.philo = NULL;
	if (ac != 6 && ac != 5)
		return (-1);
	i = 1;
	while (av[i] && ft_isnumber(av[i]) == 1)
		++i;
	if (i != ac)
		return (-1);
	g_data.simul_state = RUN;
	g_data.nb_philo = ft_atoli(av[1]);
	g_data.min_meal = -1;
	g_data.time[DIE] = ft_atoli(av[2]);
	g_data.time[EAT] = ft_atoli(av[3]);
	g_data.time[SLEEP] = ft_atoli(av[4]);
	if (av[5])
		g_data.min_meal = ft_atoli(av[5]);
	g_data.philo = init_philo(g_data.nb_philo);
	if (!g_data.philo)
		return (-2);
	return (init_sem());
}
