/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 17:50:38 by iounejja          #+#    #+#             */
/*   Updated: 2021/04/06 11:12:12 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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

void	print_msg(int timestamp, int thread_n, char *msg)
{
	pthread_mutex_lock(&g_lock_print);
	printf("%d %d %s\n", timestamp, thread_n, msg);
	if (ft_strcmp(msg, "died") != 0)
		pthread_mutex_unlock(&g_lock_print);
}

void	destroy_and_free(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < g_num_of_philo)
	{
		pthread_mutex_destroy(&g_fork[i]);
		i++;
	}
	pthread_mutex_destroy(&g_lock_print);
	free(philo);
	free(g_fork);
}
