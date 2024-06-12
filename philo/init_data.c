/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 23:02:21 by ezahiri           #+#    #+#             */
/*   Updated: 2024/06/12 00:37:06 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_info(t_data *info, char **av)
{
	info->flag = 0;
	info->n_philo = ft_atoi(av[1]);
	info->t_dead = ft_atoi(av[2]);
	info->t_eat = ft_atoi (av[3]);
	info->t_sleep = ft_atoi(av[4]);
	info->n_mails = ft_atoi(av[5]);
	info->forks = malloc (sizeof(pthread_mutex_t) * info->n_philo);
	if (!info->forks)
		return (printf ("malloc failed\n"));
	if (info->n_philo <= 0 || \
			info->n_philo > 200 || \
			info->t_dead < 60 || \
			info->t_eat < 60 || \
			info->t_sleep < 60 || \
			info->n_mails == -2)
		return (free(info->forks), printf ("invalid argument\n"));
	if (pthread_mutex_init(&info->mx_data, NULL))
		return (printf("pthread_mutex_init failed\n"));
	return (0);
}

int	init_philo(t_philo	*p, t_data *info, int i)
{
	if (pthread_mutex_init(info->forks + i, NULL))
		return (printf ("pthread_mutex_init failed\n"));
	if (pthread_mutex_init(&p->mx_philo, NULL))
		return (printf ("pthread_mutex_init failed\n"));
	p->id = i + 1;
	p->n_count = 0;
	p->info = info;
	p->right_fork = info->forks + i;
	if (i == info->n_philo - 1)
		p->left_fork = info->forks;
	else
		p->left_fork = info->forks + i + 1;
	return (0);
}

int	init_data(t_philo **p, char **av)
{
	t_data	*info;
	int		i;

	i = -1;
	info = (t_data *)malloc (sizeof(t_data));
	if (!info)
		return (printf ("malloc failed\n"));
	if (get_info(info, av))
		return (free(info), 1);
	*p = (t_philo *) malloc (sizeof(t_philo) * info->n_philo);
	if (!*p)
		return (printf ("malloc failed\n"));
	while (++i < info->n_philo)
		if (init_philo(&(*p)[i], info, i))
			return (1);
	return (0);
}
