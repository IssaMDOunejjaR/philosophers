/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 12:25:22 by iounejja          #+#    #+#             */
/*   Updated: 2021/04/06 11:38:22 by iounejja         ###   ########.fr       */
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

int	start_routine(t_philo *philo)
{
	long int	tmp;

	pthread_mutex_lock(&g_fork[philo->id]);
	print_msg(get_time() - g_time_start, philo->id, "has taken a fork");
	pthread_mutex_lock(&g_fork[(philo->id + 1) % g_num_of_philo]);
	print_msg(get_time() - g_time_start, philo->id, "has taken a fork");
	print_msg(get_time() - g_time_start, philo->id, "is eating");
	philo->limit = get_time() + g_die_time;
	tmp = g_eat_time * 1000;
	usleep(tmp);
	philo->num_eat++;
	pthread_mutex_unlock(&g_fork[philo->id]);
	pthread_mutex_unlock(&g_fork[(philo->id + 1) % g_num_of_philo]);
	if (g_num_eat != -1 && philo->num_eat == g_num_eat)
	{
		g_num_philo_eat++;
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
		i++;
	}
}

int	create_philo(t_philo *philo)
{
	int		i;

	mutex_init(philo);
	i = 0;
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
		if (g_num_philo_eat == g_num_of_philo)
			break ;
		usleep(100);
	}
	return (0);
}
