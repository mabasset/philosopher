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

#include "philo.h"

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
		while (ft_isspace(argv[i][j]) == 1)
			j++;
		if (argv[i][j] == '+')
			j++;
		if (argv[i][j] <= '0' || argv[i][j] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

long long	ft_atoi(const char *str)
{
	long long int	nb;
	int				i;
	int				sign;

	i = 0;
	nb = 0;
	sign = 1;
	while (ft_isspace(str[i]) && str[i] != '\0')
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
