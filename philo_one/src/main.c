/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:11:16 by adbenoit          #+#    #+#             */
/*   Updated: 2021/04/12 17:59:15 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	main(int ac, char **av)
{
	if ((ac != 6 && ac != 5) || init_data(av) == -1)
	{
		printf("Arguments error.\n");
		return (-1);
	}
	start_philo();
	return (0);
}
