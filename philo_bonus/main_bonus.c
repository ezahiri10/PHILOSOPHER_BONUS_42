/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 21:27:42 by ezahiri           #+#    #+#             */
/*   Updated: 2024/06/24 09:58:19 by ezahiri          ###   ########.fr       */
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
					return (printf ("invalid argument\n"));
			}
		}
	}
	else
		return (printf ("give 4 or 5 arguments"));
	return (0);
}

int	main(int ac, char **av)
{
	t_philo	*p;

	if (parse(av, ac) || init_data(av, &p))
		return (1);
	create_process(p);
	return (0);
}
