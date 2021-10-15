/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:11:16 by adbenoit          #+#    #+#             */
/*   Updated: 2021/10/15 18:18:12 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	ft_mutex_clean(void)
{
	int	i;

	i = 0;
	while (i < g_data.nb_philo)
	{
		pthread_mutex_destroy(&g_data.fork[i]);
		pthread_mutex_destroy(&g_data.philo[i].mutex);
		++i;
	}
	free(g_data.fork);
	pthread_mutex_destroy(&g_data.display);
	pthread_mutex_destroy(&g_data.state);
	pthread_mutex_destroy(&g_data.fed);
}

int	main(int ac, char **av)
{
	int	ret;

	ret = ft_data_init(ac, av);
	if (ret == -1)
		write(1, "Arguments error.\n", 17);
	else if (ret == -2)
		write(1, "Malloc error.\n", 14);
	else
		simulation();
	ft_mutex_clean();
	free(g_data.philo);
	return (0);
}
