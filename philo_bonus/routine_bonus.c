/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:06:37 by ezahiri           #+#    #+#             */
/*   Updated: 2024/06/08 18:41:44 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eating(t_philo *p)
{
	char	*s1;
	char	*s2;

	s1 = "has taken a fork\n";
	s2 = "is eating\n";
	sem_wait(p->info->fork);
	printf ("%ld\t%d\t%s", get_time() - p->info->t_start, p->id, s1);
	sem_wait(p->info->fork);
	printf ("%ld\t%d\t%s", get_time() - p->info->t_start, p->id, s1);
	p->last_eat = get_time();
	p->n_count++;
	printf ("%ld\t%d\t%s", get_time() - p->info->t_start, p->id, s2);
	ft_sleep(p->info->t_eat, p);
	sem_post(p->info->fork);
	sem_post(p->info->fork);
}

void	sleeping(t_philo *p)
{
	char	*s;

	s = "is sleeping\n";
	printf ("%ld\t%d\t%s", get_time() - p->info->t_start, p->id, s);
	ft_sleep(p->info->t_sleep, p);
}

void	thinking(t_philo *p)
{
	char	*s;

	s = "is thinking\n";
	printf ("%ld\t%d\tthinking\n", get_time() - p->info->t_start, p->id);
}
