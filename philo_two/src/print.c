/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:10:35 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/28 13:27:42 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

size_t		print_state(int x, int state)
{
	size_t	time;

	sem_wait(g_data.display);
	if (end_simul() == 1)
	{
		sem_post(g_data.display);
		return (0);
	}
	time = get_timestamp();
	if (state == TAKE_A_FORK)
		printf("%zums %d has taken a fork\n", time, x);
	else if (state == EAT)
		printf("%zums %d is eating\n", time, x);
	else if (state == SLEEP)
		printf("%zums %d is sleeping\n", time, x);
	else if (state == THINK)
		printf("%zums %d is thinking\n", time, x);
	else if (state == DIE)
	{
		sem_wait(g_data.state);
		g_data.simul_state = STOP;
		sem_post(g_data.state);
		printf("%zums %d die\n", time, x);
	}
	sem_post(g_data.display);
	return (time);
}

int		print_in_thread(char *str)
{
	sem_wait(g_data.display);
	printf("%s", str);
	sem_post(g_data.display);
	return (0);
}
