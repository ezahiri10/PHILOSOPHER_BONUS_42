/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:06:37 by ezahiri           #+#    #+#             */
/*   Updated: 2024/07/01 15:32:15 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_1(t_philo *p)
{
	sem_post(p->info->fork);
	ft_sleep(p->info->t_dead);
}

void	eating(t_philo *p)
{
	char	*s1;
	char	*s2;

	s1 = "has taken a fork";
	s2 = "is eating";
	sem_wait(p->info->fork);
	sem_wait(p->info->print);
	printf("%ld\t%d\t%s\n", get_time() - p->info->t_start, p->id, s1);
	sem_post(p->info->print);
	if (p->info->n_philo == 1)
		return (philo_1(p));
	sem_wait(p->info->fork);
	sem_wait(p->info->print);
	printf("%ld\t%d\t%s\n", get_time() - p->info->t_start, p->id, s1);
	sem_post(p->info->print);
	p->n_count++;
	sem_wait(p->sm_last_eat);
	p->last_eat = get_time();
	sem_post(p->sm_last_eat);
	sem_wait(p->info->print);
	printf("%ld\t%d\t%s\n", get_time() - p->info->t_start, p->id, s2);
	sem_post(p->info->print);
	ft_sleep(p->info->t_eat);
	sem_post(p->info->fork);
	sem_post(p->info->fork);
}

void	sleeping(t_philo *p)
{
	char	*s;

	s = "is sleeping";
	sem_wait(p->info->print);
	printf("%ld\t%d\t%s\n", get_time() - p->info->t_start, p->id, s);
	sem_post(p->info->print);
	ft_sleep(p->info->t_sleep);
}

void	thinking(t_philo *p)
{
	char	*s;

	s = "is thinking";
	sem_wait(p->info->print);
	printf("%ld\t%d\t%s\n", get_time() - p->info->t_start, p->id, s);
	sem_post(p->info->print);
}
