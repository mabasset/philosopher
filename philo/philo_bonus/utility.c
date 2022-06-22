/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabasset <mabasset@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 11:39:49 by mabasset          #+#    #+#             */
/*   Updated: 2022/04/15 11:39:49 by mabasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_error(void)
{
	write(2, "error\n", 6);
	return (1);
}

int	ft_limits(long long nb)
{
	if (nb < 0 || nb > 2147483647)
		return (0);
	return (1);
}

int	ft_checker(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] == ' ' || (argv[i][j] >= 9 && argv[i][j] <= 13))
			j++;
		if (argv[i][j] == '+')
			j++;
		if (argv[i][j] <= '0' || argv[i][j] > '9')
			return (0);
		i++;
	}
	return (1);
}

long long	ft_atoi(const char *str)
{
	long long	nb;
	int			i;
	int			sign;

	i = 0;
	nb = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb *= 10;
		nb += str[i] - '0';
		i++;
	}
	nb *= sign;
	return (nb);
}

void	ft_exit(t_rules *rules)
{
	int		i;

	i = 0;
	while (i < rules->n_ph)
	{
		kill(rules->philo[i].pid, SIGKILL);
		i++;
	}
	sem_close(rules->fork);
	sem_unlink("/forks");
	sem_close(rules->msg);
	sem_unlink("/message");
	sem_close(rules->dead);
	sem_unlink("/dead");
	sem_close(rules->finish);
	sem_unlink("/must_eat");
	free(rules->philo);
}
