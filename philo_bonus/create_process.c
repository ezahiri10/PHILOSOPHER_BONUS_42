/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:49:25 by ezahiri           #+#    #+#             */
/*   Updated: 2024/06/08 17:31:44 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	kill_all(pid_t *pid, t_philo *p, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		kill(pid[i], SIGKILL);
		i -= -1;
	}
	sem_close(p->info->fork);
	sem_close(p->info->death);
	sem_close(p->info->print);
	sem_close(p->info->full);
	sem_unlink("fork");
	sem_unlink("mail");
	sem_unlink("print");
	sem_unlink("death");
	free(p->info->pid);
	free(p->info);
	free(p);
	return (0);
}

void	*check_mails(void *arg)
{
	t_philo	*p;
	int		i;

	p = (t_philo *)arg;
	i = -1;
	while (++i < p->info->n_philo)
		sem_wait(p->info->full);
	sem_post(p->info->death);
	return (NULL);
}

void	*check_death(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	while (1)
	{
		if (get_time() - p->last_eat > p->info->t_dead)
		{
			sem_wait(p->info->print);
			sem_post(p->info->death);
			printf ("%ld\t%d\tis died\n", get_time() - p->info->t_start, p->id);
		}
	}
	return (NULL);
}

int	philo_life(t_philo *p)
{
	pthread_t	tid;

	p->last_eat = get_time();
	if (0 != pthread_create(&tid, NULL, &check_death, p))
		return (0);
	while (1)
	{
		eating(p);
		if (p->n_count == p->info->n_mails)
			sem_post(p->info->full);
		sleeping(p);
		thinking(p);
	}
	return (0);
}

int	create_process(t_philo *p)
{
	int			i;
	pthread_t	mail;
	pid_t		*pid;

	p->info->t_start = get_time();
	p->info->pid = (pid_t *)malloc(sizeof(pid_t) * p->info->n_philo);
	if (!p->info->pid)
		return (kill_all(NULL, p, 0));
	pid = p->info->pid;
	i = 0;
	while (i < p->info->n_philo)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			kill_all(pid, p, i);
		else if (pid[i] == 0)
			philo_life(p + i);
		i++;
	}
	if (0 != pthread_create(&mail, NULL, &check_mails, p))
		return (kill_all(pid, p, p->info->n_philo));
	sem_wait(p->info->death);
	kill_all(p->info->pid, p, p->info->n_philo);
	return (1);
}
