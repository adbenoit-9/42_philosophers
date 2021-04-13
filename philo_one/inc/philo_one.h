/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:11:58 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/13 15:48:39 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
#define PHILO_ONE_H

# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
#include <string.h>
# include <errno.h>

# define DIE 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define TAKE_A_FORK 4

unsigned int	start_time;

typedef struct	s_philo
{
	pthread_t			t;
	int				i;
	pthread_mutex_t	mutex;
	unsigned int	last_eat;
	int				n_eat;
	int				state;
}				t_philo;

typedef	struct	s_data
{
	unsigned int	time[3];
	pthread_mutex_t	*fork;
	pthread_mutex_t mutex;
	int				n_eat;
	int				done;
	int				n;
	int				stop;
	t_philo			*philo;
}				t_data;

t_data			data;

int				init_data(char **av);

int				ft_isnumber(char *str);
long int		ft_atoli(const char *str);

int				start_philo(void);
unsigned int	display_message(pthread_mutex_t *m, int x, int state, t_philo *philo);
unsigned int	get_time(void);

void			ft_eat(t_philo *philo, int i);
void			ft_take_forks(t_philo *philo, int i);
void			ft_sleep(t_philo *philo, int i);

int				philo_hungry(t_philo *philo);

#endif
