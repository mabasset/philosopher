/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabasset <mabasset@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 18:34:03 by mabasset          #+#    #+#             */
/*   Updated: 2022/04/15 18:34:03 by mabasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_mutex(int flag, t_philo *ph)
{
	int tmp;

	tmp = 0;
	if (flag == 0)
	{
		pthread_mutex_lock(&ph->rules->die_mutex);
		tmp = ph->rules->die;
		pthread_mutex_unlock(&ph->rules->die_mutex);
	}
	else if (flag == 1)
	{
		pthread_mutex_lock(&ph->rules->end_meal_mutex);
		tmp = ph->rules->end_meal;
		pthread_mutex_unlock(&ph->rules->end_meal_mutex);
	}
	else if (flag == 2)
	{
		pthread_mutex_lock(&ph->rules->must_eat_mutex);
		tmp = ph->end;
		pthread_mutex_unlock(&ph->rules->must_eat_mutex);
	}
	return (tmp);
}

int	ft_finish(t_philo *ph)
{
	int	tmp;
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (i < ph->rules->n_ph)
	{
		pthread_mutex_lock(&ph[i].philo_time);
		tmp = ft_time() - ph->rules->start - ph[i].strv;
		pthread_mutex_unlock(&ph[i].philo_time);
		if (tmp > ph->rules->time_death)
		{
			ft_philo_msg(&ph[i], ph[i].id, "died");
			pthread_mutex_lock(&ph->rules->die_mutex);
			ph->rules->die = 0;
			pthread_mutex_unlock(&ph->rules->die_mutex);
			return (1);
		}
		if (check_mutex(2, &ph[i]))
			check++;
		i++;
	}
	if (check == ph->rules->n_ph)
	{
		pthread_mutex_lock(&ph->rules->die_mutex);
		ph->rules->die = 0;
		pthread_mutex_unlock(&ph->rules->die_mutex);
	}
	return (0);
}

void	ft_monitor(void *philo)
{
	t_philo		*ph;

	ph = philo;
	while (1)
	{
		if (ft_finish(ph) == 1)
			break ;
	}
}

void	*ft_meal(void *philo)
{
	t_philo		*ph;

	ph = philo;
	pthread_mutex_lock(&ph->philo_time);
	ph->strv = ft_time() - ph->rules->start;
	pthread_mutex_unlock(&ph->philo_time);
	if (ph->id % 2 == 0)
		my_sleep(ph->rules->time_eat);
	while (check_mutex(0, ph) && check_mutex(1, ph))
	{
		if (ft_take_forks(ph) == 1)
			break ;
		ft_philo_msg(ph, ph->id, "is eating");
		ph->n_eat++;
		if (ph->n_eat == ph->rules->must_eat)
		{
			pthread_mutex_lock(&ph->rules->must_eat_mutex);
			ph->end = 1;
			pthread_mutex_unlock(&ph->rules->must_eat_mutex);
		}
		pthread_mutex_lock(&ph->philo_time);
		ph->strv = ft_time() - ph->rules->start;
		pthread_mutex_unlock(&ph->philo_time);
		my_sleep(ph->rules->time_eat);
		pthread_mutex_unlock(ph->right);
		pthread_mutex_unlock(ph->left);
		ft_philo_msg(ph, ph->id, "is sleeping");
		my_sleep(ph->rules->time_sleep);
		ft_philo_msg(ph, ph->id, "is thinking");
	}
	return (NULL);
}

void	ft_exit(t_rules *rules)
{
	int		i;
	t_philo	*philo;

	philo = rules->philo;
	i = 0;
	while (i < rules->n_ph)
	{
		pthread_mutex_destroy(&rules->forks[i]);
		pthread_mutex_destroy(&rules->philo[i].philo_time);
		i++;
	}
	pthread_mutex_destroy(&rules->lock);
	pthread_mutex_destroy(&rules->die_mutex);
	pthread_mutex_destroy(&rules->end_meal_mutex);
	pthread_mutex_destroy(&rules->must_eat_mutex);
	free(philo);
	free(rules->forks);
}

void	ft_thread(t_rules *rules)
{
	int		i;
	t_philo	*philo;

	philo = rules->philo;
	rules->start = ft_time();
	i = 0;
	while (i < rules->n_ph)
	{
		pthread_create(&philo[i].thread, NULL, ft_meal, &philo[i]);
		i++;
	}
	ft_monitor(philo);
	i = 0;
	while (i < rules->n_ph)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	ft_exit(rules);
}
