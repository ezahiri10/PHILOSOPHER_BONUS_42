/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:34:05 by ezahiri           #+#    #+#             */
/*   Updated: 2024/06/08 14:32:47 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_philo(t_data *info, t_philo *p, int i)
{
	p->id = i + 1;
	p->info = info;
	p->last_eat = 0;
	p->n_count = 0;
	return (0);
}

int	init_semaphores(t_data *info, t_philo **p)
{
	sem_unlink("fork");
	sem_unlink("mail");
	sem_unlink("print");
	sem_unlink("full");
	info->fork = sem_open("fork", O_CREAT, 0644, info->n_philo);
	if (info->fork == SEM_FAILED)
		return (free(info), 0);
	info->full = sem_open("full", O_CREAT, 0644, 0);
	if (info->fork == SEM_FAILED)
		return (free(info), 0);
	info->death = sem_open("mail", O_CREAT, 0644, 0);
	if (info->death == SEM_FAILED)
		return (free(info), 0);
	info->print = sem_open("print", O_CREAT, 0644, 1);
	if (info->print == SEM_FAILED)
		return (free(info), 0);
	*p = (t_philo *)malloc(sizeof(t_philo) * info->n_philo);
	if (!*p)
		return (free(info), 0);
	return (1);
}

int	init_data(char **av, t_philo **p)
{
	int		i;
	t_data	*info;

	i = -1;
	info = (t_data *)malloc(sizeof(t_data));
	if (!info)
		return (0);
	info->n_philo = ft_atoi(av[1]);
	info->t_dead = ft_atoi(av[2]);
	info->t_eat = ft_atoi(av[3]);
	info->t_sleep = ft_atoi(av[4]);
	info->n_mails = ft_atoi(av[5]);
	if (info->n_philo > 200 || info->n_philo <= 0
		|| info->t_dead < 60
		|| info->t_eat < 60
		|| info->t_sleep < 60
		|| info->n_mails == 0)
		return (free(info), 0);
	if (!init_semaphores(info, p))
		return (0);
	while (++i < info->n_philo)
		init_philo(info, *p + i, i);
	return (1);
}
