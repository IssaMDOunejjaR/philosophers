/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 14:27:56 by iounejja          #+#    #+#             */
/*   Updated: 2021/05/24 10:47:52 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*check_death(void *data)
{
	t_philo	*philo;

	philo = data;
	while (1)
	{
		if (philo->num_eat == g_num_eat)
		{
			g_eat_all = 1;
			exit(0);
		}
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

int	start_routine(t_philo *philo)
{
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
	if (g_num_eat != -1 && philo->num_eat == g_num_eat)
		sem_post(g_eat);
	print_msg(get_time() - g_time_start, philo->id, "is sleeping");
	usleep(g_sleep_time * 1000);
	print_msg(get_time() - g_time_start, philo->id, "is thinking");
	return (0);
}

void	*routine(void *data)
{
	t_philo		*philo;
	pthread_t	th;

	philo = data;
	philo->limit = get_time() + g_die_time;
	if (pthread_create(&th, NULL, &check_death, philo) != 0)
		return (NULL);
	if (pthread_detach(th) != 0)
		return (NULL);
	while (1)
		start_routine(philo);
	return (NULL);
}

void	child_process(int id)
{
	t_philo		philo;

	philo.id = id;
	philo.num_eat = 0;
	if (pthread_create(&philo.thread, NULL, &routine, &philo) != 0)
		return ;
	if (pthread_detach(philo.thread) != 0)
		return ;
	while (g_died)
	{
		if (g_eat_all == 1)
			exit(0);
		usleep(100);
	}
}

void	create_philo(void)
{
	int			i;
	pid_t		pid;
	int			*pids;

	pids = malloc(sizeof(int) * g_num_of_philo);
	init_sem();
	i = 0;
	g_time_start = get_time();
	while (i < g_num_of_philo)
	{
		pid = fork();
		if (pid == -1)
			return ;
		else if (pid == 0)
		{
			child_process(i);
			exit(0);
		}
		else
			pids[i] = pid;
		usleep(100);
		i++;
	}
	sem_wait(g_proc);
	kill_and_free(pids);
}
