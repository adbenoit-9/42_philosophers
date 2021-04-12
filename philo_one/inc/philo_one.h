/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:11:58 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/12 22:03:59 by adbenoit         ###   ########.fr       */
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

unsigned int	start_time;

typedef struct	s_philo
{
	int				i;
	pthread_mutex_t	mutex;
	unsigned int	last_eat;
	int				n_eat;
	int				is_dead;
}				t_philo;

typedef	struct	s_data
{
	unsigned int	time[3];
	pthread_mutex_t	*fork;
	pthread_mutex_t mutex;
	int				n_eat;
	int				n;
	t_philo			*philo;
}				t_data;

t_data			data;

int				init_data(char **av);

int				ft_isnumber(char *str);
long int		ft_atoli(const char *str);

int				start_philo(void);
void			display_message(pthread_mutex_t *m, int x, int state);
unsigned int	get_time(void);


#endif
