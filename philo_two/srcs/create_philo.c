/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 14:27:56 by iounejja          #+#    #+#             */
/*   Updated: 2021/05/30 18:34:15 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}

void	start_routine(t_philo *philo)
{
	sem_wait(philo->check);
	sem_wait(g_fork);
	print_msg(get_time() - g_time_start, philo->id, "has taken a fork", philo);
	sem_wait(g_fork);
	print_msg(get_time() - g_time_start, philo->id, "has taken a fork", philo);
	philo->limit = get_time() + g_die_time;
	print_msg(get_time() - g_time_start, philo->id, "is eating", philo);
	usleep(g_eat_time * 1000);
	sem_wait(g_eat);
	if (g_num_eat != -1 && g_num_philo_eat == g_num_of_philo)
	{
		g_end = 0;
		return ;
	}
	sem_post(g_eat);
	sem_post(g_fork);
	sem_post(g_fork);
	sem_post(philo->check);
	print_msg(get_time() - g_time_start, philo->id, "is sleeping", philo);
	usleep(g_sleep_time * 1000);
	print_msg(get_time() - g_time_start, philo->id, "is thinking", philo);
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

void	init_sem(t_philo *philo)
{
	int		i;
	char	*sem_name;

	g_fork = sem_open("fork", O_CREAT, 0644, g_num_of_philo);
	g_lock = sem_open("lock", O_CREAT, 0644, 1);
	g_eat = sem_open("eat", O_CREAT, 0644, 1);
	i = 0;
	while (i < g_num_of_philo)
	{
		philo[i].num_eat = 0;
		philo[i].id = i;
		sem_name = ft_itoa(i);
		sem_unlink(sem_name);
		philo[i].check = sem_open(sem_name, O_CREAT, 0644, 1);
		free(sem_name);
		i++;
	}
}

int	create_philo(t_philo *philo)
{
	int		i;

	i = 0;
	init_sem(philo);
	g_time_start = get_time();
	while (i < g_num_of_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]) != 0)
			return (-1);
		if (pthread_detach(philo[i].thread) != 0)
			return (-1);
		usleep(100);
		i++;
	}
	while (g_end)
		usleep(100);
	return (0);
}
