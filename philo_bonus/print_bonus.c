/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 09:53:37 by ezahiri           #+#    #+#             */
/*   Updated: 2024/06/09 13:17:52 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_putchar_fd(char c, int fd)
{
	if (fd >= 0)
		write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
		ft_putchar_fd(*s++, fd);
}

void	ft_putnbr_fd(long n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
		ft_putchar_fd(n + '0', fd);
}

void	print(t_philo *p, size_t t, char *s)
{
	sem_wait(p->info->print);
	ft_putnbr_fd(t, 1);
	ft_putchar_fd('\t', 1);
	ft_putnbr_fd(p->id, 1);
	ft_putchar_fd('\t', 1);
	ft_putstr_fd(s, 1);
	ft_putchar_fd('\n', 1);
	sem_post(p->info->print);
}
