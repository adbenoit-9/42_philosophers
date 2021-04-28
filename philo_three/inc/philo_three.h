/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 22:07:02 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/28 17:19:36 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

# define DIE 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define TAKE_A_FORK 4

# define RUN 0
# define END 1
# define STOP 2

size_t	g_start_time;

typedef struct	s_philo
{
	pid_t	pid;
	int		i;
	size_t	last_meal;
	int		nb_meal;
	int		state;
}				t_philo;

typedef	struct	s_data
{
	size_t		time[3];
	sem_t		*fork;
	sem_t		*display;
	sem_t		*is_dead;
	sem_t		*is_fed;
	sem_t		*wait_all;
	sem_t		*his_turn;
	int			min_meal;
	int			nb_fed;
	int			nb_philo;
	int			simul_state;
	t_philo		*philo;
}				t_data;

t_data			g_data;

int				ft_isnumber(char *str);
long int		ft_atoli(const char *str);
size_t			get_timestamp(void);

int				ft_data_init(int ac, char **av);
int				simulation(void);
size_t			print_state(t_philo *philo, int x, int state);
void			ft_eat(t_philo *philo, int i);
void			ft_take_forks(t_philo *philo, int i);
void			ft_sleep(t_philo *philo, int i);
void			ft_isalive(t_philo *philo);
void			is_someone_dead(void);
void			is_someone_hungry(void);
void			ft_quit(int status, char *error);
int				print_in_thread(char *str);
#endif
