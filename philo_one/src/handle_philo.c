/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 18:00:06 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/07 18:00:43 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	clear_philo(t_philo *philo)
{
	while (philo)
	{
		free(philo);
		philo = philo->next;
	}
}

t_philo	*new_philo(int i)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->i = i;
	philo->n_eat = 0;
	philo->next = NULL;
	return (philo);
}
