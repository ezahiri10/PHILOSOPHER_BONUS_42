/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:34:05 by ezahiri           #+#    #+#             */
/*   Updated: 2024/07/01 10:50:57 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_philo(t_data *info, t_philo *p, int i)
{
	sem_unlink("mail");
	sem_unlink("last_eat");
	p->mx_mails = sem_open("mail", O_CREAT, 0644, 1);
	if (p->mx_mails == SEM_FAILED)
		return (ft_handler(info, 4), 1);
	p->sm_last_eat = sem_open("last_eat", O_CREAT, 0644, 1);
	if (p->sm_last_eat == SEM_FAILED)
		return (sem_clean(p->sm_last_eat, "last_eat"), ft_handler(info, 4), 1);
	p->id = i + 1;
	p->info = info;
	p->last_eat = 0;
	p->n_count = 0;
	p->pid = 0;
	return (0);
}

int	init_semaphores(t_data *info, t_philo **p)
{
	sem_unlink("fork");
	sem_unlink("full");
	sem_unlink("death");
	sem_unlink("print");
	info->fork = sem_open("fork", O_CREAT, 0644, info->n_philo);
	if (info->fork == SEM_FAILED)
		return (ft_handler(info, 1), 1);
	info->full = sem_open("full", O_CREAT, 0644, 0);
	if (info->fork == SEM_FAILED)
		return (ft_handler(info, 1), 2);
	info->death = sem_open("death", O_CREAT, 0644, 0);
	if (info->death == SEM_FAILED)
		return (ft_handler(info, 1), 3);
	info->print = sem_open("print", O_CREAT, 0644, 1);
	if (info->print == SEM_FAILED)
		return (ft_handler(info, 1), 4);
	*p = (t_philo *)malloc(sizeof(t_philo) * info->n_philo);
	if (!*p)
		return (ft_handler(info, 4), write (2, "malloc failed\n", 15));
	return (0);
}

int	get_info(t_data *info, char **av)
{
	info->n_philo = ft_atoi(av[1]);
	info->t_dead = ft_atoi(av[2]);
	info->t_eat = ft_atoi(av[3]);
	info->t_sleep = ft_atoi(av[4]);
	info->n_mails = ft_atoi(av[5]);
	if (info->n_philo > 200 || info->n_philo <= 0
		|| info->t_dead < 60
		|| info->t_eat < 60
		|| info->t_sleep < 60)
		return (printf ("invalid argument\n"));
	return (0);
}

int	init_data(char **av, t_philo **p)
{
	int		i;
	t_data	*info;

	i = -1;
	info = (t_data *)malloc(sizeof(t_data));
	if (!info)
		return (write (2, "malloc failed\n", 15));
	if (get_info(info, av) || init_semaphores(info, p))
		return (free(info), 1);
	while (++i < info->n_philo)
		if (init_philo(info, *p + i, i))
			return (free(info), free(p), 1);
	return (0);
}
