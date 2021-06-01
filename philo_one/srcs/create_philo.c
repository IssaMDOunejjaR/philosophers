/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 12:25:22 by iounejja          #+#    #+#             */
/*   Updated: 2021/06/01 11:20:05 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*check_death(void *data)
{
	t_philo	*philo;

	philo = data;
	while (1)
	{
		if (get_time() > philo->limit)
		{
			pthread_mutex_lock(&philo->check);
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
	pthread_mutex_lock(&philo->check);
	pthread_mutex_lock(&g_fork[philo->id]);
	print_msg(get_time() - g_time_start, philo->id, "has taken a fork", philo);
	pthread_mutex_lock(&g_fork[(philo->id + 1) % g_num_of_philo]);
	print_msg(get_time() - g_time_start, philo->id, "has taken a fork", philo);
	philo->limit = get_time() + g_die_time;
	print_msg(get_time() - g_time_start, philo->id, "is eating", philo);
	usleep(g_eat_time * 1000);
	pthread_mutex_lock(&g_eat);
	if (g_num_eat != -1 && g_num_philo_eat == g_num_of_philo)
	{
		g_end = 0;
		return ;
	}
	pthread_mutex_unlock(&g_eat);
	pthread_mutex_unlock(&g_fork[philo->id]);
	pthread_mutex_unlock(&g_fork[(philo->id + 1) % g_num_of_philo]);
	pthread_mutex_unlock(&philo->check);
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

void	mutex_init(t_philo *philo)
{
	int			i;

	i = 0;
	while (i < g_num_of_philo)
	{
		pthread_mutex_init(&g_fork[i], NULL);
		i++;
	}
	i = 0;
	while (i < g_num_of_philo)
	{
		philo[i].id = i;
		philo[i].num_eat = 0;
		pthread_mutex_init(&philo[i].check, NULL);
		i++;
	}
	pthread_mutex_init(&g_eat, NULL);
}

int	create_philo(t_philo *philo)
{
	int		i;

	i = 0;
	mutex_init(philo);
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
