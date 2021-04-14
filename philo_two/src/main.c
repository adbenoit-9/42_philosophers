/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:11:16 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/14 14:48:43 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static void	clean_forks(void)
{
	// int	i;

	// i = 0;
	// while (i < g_data.n)
	// {
	// 	sem_close(&g_data.fork[i]);
	// 	++i;
	// }
	// free(g_data.fork);
	sem_close(g_data.fork);
	sem_unlink("fork");
}

int			main(int ac, char **av)
{
	int ret;

	ret = init_data(ac, av);
	if (ret == -1)
		printf("Arguments error.\n");
	else if (ret == -2)
		printf("Malloc error.\n");
	else
	{
		simulation();
		clean_forks();
		sem_close(g_data.sem);
		sem_close(g_data.sem1);
		sem_unlink("sem");
		sem_unlink("philo");
	}
	free(g_data.philo);
	return (0);
}
