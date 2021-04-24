/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:11:58 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/24 16:24:43 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

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
	pthread_t	t;
	int			i;
	size_t		last_meal;
	int			nb_meal;
	int			state;
}				t_philo;

typedef	struct	s_data
{
	t_philo			*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t display;
	size_t			time[3];
	int				min_meal;
	int				nb_fed;
	int				nb_philo;
	int				simul_state;
}				t_data;

t_data	g_data;

int				ft_isnumber(char *str);
long int		ft_atoli(const char *str);
size_t			current_timestamp(void);

int				init_data(int ac, char **av);
int				simulation(void);
size_t			philo_state(t_philo *philo, int x, int state);
void			ft_eat(t_philo *philo, int i);
void			ft_take_forks(t_philo *philo, int i);
void			ft_sleep(t_philo *philo, int i);

#endif
