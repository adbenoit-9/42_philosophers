/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 20:00:30 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/14 19:13:36 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void	checkup(t_philo *philo)
{
	size_t	time;

	time = get_time();
	while ((get_time() - philo->last_eat <= g_data.time[DIE] ||
	philo->state == EAT) && g_data.simul_state == RUN)
		usleep(10);
	philo_state(philo, philo->i + 1, DIE);
}

static void	routine(t_philo *philo)
{
	int			i;
	pthread_t	t;

	if (g_data.simul_state > 0)
		return ;
	i = philo->i;
	if (pthread_create(&t, NULL, (void *)checkup, philo) != 0)
		return ((void)printf("Thread Error.\n"));
	while (g_data.simul_state == RUN)
	{
		ft_take_forks(philo, i);
		ft_eat(philo, i);
		ft_sleep(philo, i);
		philo_state(philo, i + 1, THINK);
	}
	exit(0);
}

void		kill_process(int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		kill(g_data.philo[i].pid, 0);
		++i;
	}
}

int			simulation(void)
{
	int				i;
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (printf("Get Time Error.\n"));
	g_start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	i = 0;
	while (i < g_data.n)
	{
		g_data.philo[i].pid = fork();
		if (g_data.philo[i].pid == -1)
			return (printf("Fork Error.\n"));
		waitpid(g_data.philo[i].pid, NULL, 0);
		if (g_data.philo[i].pid == 0)
		{
			g_start_time += get_time();
			routine(&g_data.philo[i]);
		}
		++i;
	}

	i = 0;
	while (i < g_data.n)
	{
		// waitpid(g_data.philo[i].pid, NULL, 0);
		++i;
	}
	return (0);
}
