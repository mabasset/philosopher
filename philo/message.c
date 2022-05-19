/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabasset <mabasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 22:54:42 by mabasset          #+#    #+#             */
/*   Updated: 2022/05/09 23:26:31 by mabasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	my_sleep(long long time, t_rules *rules)
{
	long long	tmp;

	tmp = ft_time();
	while (time > ft_time() - tmp)
	{
		if (rules->finish == 1)
			break ;
		usleep(50);
	}
}

void	ft_philo_msg(t_rules *rules, int id, char *str)
{
	pthread_mutex_lock(&rules->lock);
	if (rules->finish == 0)
	{
		printf("%lld ", ft_time() - rules->start);
		printf("%d %s\n", id, str);
	}
	pthread_mutex_unlock(&rules->lock);
}
