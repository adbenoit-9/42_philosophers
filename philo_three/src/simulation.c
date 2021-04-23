/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 20:00:30 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/23 18:06:00 by adbenoit         ###   ########.fr       */
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
	if (philo->state == TAKE_A_FORK)
		sem_post(g_data.fork);
	philo_state(philo, philo->i + 1, DIE);
}

void		ft_isdone(void)
 {
 	int i;
 	int status;

 	i = 0;
 	while (i < g_data.n)
 	{
 		waitpid(-1, &status, 0);
 		++i;
 	}
 	return ;
 }

 void		ft_dead(void)
 {
	int	i;
	
	sem_wait(g_data.dead);
	i = 0;
	while (i < g_data.n)
	{
		kill(g_data.philo[i].pid, SIGINT);
		++i;
	}
	exit(0);
 }

 void	ft_done_eat(void)
 {
	int	i;

	sem_wait(g_data.done_eat);
	++g_data.n_done_eat;
	if (g_data.n_done_eat == g_data.n)
		g_data.simul_state = END;
	i = 0;
	while (i < g_data.n)
	{
		kill(g_data.philo[i].pid, SIGINT);
		++i;
	}
	printf("All philosophers ate at least %d times\n", g_data.n_eat);
 }

void	routine(t_philo *philo)
{
	int			i;
	pthread_t	t;

	if (g_data.simul_state == STOP)
		exit(STOP);
	i = philo->i;
	if (pthread_create(&t, NULL, (void *)ft_isalive, philo) != 0)
	{
		sem_wait(g_data.sem);
		printf("Thread Error.\n");
		sem_post(g_data.sem);
		exit(-1);
	}
	while (g_data.simul_state != END)
	{
		ft_take_forks(philo, i);
		ft_eat(philo, i);
		ft_sleep(philo, i);
	}
	exit(END);
}

int			simulation(void)
{
	int				i;
	struct timeval	tv;
	pid_t			pid;
	pthread_t		t;
	pthread_t		t1;

	if (gettimeofday(&tv, NULL) == -1)
		return (printf("Get Time Error.\n"));
	g_start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	if (pthread_create(&t, NULL, (void *)ft_dead, NULL) != 0)
		return (printf("Thread Error.\n"));
	if (pthread_create(&t1, NULL, (void *)ft_done_eat, NULL) != 0)
		return (printf("Thread Error.\n"));
	i = 0;
	pid = 1;
	while (i < g_data.n && pid > 0)
	{
		pid = fork();
		g_data.philo[i].pid = pid;
		if (pid == -1)
			return (printf("Fork Error.\n"));
		++i;
	}
	if (pid == 0)
	{
		sem_wait(g_data.wait_all);
		if (gettimeofday(&tv, NULL) == -1)
			return (printf("Get Time Error.\n"));
		g_start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
		routine(&g_data.philo[i - 1]);
	}
	usleep(100000);
	i = 0;
	while (i < g_data.n && pid > 0)
	{
		sem_post(g_data.wait_all);
		++i;
	}
	ft_isdone();
	return (0);
}
