/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 19:58:25 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/13 22:07:33 by adbenoit         ###   ########.fr       */
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
		philo[i].i = i + 1;
		philo[i].state = -1;
		philo[i].n_eat = 0;
		philo[i].i = i;
		philo[i].last_eat = 0;
		++i;
	}
	return (philo);
}

static int		init_forks(void)
{
	int	i;

	g_data.fork = malloc(sizeof(pthread_mutex_t) * g_data.n);
	if (!g_data.fork)
		return (-2);
	i = 0;
	while (i < g_data.n)
	{
		pthread_mutex_init(&g_data.fork[i], NULL);
		++i;
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
	g_data.n = ft_atoli(av[1]);
	g_data.n_eat = -1;
	g_data.time[DIE] = ft_atoli(av[2]);
	g_data.time[EAT] = ft_atoli(av[3]);
	g_data.time[SLEEP] = ft_atoli(av[4]);
	if (av[5])
		g_data.n_eat = ft_atoli(av[5]);
	g_data.philo = init_philo(g_data.n);
	if (!g_data.philo)
		return (-2);
	pthread_mutex_init(&g_data.mutex, NULL);
	return (init_forks());
}
