/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 00:30:47 by ezahiri           #+#    #+#             */
/*   Updated: 2024/06/12 00:30:14 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Edo Tensei No Jurtsu

void	*philo_life(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	while (!ft_read(&p->info->t_start, &p->info->mx_data))
		;
	if (p->id % 2 == 0)
		ft_sleep(p, p->info->t_eat);
	if (p->info->n_mails != 0)
	{
		while (!ft_read(&p->info->flag, &p->info->mx_data))
		{
			eating(p);
			if (p->n_count == p->info->n_mails)
				return (NULL);
			sleeping(p);
			thinking(p);
		}
	}
	return (NULL);
}

int	edo_tensei(t_philo *p)
{
	int		i;
	long	t_start;

	i = -1;
	p->info->t_start = 0;
	while (++i < p->info->n_philo)
	{
		if (pthread_create(&(p + i)->tid, NULL, &philo_life, p + i))
			return (printf ("pthread_create failed"));
	}
	t_start = get_time();
	ft_mutex(&p->info->t_start, &t_start, &p->info->mx_data);
	ft_sleep(p, p->info->t_dead);
	return (0);
}
