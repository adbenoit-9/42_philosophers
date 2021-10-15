/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:58:58 by adbenoit          #+#    #+#             */
/*   Updated: 2021/10/15 18:15:15 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

size_t	get_timestamp(void)
{
	size_t			time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000 - g_start_time;
	return (time);
}

static t_philo	*ft_philo_init(int n)
{
	t_philo	*philo;
	int		i;

	if (n == 0)
		return (NULL);
	philo = (t_philo *)malloc(sizeof(t_philo) * n);
	if (!philo)
		return (NULL);
	i = -1;
	while (++i < n)
	{
		philo[i].i = i;
		philo[i].nb_meal = 0;
		philo[i].last_meal = 0;
		philo[i].ifork[i % 2] = i;
		philo[i].ifork[1 - i % 2] = (i + 1) % g_data.nb_philo;
	}
	return (philo);
}

static int	ft_mutex_init(void)
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
	pthread_mutex_init(&g_data.start, NULL);
	return (0);
}

void	ft_time_init(char **av)
{
	g_data.time[DIED] = ft_atoli(av[2]);
	g_data.time[EAT] = ft_atoli(av[3]);
	g_data.time[SLEEP] = ft_atoli(av[4]);
}

int	ft_data_init(int ac, char **av)
{
	int	i;

	g_data.fork = NULL;
	g_data.philo = NULL;
	if (ac != 6 && ac != 5)
		return (-1);
	i = 1;
	while (av[i] && ft_isnumber(av[i]) == 1)
		++i;
	if (i != ac || ft_strlen(av[1]) > 18 || ft_strlen(av[2]) > 18
		|| ft_strlen(av[3]) > 18 || ft_strlen(av[4]) > 18
		|| ft_strlen(av[5]) > 18)
		return (-1);
	g_data.status = RUN;
	g_data.nb_philo = ft_atoli(av[1]);
	ft_time_init(av);
	g_data.nb_meal_min = -1;
	if (av[5])
		g_data.nb_meal_min = ft_atoli(av[5]);
	g_data.philo = ft_philo_init(g_data.nb_philo);
	if (!g_data.philo)
		return (-2);
	return (ft_mutex_init());
}
