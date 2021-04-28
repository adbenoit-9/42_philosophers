/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 20:00:30 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/28 13:10:16 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void	routine(t_philo *philo)
{
	int				i;
	pthread_t		t;
	struct timeval	tv;

	sem_wait(g_data.wait_all);
	if (gettimeofday(&tv, NULL) == -1)
		ft_quit(-1, "Get Time Error.");
	g_start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	i = philo->i;
	if (pthread_create(&t, NULL, (void *)ft_isalive, philo) != 0)
		ft_quit(-1, "Thread Error.");
	pthread_detach(t);
	while (1)
	{
		ft_take_forks(philo, i);
		ft_eat(philo, i);
		ft_sleep(philo, i);
	}
}

static int	ft_philo_launch(int *pid)
{
	int	i;

	*pid = 1;
	i = 0;
	while (i < g_data.nb_philo && *pid > 0)
	{
		*pid = fork();
		g_data.philo[i].pid = *pid;
		if (*pid == -1)
			return (-1);
		++i;
	}
	if (*pid == 0)
		routine(&g_data.philo[i - 1]);
	return (0);
}

static void	ft_philo_wait(int pid)
{
	int	i;
	int	status;

	usleep(100000);
	i = 0;
	while (i < g_data.nb_philo && pid > 0)
	{
		sem_post(g_data.wait_all);
		++i;
	}
	i = 0;
	while (i < g_data.nb_philo)
	{
		waitpid(-1, &status, 0);
		++i;
	}
	return ;
}

int			simulation(void)
{
	pid_t			pid;
	pthread_t		t;
	pthread_t		t1;

	if (pthread_create(&t, NULL, (void *)is_someone_dead, NULL) != 0)
		ft_quit(-1, "Thread Error.");
	pthread_detach(t);
	if (pthread_create(&t1, NULL, (void *)is_someone_hungry, NULL) != 0)
		ft_quit(-1, "Thread Error.");
	pthread_detach(t1);
	if (ft_philo_launch(&pid) == -1)
		ft_quit(-1, "Fork Error.");
	ft_philo_wait(pid);
	return (0);
}
