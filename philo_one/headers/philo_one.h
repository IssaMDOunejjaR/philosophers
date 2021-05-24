/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 17:29:51 by iounejja          #+#    #+#             */
/*   Updated: 2021/05/23 12:51:54 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

int					g_num_of_philo;
int					g_die_time;
int					g_eat_time;
int					g_sleep_time;
int					g_num_eat;
long int			g_time_start;
pthread_mutex_t		*g_fork;
pthread_mutex_t		g_lock_print;
int					g_died;
int					g_num_philo_eat;
int					g_all_eat;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				num_eat;
	long int		limit;
}					t_philo;

int					ft_atoi(const char *str);
int					is_all_num(char *str);
int					check_params(void);
int					init_options(int argc, char **argv);
void				destroy_and_free(t_philo *philo);
long int			get_time(void);
void				print_msg(int timestamp, int thread_n, char *msg);
int					create_philo(t_philo *philo);
void				mutex_init(t_philo *philo);

#endif
