/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 15:39:28 by adbenoit          #+#    #+#             */
/*   Updated: 2021/10/15 18:13:52 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	print_action(int x, int action)
{
	size_t		time;
	static char	*mess[5] = {"died", "is eating", "is sleeping", "is thinking",
			"has taken a fork"};

	pthread_mutex_lock(&g_data.display);
	time = get_timestamp();
	if (get_status() == RUN)
		printf("%zums %d %s\n", time, x, mess[action]);
	if (action == DIED)
		set_status(STOP);
	pthread_mutex_unlock(&g_data.display);
}

int	print_in_thread(char *str)
{
	pthread_mutex_lock(&g_data.display);
	printf("%s", str);
	pthread_mutex_unlock(&g_data.display);
	return (0);
}
