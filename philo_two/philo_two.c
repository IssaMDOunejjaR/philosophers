/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 14:11:01 by iounejja          #+#    #+#             */
/*   Updated: 2021/05/30 18:16:12 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int	main(int argc, char **argv)
{
	t_philo	*philo;

	if (!(argc >= 5 && argc < 7))
		printf("Bad Arguments!\n");
	else
	{
		sem_unlink("fork");
		sem_unlink("lock");
		sem_unlink("eat");
		g_end = 1;
		g_num_philo_eat = 0;
		if (init_options(argc, argv) != 0)
			printf("Bad Arguments!\n");
		else
		{
			philo = malloc(sizeof(t_philo) * g_num_of_philo);
			if (create_philo(philo) != 0)
				printf("Error\n");
			free(philo);
			sem_unlink("fork");
			sem_unlink("lock");
			sem_unlink("eat");
		}
	}
	return (0);
}
