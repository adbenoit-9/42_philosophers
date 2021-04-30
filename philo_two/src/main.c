/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:11:16 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/30 15:49:59 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static void	ft_sem_clean(void)
{
	int	i;

	sem_close(g_data.fork);
	sem_close(g_data.display);
	sem_close(g_data.his_turn);
	sem_close(g_data.state);
	sem_close(g_data.fed);
	i = 0;
	while (i < g_data.nb_philo)
	{
		sem_close(g_data.philo[i].sem);
		++i;
	}
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
		simulation();
	ft_sem_clean();
	free(g_data.philo);
	return (0);
}
