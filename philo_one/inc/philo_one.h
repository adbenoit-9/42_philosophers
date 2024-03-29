/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:11:58 by adbenoit          #+#    #+#             */
/*   Updated: 2021/10/15 18:15:34 by adbenoit         ###   ########.fr       */
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

# define DIED 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define TAKE_A_FORK 4

# define RUN 0
# define END 1
# define STOP 2

size_t	g_start_time;

typedef struct s_philo
{
	pthread_t		t;
	pthread_mutex_t	mutex;
	int				i;
	size_t			last_meal;
	int				nb_meal;
	int				ifork[2];
}				t_philo;

typedef struct s_data
{
	t_philo			*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	display;
	pthread_mutex_t	state;
	pthread_mutex_t	fed;
	pthread_mutex_t	start;
	size_t			time[3];
	int				nb_meal_min;
	int				nb_fed;
	int				nb_philo;
	int				status;
}				t_data;

t_data	g_data;

size_t			ft_strlen(char *str);
int				ft_isnumber(char *str);
long int		ft_atoli(const char *str);

size_t			get_timestamp(void);
int				ft_data_init(int ac, char **av);
int				simulation(void);
void			print_action(int x, int action);
void			ft_eat(t_philo *philo, int i);
void			ft_take_forks(const t_philo philo, int i);
void			ft_sleep(int i);
int				print_in_thread(char *str);
void			set_status(int status);
int				get_status(void);

#endif
