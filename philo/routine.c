/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:29:05 by ezahiri           #+#    #+#             */
/*   Updated: 2024/06/12 00:05:20 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *p)
{
	char	*s1;
	char	*s2;
	long	cur_t;

	s1 = "has taken a fork";
	s2 = "is eating";
	pthread_mutex_lock(p->right_fork);
	printf ("%lu\t%d\t%s\n", get_time() - p->info->t_start, p->id, s1);
	pthread_mutex_lock(p->left_fork);
	printf ("%lu\t%d\t%s\n", get_time() - p->info->t_start, p->id, s1);
	printf ("%lu\t%d\t%s\n", get_time() - p->info->t_start, p->id, s2);
	cur_t = get_time ();
	if (p->info->t_eat > 0)
		p->n_count++;
	ft_mutex(&p->last_eat, &cur_t, &p->mx_philo);
	ft_sleep(p, p->info->t_eat);
	pthread_mutex_unlock(p->right_fork);
	pthread_mutex_unlock(p->left_fork);
}

void	sleeping(t_philo *p)
{
	char	*s;

	s = "is sleeping";
	printf ("%lu\t%d\t%s\n", get_time() - p->info->t_start, p->id, s);
	ft_sleep(p, p->info->t_sleep);
}

void	thinking(t_philo *p)
{
	char	*s;

	s = "is thinking";
	printf ("%lu\t%d\t%s\n", get_time() - p->info->t_start, p->id, s);
}
