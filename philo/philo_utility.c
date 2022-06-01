/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utility.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabasset <mabasset@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:15:11 by mabasset          #+#    #+#             */
/*   Updated: 2022/06/01 16:37:00 by mabasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_mutex(int flag, t_philo *ph)
{
	int	tmp;

	tmp = 0;
	if (flag == 0)
	{
		pthread_mutex_lock(&ph->rules->die_mutex);
		tmp = ph->rules->die;
		pthread_mutex_unlock(&ph->rules->die_mutex);
	}
	else if (flag == 1)
	{
		pthread_mutex_lock(&ph->rules->must_eat_mutex);
		tmp = ph->end;
		pthread_mutex_unlock(&ph->rules->must_eat_mutex);
	}
	return (tmp);
}

void	ft_starving(t_philo *ph)
{
	pthread_mutex_lock(&ph->philo_time);
	ph->strv = ft_time() - ph->rules->start;
	pthread_mutex_unlock(&ph->philo_time);
}

void	ft_death(t_philo *ph)
{
	pthread_mutex_lock(&ph->rules->die_mutex);
	ph->rules->die = 0;
	pthread_mutex_unlock(&ph->rules->die_mutex);
}

int	ft_take_forks(t_philo *ph)
{
	pthread_mutex_lock(ph->right);
	ft_philo_msg(ph, ph->id, "has taken a fork");
	if (ph->rules->n_ph == 1)
		return (1);
	pthread_mutex_lock(ph->left);
	ft_philo_msg(ph, ph->id, "has taken a fork");
	return (0);
}

void	ft_routine(t_philo *ph)
{
	my_sleep(ph->rules->time_eat);
	pthread_mutex_unlock(ph->right);
	pthread_mutex_unlock(ph->left);
	ft_philo_msg(ph, ph->id, "is sleeping");
	my_sleep(ph->rules->time_sleep);
	ft_philo_msg(ph, ph->id, "is thinking");
}
