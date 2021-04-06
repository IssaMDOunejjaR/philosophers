/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 14:27:56 by iounejja          #+#    #+#             */
/*   Updated: 2021/04/06 12:41:00 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*check_death(void *data)
{
	t_philo	*philo;

	philo = data;
	while (1)
	{
		if (g_num_eat != -1 && philo->num_eat == g_num_eat)
			break ;
		if (get_time() > philo->limit)
		{
			print_msg(get_time() - g_time_start, philo->id, "died");
			g_died = 0;
			sem_post(g_proc);
			break ;
		}
		usleep(100);
	}
	return (NULL);
}

int	start_routine(t_philo *philo)
{
	long int	tmp;

	if (sem_wait(g_fork) != 0)
		return (-1);
	print_msg(get_time() - g_time_start, philo->id, "has taken a fork");
	if (sem_wait(g_fork) != 0)
		return (-1);
	print_msg(get_time() - g_time_start, philo->id, "has taken a fork");
	print_msg(get_time() - g_time_start, philo->id, "is eating");
	philo->limit = get_time() + g_die_time;
	tmp = g_eat_time * 1000;
	usleep(tmp);
	philo->num_eat++;
	if (sem_post(g_fork) != 0)
		return (-1);
	if (sem_post(g_fork) != 0)
		return (-1);
	if (g_num_eat != -1 && philo->num_eat == g_num_eat)
	{
		sem_post(g_eat);
		return (-1);
	}
	print_msg(get_time() - g_time_start, philo->id, "is sleeping");
	tmp = g_sleep_time * 1000;
	usleep(tmp);
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
	{
		if (start_routine(philo) != 0)
			break ;
	}
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
		if (philo.num_eat == g_num_eat)
			break ;
		usleep(100);
	}
	sem_close(g_fork);
	sem_close(g_lock);
}

void	*check_eat(void *data)
{
	int	i;

	i = g_num_of_philo;
	while (i)
	{
		sem_wait(g_eat);
		i--;
	}
	sem_post(g_proc);
	return (NULL);
}

void	create_philo(void)
{
	int			i;
	pid_t		pid;
	int			*pids;

	pids = malloc(sizeof(int) * g_num_of_philo);
	init_sem();
	i = 0;
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
