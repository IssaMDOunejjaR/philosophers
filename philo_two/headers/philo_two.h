/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 14:11:43 by iounejja          #+#    #+#             */
/*   Updated: 2021/04/03 14:44:35 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>

int					g_num_of_philo;
int					g_die_time;
int					g_eat_time;
int					g_sleep_time;
int					g_num_eat;
long int			g_time_start;
int					g_died;
int					g_num_philo_eat;
sem_t				*g_fork;
sem_t				*g_lock;

typedef struct		s_philo
{
	int				id;
	pthread_t		thread;
	int				num_eat;
	long int		last_eat;
	long int		limit;
}					t_philo;

int					ft_strcmp(char *s1, char *s2);
int					ft_atoi(const char *str);
long int 			get_time();
int					is_all_num(char *str);
int					check_params(void);
int					init_options(int argc, char **argv);
void				print_msg(int timestamp, int thread_n, char *msg);
int					create_philo(t_philo *philo);

#endif