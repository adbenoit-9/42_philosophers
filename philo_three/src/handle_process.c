/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 14:39:53 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/24 16:20:09 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	    ft_kill_process(char *error)
{
	int i;

	if (error)
	{
		sem_wait(g_data.display);
		printf("%s\n", error);
		sem_wait(g_data.display);
	}
	i = 0;
	while (i < g_data.nb_philo)
	{
		if (g_data.philo[i].pid != 0)
			kill(g_data.philo[i].pid, SIGINT);
		++i;
	}
	return (0);
}
