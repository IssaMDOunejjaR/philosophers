/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 14:22:16 by iounejja          #+#    #+#             */
/*   Updated: 2021/05/30 19:07:58 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (s1[i] != s2[i])
		return (s1[i] - s2[i]);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		n;
	long	nb;
	long	val;

	i = 0;
	n = 1;
	nb = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		n = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		val = nb;
		nb = ((nb * 10) + (str[i++] - 48) * n);
		if (n == 1 && val > nb)
			return (-1);
		if (n == -1 && val < nb)
			return (0);
	}
	return (nb);
}

long int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec * 0.001));
}

void	print_msg(int timestamp, int thread_n, char *msg, t_philo *philo)
{
	sem_wait(g_lock);
	printf("%d %d %s\n", timestamp, thread_n, msg);
	if (ft_strcmp(msg, "is eating") == 0)
	{
		philo->num_eat++;
		if (g_num_eat != -1 && philo->num_eat == g_num_eat)
			sem_post(g_eat);
		else
			sem_post(g_lock);
	}
	else if (ft_strcmp(msg, "died") != 0)
		sem_post(g_lock);
}

void	init_sem(void)
{
	pthread_t	th;

	g_fork = sem_open("fork", O_CREAT, 0644, g_num_of_philo);
	g_lock = sem_open("lock", O_CREAT, 0644, 1);
	g_proc = sem_open("proc", O_CREAT, 0644, 0);
	g_eat = sem_open("eat", O_CREAT, 0644, 0);
	if (pthread_create(&th, NULL, &check_eat, NULL) != 0)
		return ;
	if (pthread_detach(th) != 0)
		return ;
}
