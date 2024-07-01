/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:49:25 by ezahiri           #+#    #+#             */
/*   Updated: 2024/07/01 08:52:08 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	kill_all(t_philo *p, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		kill((p + i)->pid, SIGKILL);
		waitpid((p + i)->pid, NULL, 0);
		i -= -1;
	}
	sem_close(p->info->full);
	sem_close(p->info->fork);
	sem_close(p->info->death);
	sem_close(p->info->print);
	sem_close(p->mx_mails);
	sem_unlink("mail");
	sem_unlink("death");
	sem_unlink("print");
	sem_unlink("death");
	sem_unlink("full");
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
	if (p->info->n_mails < 0)
		return (NULL);
	while (++i < p->info->n_philo)
		sem_wait(p->info->full);
	sem_post(p->info->death);
	return (NULL);
}

void	*check_death(void *arg)
{
	t_philo	*p;
	long	t;

	p = (t_philo *)arg;
	while (1)
	{
		sem_wait(p->sm_last_eat);
		t = p->last_eat;
		sem_post(p->sm_last_eat);
		if (get_time() - t >= p->info->t_dead)
		{
			sem_wait(p->info->print);
			ft_putnbr_fd(get_time() - p->info->t_start, 1);
			ft_putchar_fd('\t', 1);
			ft_putnbr_fd(p->id, 1);
			ft_putchar_fd('\t', 1);
			ft_putstr_fd("died", 1);
			ft_putchar_fd('\n', 1);
			sem_post(p->info->death);
			break ;
		}
	}
	return (NULL);
}

int	philo_life(t_philo *p)
{
	pthread_t	tid;
	int			n;

	p->last_eat = get_time();
	if (0 != pthread_create(&tid, NULL, &check_death, p))
		return (0);
	pthread_detach(tid);
	if (p->id % 2 == 0)
		ft_sleep(p->info->t_eat);
	while (1)
	{
		eating(p);
		sem_wait(p->mx_mails);
		n = p->n_count;
		sem_post(p->mx_mails);
		if (n == p->info->n_mails)
		{
			sem_post(p->info->full);
			exit(0);
		}
		sleeping(p);
		thinking(p);
	}
	return (0);
}

int	create_process(t_philo *p)
{
	int			i;
	pthread_t	mail;

	i = 0;
	p->info->t_start = get_time();
	while (i < p->info->n_philo)
	{
		(p + i)->pid = fork();
		if ((p + i)->pid < 0)
			kill_all(p, i);
		else if ((p + i)->pid == 0)
			philo_life(p + i);
		i++;
	}
	if (0 != pthread_create(&mail, NULL, &check_mails, p))
		return (kill_all(p, p->info->n_philo));
	pthread_detach(mail);
	i = -1;
	sem_wait(p->info->death);
	while (++i < p->info->n_philo)
		sem_post(p->info->full);
	kill_all(p, p->info->n_philo);
	return (1);
}
