/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 20:00:30 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/21 18:23:09 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void	ft_isalive(t_philo *philo)
{
	size_t	time;

	time = get_time();
	while ((get_time() - philo->last_eat <= g_data.time[DIE] ||
	philo->state == EAT) && g_data.simul_state != STOP)
		usleep(10);
	philo_state(philo, philo->i + 1, DIE);
}

static void	routine(t_philo *philo)
{
	int			i;
	pthread_t	t;

	if (g_data.simul_state > 0)
		exit(g_data.simul_state) ;
	i = philo->i;
	if (pthread_create(&t, NULL, (void *)ft_isalive, philo) != 0)
	{
		sem_wait(g_data.sem);
		printf("Thread Error.\n");
		sem_post(g_data.sem);
		exit(-1);
	}
	while (g_data.simul_state == RUN)
	{
		ft_take_forks(philo, i);
		ft_eat(philo, i);
		ft_sleep(philo, i);
		philo_state(philo, i + 1, THINK);
	}
	exit(g_data.simul_state);
}

void		kill_process(int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		kill(g_data.philo[i].pid, SIGINT);
		++i;
	}
}

void		ft_isdone(void)
{
	int status;
	// printf("All philosophers ate at least %d times\n", g_data.n_eat);
	int i = 0;
	sem_wait(g_data.dead);
	while (i < g_data.n)
	{
		sem_wait(g_data.dead);
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == END)
		{
			printf("All philosophers ate at least %d times\n", g_data.n_eat);
			exit (0);
		}
		else if (WEXITSTATUS(status) == STOP)
		{
			printf("dead\n");
			return ;
		}
		++i;
	}
	sem_post(g_data.dead);
}

int			simulation(void)
{
	int				i;
	struct timeval	tv;
	// int				status;
	// pthread_t		t;

	// pthread_create(&t, NULL, (void *)ft_isdone, NULL);
	i = 0;
	while (i < g_data.n)
	{
		g_data.philo[i].pid = fork();
		if (gettimeofday(&tv, NULL) == -1)
			return (printf("Get Time Error.\n"));
		g_start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
		sem_post(g_data.wait_all);
		if (g_data.philo[i].pid == -1)
			return (printf("Fork Error.\n"));
		if (g_data.philo[i].pid == 0)
		{
			routine(&g_data.philo[i]);
		}
		++i;
		// usleep(100);
	}
	ft_isdone();
	kill_process(g_data.n);
	return (0);
}
