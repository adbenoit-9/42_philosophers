/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:11:16 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/29 11:49:34 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	clean_forks(void)
{
	int	i;

	i = 0;
	while (i < g_data.nb_philo)
	{
		pthread_mutex_destroy(&g_data.fork[i]);
		pthread_mutex_destroy(&g_data.philo[i].sem);
		++i;
	}
	free(g_data.fork);
}

int			main(int ac, char **av)
{
	int ret;

	ret = ft_data_init(ac, av);
	if (ret == -1)
		write(1, "Arguments error.\n", 17);
	else if (ret == -2)
		write(1, "Malloc error.\n", 14);
	else
		simulation();
	clean_forks();
	pthread_mutex_destroy(&g_data.display);
	pthread_mutex_destroy(&g_data.state);
	pthread_mutex_destroy(&g_data.fed);
	free(g_data.philo);
	return (0);
}
