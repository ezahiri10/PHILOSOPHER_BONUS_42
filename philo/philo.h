/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 15:43:11 by ezahiri           #+#    #+#             */
/*   Updated: 2024/06/12 00:53:49 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	long			n_philo;
	long			t_eat;
	long			t_sleep;
	long			t_dead;
	int				n_mails;
	long			t_start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mx_data;
	long			flag;
}				t_data;

typedef struct s_philo
{
	t_data			*info;
	pthread_t		tid;
	long			last_eat;
	pthread_mutex_t	mx_philo;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	int				n_count;
	int				id;
}				t_philo;

int		init_data(t_philo **p, char **av);
long	ft_atoi(const char *str);
long	get_time(void);
void	ft_sleep(t_philo *p, size_t t);
int		edo_tensei(t_philo *p);
void	eating(t_philo *p);
void	sleeping(t_philo *p);
void	thinking(t_philo *p);
void	ft_mutex(long	*dst, long *src, pthread_mutex_t *m);
long	ft_read(void *r, pthread_mutex_t *m);

#endif