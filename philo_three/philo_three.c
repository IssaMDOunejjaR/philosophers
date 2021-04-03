/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 16:04:48 by iounejja          #+#    #+#             */
/*   Updated: 2021/04/03 18:12:57 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		main(int argc, char **argv)
{
	if (!(argc >= 5 && argc < 7))
		printf("Bad Arguments!\n");
	else
	{
		sem_unlink("fork");
		sem_unlink("lock");
		g_died = 1;
		g_num_philo_eat = 0;
		if (init_options(argc, argv) != 0)
			printf("Bad Arguments!\n");
		else
		{
			if (create_philo() != 0)
				printf("Error\n");
			sem_unlink("fork");
			sem_unlink("lock");
			sem_close(g_fork);
			sem_close(g_lock);
		}
	}
	return (0);
}