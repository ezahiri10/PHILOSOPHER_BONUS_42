/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 21:27:42 by ezahiri           #+#    #+#             */
/*   Updated: 2024/06/09 10:10:06 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	parse(char **av, int ac)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (ac == 6 || ac == 5)
	{
		while (++i < ac)
		{
			j = 0;
			while (av[i][j])
			{
				if (av[i][j] >= '0' && av[i][j] <= '9')
					j -= -1;
				else
					return (0);
			}
		}
	}
	else
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_philo	*p;

	if (!parse(av, ac))
		return (1);
	if (!init_data(av, &p))
		return (1);
	create_process(p);
	return (0);
}
