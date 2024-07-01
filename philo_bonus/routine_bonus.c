/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:06:37 by ezahiri           #+#    #+#             */
/*   Updated: 2024/07/01 09:30:28 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eating(t_philo *p)
{
	char	*s1;
	char	*s2;

	s1 = "has taken a fork";
	s2 = "is eating";
	sem_wait(p->info->fork);
	print (p, get_time() - p->info->t_start, s1);
	if (p->info->n_philo == 1)
	{
		sem_post(p->info->fork);
		ft_sleep(p->info->t_dead);
		return ;
	}
	sem_wait(p->info->fork);
	print (p, get_time() - p->info->t_start, s1);
	sem_wait(p->mx_mails);
	p->n_count++;
	sem_post(p->mx_mails);
	sem_wait(p->sm_last_eat);
	p->last_eat = get_time();
	sem_post(p->sm_last_eat);
	print (p, get_time() - p->info->t_start, s2);
	ft_sleep(p->info->t_eat);
	sem_post(p->info->fork);
	sem_post(p->info->fork);
}

void	sleeping(t_philo *p)
{
	char	*s;

	s = "is sleeping";
	print (p, get_time() - p->info->t_start, s);
	ft_sleep(p->info->t_sleep);
}

void	thinking(t_philo *p)
{
	char	*s;

	s = "is thinking";
	print (p, get_time() - p->info->t_start, s);
}
