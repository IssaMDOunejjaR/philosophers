/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 16:04:48 by iounejja          #+#    #+#             */
/*   Updated: 2021/04/06 11:16:00 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	main(int argc, char **argv)
{
	if (!(argc >= 5 && argc < 7))
		printf("Bad Arguments!\n");
	else
	{
		sem_unlink("fork");
		sem_unlink("lock");
		sem_unlink("proc");
		g_died = 1;
		g_num_philo_eat = 0;
		if (init_options(argc, argv) != 0)
			printf("Bad Arguments!\n");
		else
		{
			create_philo();
			sem_close(g_lock);
			sem_close(g_fork);
			sem_close(g_proc);
		}
	}
	return (0);
}
