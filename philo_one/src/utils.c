/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 18:04:05 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/12 23:48:31 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

long int	ft_atoli(const char *str)
{
        int             i;
        long int        num;
        int             neg;

        i = 0;
        neg = 1;
        num = 0;
        while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
                || str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
                ++i;
        if (str[i] == '-')
                neg = -1;
        if (str[i] == '-' || str[i] == '+')
                ++i;
        while (str[i] && str[i] >= '0' && str[i] <= '9')
        {
                num = num * 10 + (str[i] - 48);
                ++i;
        }
        num = num * neg;
        return (num);
}

int			ft_isnumber(char *str)
{
        int i;

        i = 0;
        while (str[i])
        {
                if (ft_isdigit(str[i]) == 0)
                        return (0);
                ++i;
        }
        return (1);
}

unsigned int	get_time(void)
{
	unsigned int	time;
	struct timeval	tv;

	tv.tv_sec = 0;
	tv.tv_usec = 0;
	gettimeofday(&tv, NULL);
	time = tv.tv_usec / 1000 - start_time;
	return (time);
}

void			display_message(pthread_mutex_t *m, int x, int state)
{
	unsigned int	time;

	// if (data.stop == 1)
	// 	return ;
	pthread_mutex_lock(m);
	time = get_time();
	if (state == -1)
	{
		printf("%ums %d has taken a fork\n", time, x);
		pthread_mutex_unlock(m);
		return ;
	}
	printf("%ums %d ", time, x);
	if (state == EAT)
		printf("is eating\n");
	else if (state == SLEEP)
		printf("is sleeping\n");
	else if (state == THINK)
		printf("is thinking\n");
	else if (state == DIE)
		printf("died\n");
	pthread_mutex_unlock(m);
}
