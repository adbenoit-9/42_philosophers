/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 20:00:30 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/14 18:01:36 by adbenoit         ###   ########.fr       */
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
	printf("end\n");
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
	// int				ret;
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (printf("Get Time Error.\n"));
	// g_start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	i = 0;
	g_data.philo[i].pid = fork();
	// g_start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	waitpid(g_data.philo[i].pid, NULL, 0);
	if (g_data.philo[i].pid == 0)
		{
			// exit(0);
			// printf("son\n");
			g_start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
			routine(&g_data.philo[i]);
		}
	// while (i < g_data.n)
	// {
	// 	g_data.philo[i].pid = fork();
	// 	if (g_data.philo[i].pid == -1)
	// 		return (printf("Fork Error.\n"));
	// 	if (g_data.philo[i].pid == 0)
	// 	{
	// 		// exit(0);
	// 		printf("son\n");
	// 		routine(&g_data.philo[i]);
	// 	}
	// 	printf("pid = %d\n", g_data.philo[i].pid);
	// 	ret = waitpid(g_data.philo[i].pid, NULL, 0);
	// 	printf("ret = %d\n", ret);
	// 	++i;
	// }

	// i = 0;
	// while (i < g_data.n)
	// {
	// 	printf("test\n");
	// 	// printf("pid = %d\n", g_data.philo[i].pid);
	// 	ret = waitpid(g_data.philo[i].pid, NULL, 0);
	// 	printf("ret = %d\n", ret);
	// 	if (g_data.philo[i].pid == 0)
	// 		printf("soooon");
	// 	++i;
	// }
	// printf("???\n");
	// kill_process(i);
	return (0);
}
