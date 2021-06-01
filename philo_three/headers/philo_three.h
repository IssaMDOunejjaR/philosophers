/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 16:05:27 by iounejja          #+#    #+#             */
/*   Updated: 2021/05/30 18:42:29 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <pthread.h>
# include <signal.h>
# include <sys/time.h>

int					g_num_of_philo;
int					g_die_time;
int					g_eat_time;
int					g_sleep_time;
int					g_num_eat;
long int			g_time_start;
int					g_end;
int					g_num_philo_eat;
sem_t				*g_fork;
sem_t				*g_lock;
sem_t				*g_proc;
sem_t				*g_eat;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				num_eat;
	long int		limit;
	sem_t			*check;
}					t_philo;

int					ft_strcmp(char *s1, char *s2);
int					ft_atoi(const char *str);
char				*ft_itoa(int n);
long int			get_time(void);
void				print_msg(int timestamp, int thread_n, char *msg,
						t_philo *philo);
int					is_all_num(char *str);
int					check_params(void);
int					init_options(int argc, char **argv);
void				create_philo(void);
void				kill_and_free(int *pids);
void				init_sem(void);
void				*check_eat(void *data);

#endif
