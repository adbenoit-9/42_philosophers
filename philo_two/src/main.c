/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:11:16 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/25 13:20:30 by adbenoit         ###   ########.fr       */
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
		sem_close(g_data.his_turn);
	}
	free(g_data.philo);
	return (0);
}
