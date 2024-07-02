/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 21:27:42 by ezahiri           #+#    #+#             */
/*   Updated: 2024/07/02 09:35:42 by ezahiri          ###   ########.fr       */
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
			while (av[i][j] || av[i][0] == '\0')
			{
				if (av[i][j] >= '0' && av[i][j] <= '9' && av[i][0] != '\0')
					j -= -1;
				else
					return (write(2, "invalid argument\n", 18));
			}
		}
	}
	else
		return (write(2, "give 4 or 5 arguments\n", 22));
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
