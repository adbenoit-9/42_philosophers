/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:11:58 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/09 16:58:38 by adbenoit         ###   ########.fr       */
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

# define DIE 0
# define EAT 1
# define SLEEP 2
# define THINK 3


typedef struct	s_philo
{
	int				i;
	pthread_t		t;
	long int		timestamp[4];
	int				n_eat;
	int				dead;
	int				eat;
}				t_philo;

typedef	struct	s_data
{
	unsigned int	time[3];
	pthread_mutex_t	*fork;
	int				n_eat;
	int				n_dead;
	int				n;
	int				i;
	struct timeval	*tv;
	t_philo			*philo;
}				t_data;

int			init_data(char **av, t_data *data);

int			ft_isnumber(char *str);
long int	ft_atoli(const char *str);

int		start_philo(t_data *data);


#endif
