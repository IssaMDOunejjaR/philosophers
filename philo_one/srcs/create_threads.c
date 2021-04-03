/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 12:25:22 by iounejja          #+#    #+#             */
/*   Updated: 2021/04/03 13:05:03 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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
			break ;
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
	philo->last_eat = get_time();
	philo->limit = get_time() + g_die_time;
	if (pthread_create(&th, NULL, &check_death, philo) != 0)
		return (NULL);
	while (1)
	{
		if (g_num_eat != -1 && philo->num_eat == g_num_eat)
		{
			g_num_philo_eat++;
			break ;
		}
		pthread_mutex_lock(&g_fork[philo->id]);
		pthread_mutex_lock(&g_fork[(philo->id + 1) % g_num_of_philo]);
		print_msg(get_time() - g_time_start, philo->id, "has taken a fork");
		print_msg(get_time() - g_time_start, philo->id, "has taken a fork");
		print_msg(get_time() - g_time_start, philo->id, "is eating");
		philo->limit = get_time() + g_die_time;
		usleep(g_eat_time * 1000);
		philo->num_eat++;
		pthread_mutex_unlock(&g_fork[philo->id]);
		pthread_mutex_unlock(&g_fork[(philo->id + 1) % g_num_of_philo]);
		print_msg(get_time() - g_time_start, philo->id, "is sleeping");
		usleep(g_sleep_time * 1000);
		print_msg(get_time() - g_time_start, philo->id, "is thinking");
	}
	return (NULL);
}

void	mutex_init(t_philo *philo)
{
	int		i;

	i = 0;
	g_time_start = get_time();
	while (i < g_num_of_philo)
	{
		pthread_mutex_init(&g_fork[i], NULL);
		i++;
	}
	i = 0;
	while (i < g_num_of_philo)
	{
		philo[i].num_eat = 0;
		philo[i].id = i;
		philo[i].last_eat = 0;
		i++;
	}
}

int		create_philo(t_philo *philo)
{
	int		i;

	i = 0;
	mutex_init(philo);
	while (i < g_num_of_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, &philo_routine, &philo[i]) != 0)
			return (-1);
		pthread_detach(philo[i].thread);
		usleep(100);
		i++;
	}
	while (g_died)
	{
		if (g_num_philo_eat == g_num_of_philo)
			break ;
		usleep(100);
	}
	return (0);
}
