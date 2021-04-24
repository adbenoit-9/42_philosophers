/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:11:16 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/24 14:54:19 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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
		sem_close(g_data.fork);
		sem_close(g_data.display);
		sem_close(g_data.is_dead);
		sem_close(g_data.is_fed);
		sem_close(g_data.wait_all);
	}
	free(g_data.philo);
	return (0);
}
