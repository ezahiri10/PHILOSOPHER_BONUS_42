/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 15:42:19 by ezahiri           #+#    #+#             */
/*   Updated: 2024/06/22 09:20:23 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse(char **av, int ac)
{
	int	i;
	int	j;

	i = 0;
	if (ac == 5 || ac == 6)
	{
		while (av[++i])
		{
			j = 0;
			while (av[i][j])
			{
				if (av[i][j] >= '0' && av[i][j] <= '9')
					j++;
				else
					return (printf("invalid input\n"));
			}
		}
	}
	else
		return (printf ("donner 4 ou 5 argmuent"));
	return (0);
}

int	ft_free(t_philo *p, t_data *info, int n)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&p->info->mx_data);
	while (++i < n)
	{
		pthread_mutex_destroy(p->info->forks + i);
		pthread_mutex_destroy(&(p + i)->mx_philo);
	}
	free(info->forks);
	free(p->info);
	free(p);
	return (1);
}

void	ft_clean(t_philo *p, int n)
{
	int		i;
	long	flag;

	flag = 1;
	i = -1;
	ft_write(&p->info->flag, &flag, &p->info->mx_data);
	while (++i < n)
		pthread_join((p + i)->tid, NULL);
}

int	monitor(t_philo *p)
{
	int		i;
	int		d;
	long	s_time;

	s_time = p->info->t_start;
	i = 0;
	d = p->info->t_dead;
	while (i < p->info->n_philo)
	{
		if (ft_read(&(p + i)->n_count, &(p + i)->mx_philo) == p->info->n_mails)
		{
			ft_clean(p, p->info->n_philo);
			return (0);
		}
		if (get_time() - ft_read(&(p + i)->last_eat, &(p + i)->mx_philo) >= d)
		{
			ft_clean(p, p->info->n_philo);
			printf ("%lu\t%d\t%s\n", get_time() - s_time, (p + i)->id, "deid");
			return (0);
		}
		i = (i + 1) % p->info->n_philo;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_philo		*p;

	if (parse(av, ac))
		return (1);
	if (init_data(&p, av))
		return (1);
	if (edo_tensei(p))
		return (1);
	monitor(p);
	ft_free(p, p->info, p->info->n_philo);
	return (0);
}
