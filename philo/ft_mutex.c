/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 08:49:34 by ezahiri           #+#    #+#             */
/*   Updated: 2024/07/02 08:28:18 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_write(long	*dst, long src, pthread_mutex_t *m)
{
	pthread_mutex_lock(m);
	*dst = src;
	pthread_mutex_unlock(m);
}

long	ft_read(void *r, pthread_mutex_t *m)
{
	long	red;

	pthread_mutex_lock(m);
	red = *((long *)r);
	pthread_mutex_unlock(m);
	return (red);
}

int	ft_free(t_philo *p, t_data *info, int n)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&info->mx_data);
	while (++i < n)
	{
		pthread_mutex_destroy(info->forks + i);
		pthread_mutex_destroy(&(p + i)->mx_philo);
	}
	free(info->forks);
	free(p->info);
	free(p);
	return (1);
}
