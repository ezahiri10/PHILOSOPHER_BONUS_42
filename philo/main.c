/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 15:42:19 by ezahiri           #+#    #+#             */
/*   Updated: 2024/06/22 15:24:06 by ezahiri          ###   ########.fr       */
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

void	ft_clean(t_philo *p, int n)
{
	int		i;

	i = -1;
	ft_write(&p->info->flag, 1, &p->info->mx_data);
	while (++i < n)
		pthread_join((p + i)->tid, NULL);
}

int	check_time(t_philo *p)
{
	int	i;
	int	mail;

	i = -1;
	mail = p->info->n_mails;
	while (++i < p->info->n_philo)
	{
		if ((int)ft_read(&(p + i)->n_count, &(p + i)->mx_philo) != mail)
			return (0);
	}
	return (1);
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
		if (check_time (p) == 1)
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
