/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 17:29:27 by iounejja          #+#    #+#             */
/*   Updated: 2021/05/23 12:52:23 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	main(int argc, char **argv)
{
	t_philo	*philo;

	if (!(argc >= 5 && argc < 7))
		printf("Bad Arguments!\n");
	else
	{
		g_died = 1;
		g_num_philo_eat = 0;
		g_all_eat = 0;
		if (init_options(argc, argv) != 0)
			printf("Bad Arguments!\n");
		else
		{
			g_fork = malloc(sizeof(pthread_mutex_t) * g_num_of_philo);
			philo = malloc(sizeof(t_philo) * g_num_of_philo);
			pthread_mutex_init(&g_lock_print, NULL);
			if (create_philo(philo) != 0)
				printf("Error\n");
			destroy_and_free(philo);
		}
	}
	return (0);
}
