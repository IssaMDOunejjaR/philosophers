/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 14:27:56 by iounejja          #+#    #+#             */
/*   Updated: 2021/04/03 18:10:38 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*check_death(void *data)
{
	t_philo		*philo;

	philo = data;
	while (1)
	{
		// if (g_num_eat != -1 && philo->num_eat == g_num_eat)
		// 	exit(0);
		if (get_time() > philo->limit)
		{
			print_msg(get_time() - g_time_start, philo->id, "died");
			g_died = 0;
			sem_post(g_proc);
			exit(0);
		}
		usleep(100);
	}
	return (NULL);
}

void	*philo_routine(void *data)
{
	t_philo		*philo;
	pthread_t	th;

	philo = data;
	philo->limit = get_time() + g_die_time;
	if (pthread_create(&th, NULL, &check_death, philo) != 0)
		return (NULL);
	pthread_detach(th);
	while (1)
	{
		if (g_num_eat != -1 && philo->num_eat == g_num_eat)
		{
			g_num_philo_eat++;
			exit(0);
		}
		sem_wait(g_fork);
		print_msg(get_time() - g_time_start, philo->id, "has taken a fork");
		sem_wait(g_fork);
		print_msg(get_time() - g_time_start, philo->id, "has taken a fork");
		print_msg(get_time() - g_time_start, philo->id, "is eating");
		philo->limit = get_time() + g_die_time;
		usleep(g_eat_time * 1000);
		philo->num_eat++;
		sem_post(g_fork);
		sem_post(g_fork);
		print_msg(get_time() - g_time_start, philo->id, "is sleeping");
		usleep(g_sleep_time * 1000);
		print_msg(get_time() - g_time_start, philo->id, "is thinking");
	}
	return (NULL);
}

int		create_philo(void)
{
	int			i;
	pid_t		pid;
	t_philo		philo;
	int			*pids;

	pids = malloc(sizeof(int) * g_num_of_philo);
	g_time_start = get_time();
	g_fork = sem_open("fork", O_CREAT, 0644, g_num_of_philo);
	g_lock = sem_open("lock", O_CREAT, 0644, 1);
	g_proc = sem_open("proc", O_CREAT, 0644, 0);
	i = 0;
	while (i < g_num_of_philo)
	{
		if ((pid = fork()) == -1)
			return (-1);
		else if (pid == 0)
		{
			philo.id = i;
			philo.num_eat = 0;
			pthread_create(&philo.thread, NULL, &philo_routine, &philo);
			pthread_detach(philo.thread);
			while (g_died)
			{
				if (g_num_philo_eat == g_num_of_philo)
					exit(0);
				usleep(100);
			}
			exit(0);
		}
		else
			pids[i] = pid;
		i++;
	}
	sem_wait(g_proc);
	i = 0;
	while (i < g_num_of_philo)
	{
		kill(pids[i], 0);
		i++;
	}
	// while (i < g_num_of_philo)
	// {
	// 	waitpid(0, 0, 0);
	// 	i++;
	// }
	return (0);
}