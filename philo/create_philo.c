/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 00:30:47 by ezahiri           #+#    #+#             */
/*   Updated: 2024/06/25 22:25:10 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
				break ;
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
		{
			ft_clean(p, i);
			ft_free(p, p->info, p->info->n_philo);
			return (write (2, "pthread_create failed", 22));
		}
	}
	t_start = get_time();
	ft_write(&p->info->t_start, t_start, &p->info->mx_data);
	ft_sleep(p, p->info->t_dead);
	return (0);
}
