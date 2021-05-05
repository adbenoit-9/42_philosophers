/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:58:58 by adbenoit          #+#    #+#             */
/*   Updated: 2021/05/05 19:42:29 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static t_philo	*ft_philo_init(int n)
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
		philo[i].nb_meal = 0;
		philo[i].i = i;
		philo[i].last_meal = 0;
		++i;
	}
	return (philo);
}

static int		ft_mutex_init(void)
{
	int	i;

	g_data.fork = malloc(sizeof(pthread_mutex_t) * g_data.nb_philo);
	if (!g_data.fork)
		return (-2);
	i = 0;
	while (i < g_data.nb_philo)
	{
		pthread_mutex_init(&g_data.fork[i], NULL);
		pthread_mutex_init(&g_data.philo[i].mutex, NULL);
		++i;
	}
	pthread_mutex_init(&g_data.display, NULL);
	pthread_mutex_init(&g_data.state, NULL);
	pthread_mutex_init(&g_data.fed, NULL);
	return (0);
}

int				ft_data_init(int ac, char **av)
{
	int i;

	g_data.fork = NULL;
	g_data.philo = NULL;
	if (ac != 6 && ac != 5)
		return (-1);
	i = 1;
	while (av[i] && ft_isnumber(av[i]) == 1)
		++i;
	if (i != ac || ft_strlen(av[1]) > 18 || ft_strlen(av[2]) > 18 ||
	ft_strlen(av[3]) > 18 || ft_strlen(av[4]) > 18 || ft_strlen(av[5]) > 18)
		return (-1);
	g_data.simul_state = RUN;
	g_data.nb_philo = ft_atoli(av[1]);
	g_data.nb_run = 0;
	g_data.nb_meal_min = -1;
	g_data.time[DIED] = ft_atoli(av[2]);
	g_data.time[EAT] = ft_atoli(av[3]);
	g_data.time[SLEEP] = ft_atoli(av[4]);
	if (av[5])
		g_data.nb_meal_min = ft_atoli(av[5]);
	g_data.philo = ft_philo_init(g_data.nb_philo);
	if (!g_data.philo)
		return (-2);
	return (ft_mutex_init());
}
