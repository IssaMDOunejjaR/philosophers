/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 11:14:37 by iounejja          #+#    #+#             */
/*   Updated: 2021/05/30 19:40:35 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	is_all_num(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (-1);
		i++;
	}
	return (0);
}

int	check_params(void)
{
	if (g_num_of_philo < 2)
		return (-1);
	if (g_num_of_philo > 200)
		return (-1);
	if (g_die_time < 60 || g_eat_time < 60
		|| g_sleep_time < 60)
		return (-1);
	return (0);
}

int	init_options(int argc, char **argv)
{
	int		i;

	i = 1;
	while (argv[i] != NULL)
	{
		if (is_all_num(argv[i]) != 0)
			return (-1);
		i++;
	}
	g_num_of_philo = ft_atoi(argv[1]);
	g_die_time = ft_atoi(argv[2]);
	g_eat_time = ft_atoi(argv[3]);
	g_sleep_time = ft_atoi(argv[4]);
	g_num_eat = -1;
	if (argc == 6)
	{
		g_num_eat = ft_atoi(argv[5]);
		if (g_num_eat <= 0)
			return (-1);
	}
	if (check_params() != 0)
		return (-1);
	return (0);
}
