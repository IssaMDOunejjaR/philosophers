/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 14:27:56 by iounejja          #+#    #+#             */
/*   Updated: 2021/05/30 18:52:10 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*check_death(void *data)
{
	t_philo	*philo;

	philo = data;
	while (1)
	{
		if (get_time() > philo->limit)
		{
			sem_wait(philo->check);
			print_msg(get_time() - g_time_start, philo->id, "died", philo);
			g_end = 0;
			sem_post(g_proc);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}

int	start_routine(t_philo *philo)
{
	sem_wait(philo->check);
	sem_wait(g_fork);
	print_msg(get_time() - g_time_start, philo->id, "has taken a fork", philo);
	sem_wait(g_fork);
	print_msg(get_time() - g_time_start, philo->id, "has taken a fork", philo);
	print_msg(get_time() - g_time_start, philo->id, "is eating", philo);
	philo->limit = get_time() + g_die_time;
	usleep(g_eat_time * 1000);
	sem_post(g_fork);
	sem_post(g_fork);
	sem_post(philo->check);
	print_msg(get_time() - g_time_start, philo->id, "is sleeping", philo);
	usleep(g_sleep_time * 1000);
	print_msg(get_time() - g_time_start, philo->id, "is thinking", philo);
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
	t_philo	philo;
	char	*sem_name;

	philo.id = id;
	philo.num_eat = 0;
	sem_name = ft_itoa(id);
	sem_unlink(sem_name);
	philo.check = sem_open(sem_name, O_CREAT, 06444, 1);
	free(sem_name);
	if (pthread_create(&philo.thread, NULL, &routine, &philo) != 0)
		return ;
	if (pthread_detach(philo.thread) != 0)
		return ;
	while (g_end)
		usleep(100);
}

void	create_philo(void)
{
	int			i;
	pid_t		pid;
	int			*pids;

	init_sem();
	i = 0;
	pids = malloc(sizeof(int) * g_num_of_philo);
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
