/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 14:27:56 by iounejja          #+#    #+#             */
/*   Updated: 2021/05/23 18:43:29 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	*check_death(void *data)
{
	t_philo	*philo;

	philo = data;
	while (1)
	{
		if (g_num_philo_eat == g_num_of_philo)
			g_eat_all = 1;
		if (get_time() > philo->limit)
		{
			print_msg(get_time() - g_time_start, philo->id, "died");
			g_died = 0;
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
		g_num_philo_eat++;
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

void	init_sem(t_philo *philo)
{
	int	i;

	g_fork = sem_open("fork", O_CREAT, 0644, g_num_of_philo);
	g_lock = sem_open("lock", O_CREAT, 0644, 1);
	i = 0;
	while (i < g_num_of_philo)
	{
		philo[i].num_eat = 0;
		philo[i].id = i;
		i++;
	}
}

int	create_philo(t_philo *philo)
{
	int		i;

	init_sem(philo);
	i = 0;
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
	while (g_died)
	{
		if (g_eat_all == 1)
		{
			sem_close(g_lock);
			sem_close(g_fork);
			break ;
		}
		usleep(100);
	}
	return (0);
}
