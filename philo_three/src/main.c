/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:11:16 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/28 13:48:07 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	main(int ac, char **av)
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
		return (0);
	}
	ft_sem_clean();
	free(g_data.philo);
	return (0);
}
