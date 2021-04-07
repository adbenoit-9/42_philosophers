/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:11:58 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/07 18:05:28 by adbenoit         ###   ########.fr       */
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

# define DIE
# define EAT
# define SLEEP
# define THINK


typedef struct	s_philo
{
	int				i;
	pthread_t		t;
	pthread_mutex_t	m;
	long int		timestamp[4];
	int				n_eat;
	struct s_philo	*next;
}				t_philo;

typedef	struct	s_data
{
	long int	time[3];
	int			n_eat;
	int			n;
	t_philo		*philo;
}				t_data;

int			init_data(char **av, t_data *data);
void		clear_philo(t_philo *philo);
t_philo		*new_philo(int i);

int			ft_isnumber(char *str);
long int	ft_atoli(const char *str);


#endif
