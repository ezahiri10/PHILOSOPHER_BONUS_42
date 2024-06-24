/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:29:05 by ezahiri           #+#    #+#             */
/*   Updated: 2024/06/24 09:08:54 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *p)
{
	char	*s1;
	char	*s2;

	s1 = "has taken a fork";
	s2 = "is eating";
	pthread_mutex_lock(p->right_fork);
	printf ("%lu\t%d\t%s\n", get_time() - p->info->t_start, p->id, s1);
	if (p->info->n_philo == 1)
	{
		ft_sleep(p, p->info->t_dead + 1);
		return ;
	}
	pthread_mutex_lock(p->left_fork);
	printf ("%lu\t%d\t%s\n", get_time() - p->info->t_start, p->id, s1);
	printf ("%lu\t%d\t%s\n", get_time() - p->info->t_start, p->id, s2);
	if (p->info->t_eat > 0)
	{
		pthread_mutex_lock(&p->mx_philo);
		p->n_count++;
		pthread_mutex_unlock(&p->mx_philo);
	}
	ft_write(&p->last_eat, get_time(), &p->mx_philo);
	ft_sleep(p, p->info->t_eat);
	pthread_mutex_unlock(p->right_fork);
	pthread_mutex_unlock(p->left_fork);
}

void	sleeping(t_philo *p)
{
	char	*s;

	if (ft_read(&p->info->flag, &p->info->mx_data) == 1)
		return ;
	s = "is sleeping";
	printf ("%lu\t%d\t%s\n", get_time() - p->info->t_start, p->id, s);
	ft_sleep(p, p->info->t_sleep);
}

void	thinking(t_philo *p)
{
	char	*s;

	if (ft_read(&p->info->flag, &p->info->mx_data) == 1)
		return ;
	s = "is thinking";
	printf ("%lu\t%d\t%s\n", get_time() - p->info->t_start, p->id, s);
}
