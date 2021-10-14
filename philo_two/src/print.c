/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 15:39:28 by adbenoit          #+#    #+#             */
/*   Updated: 2021/10/14 12:40:57 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static void	get_message(char *mess, int x, size_t time, char *str)
{
	char	*tmp;

	tmp = ft_uitoa(time);
	ft_strcat(mess, tmp);
	free(tmp);
	ft_strcat(mess, "ms ");
	tmp = ft_uitoa(x);
	ft_strcat(mess, tmp);
	free(tmp);
	ft_strcat(mess, " ");
	ft_strcat(mess, str);
}

void	print_action(int x, int action)
{
	size_t	time;
	char	mess[1000];

	sem_wait(g_data.display);
	mess[0] = 0;
	time = get_timestamp();
	if (action == TAKE_A_FORK)
		get_message(mess, x, time, "has taken a fork\n");
	else if (action == EAT)
		get_message(mess, x, time, "is eating\n");
	else if (action == SLEEP)
		get_message(mess, x, time, "is sleeping\n");
	else if (action == THINK)
		get_message(mess, x, time, "is thinking\n");
	else if (action == DIED)
		get_message(mess, x, time, "died\n");
	if (ft_stop() == 0)
		write(1, mess, ft_strlen(mess));
	if (action == DIED)
	{
		sem_wait(g_data.state);
		g_data.simul_state = STOP;
		sem_post(g_data.state);
	}
	sem_post(g_data.display);
}

int	print_in_thread(char *str)
{
	sem_wait(g_data.display);
	printf("%s", str);
	sem_post(g_data.display);
	return (0);
}
