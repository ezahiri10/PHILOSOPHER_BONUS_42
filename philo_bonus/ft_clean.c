/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 15:54:28 by ezahiri           #+#    #+#             */
/*   Updated: 2024/06/30 16:40:44 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	sem_clean(sem_t *s, char *name)
{
	sem_close(s);
	sem_unlink(name);
}

void	ft_handler(t_data *info, int n)
{
	if (n == 1)
		sem_clean(info->fork, "fork");
	else if (n == 2)
	{
		sem_clean(info->full, "full");
		ft_handler(info, n - 1);
	}
	else if (n == 3)
	{
		sem_clean(info->death, "death");
		ft_handler(info, n - 1);
	}
	else if (n == 4)
	{
		sem_clean(info->print, "print");
		ft_handler(info, n - 1);
	}
	write (2, "Sem_open failed\n", 17);
}
