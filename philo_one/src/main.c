/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:11:16 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/28 13:05:35 by adbenoit         ###   ########.fr       */
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
		++i;
	}
	free(g_data.fork);
}

int			main(int ac, char **av)
{
	int ret;

	ret = ft_data_init(ac, av);
	if (ret == -1)
		printf("Arguments error.\n");
	else if (ret == -2)
		printf("Malloc error.\n");
	else
	{
		simulation();
		clean_forks();
		pthread_mutex_destroy(&g_data.display);
	}
	free(g_data.philo);
	return (0);
}
