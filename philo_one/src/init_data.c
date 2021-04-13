/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:50:25 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/07 17:40:47 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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

static int		init_mutex(void)
{
	int	i;

	data.fork = malloc(sizeof(pthread_mutex_t) * data.n);
	if (!data.fork)
		return (-1);
	pthread_mutex_init(&data.mutex, NULL);
	i = 0;
	while (i < data.n)
	{
		pthread_mutex_init(&data.fork[i], NULL);
		pthread_mutex_init(&data.philo[i].mutex, NULL);
		++i;
	}
	return (0);
}

int 			init_data(char **av)
{
	int i;

	if (ft_isnumber(av[1]) == 0)
		return (-1);
	data.n = ft_atoli(av[1]);
	data.n_eat = -1;
	i = 0;
	while (i < 3)
	{
		if (ft_isnumber(av[i + 2]) == 0)
			return (-1);
		data.time[i] = ft_atoli(av[i + 2]);
		++i;
	}
	if (av[5])
	{
		if (ft_isnumber(av[5]) == 0)
			return (-1);
		data.n_eat = ft_atoli(av[5]);
	}
	data.philo = init_philo(data.n);
	data.stop = 0;
	if (!data.philo || init_mutex() == -1)
	{
		free(data.philo);
		return (-1);
	}
	return (0);
}