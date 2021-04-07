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

t_philo				*init_philo(int n)
{
	t_philo	*philo;
	t_philo	*tmp;
	int		i;

	if (n == 0)
		return (NULL);
	philo = new_philo(0);
	if (!philo)
		return (NULL);
	tmp = philo->next;
	i = 0;
	while (i < n)
	{
		tmp = new_philo(i);
		if (!tmp)
		{
			clear_philo(philo);
			return (NULL);
		}
		++i;
	}
	return (philo);
	
}

int 			init_data(char **av, t_data *data)
{
	int i;

	if (!data)
		return (-1);
	if (ft_isnumber(av[1]) == 0)
		return (-1);
	data->n = ft_atoli(av[1]);
	data->n_eat = -1;
	i = 0;
	while (i < 3)
	{
		if (ft_isnumber(av[i + 2]) == 0)
			return (-1);
		data->time[i] = ft_atoli(av[i + 2]);
		++i;
	}
	if (av[5])
	{
		if (ft_isnumber(av[5]) == 0)
			return (-1);
		data->n_eat = ft_atoli(av[5]);
	}
	data->philo = init_philo(data->n);
	if (!data->philo)
		return (-1);
	return (0);
}