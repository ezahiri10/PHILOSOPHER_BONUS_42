/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 00:34:38 by ezahiri           #+#    #+#             */
/*   Updated: 2024/06/26 07:40:37 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	t;

	if (-1 == gettimeofday(&t, NULL))
		return (0);
	else
		return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_sleep(t_philo *p, size_t t)
{
	size_t	s;

	s = get_time();
	while (!ft_read(&p->info->flag, &p->info->mx_data))
	{
		if (get_time() - s >= t)
			return ;
		usleep(100);
	}
}
