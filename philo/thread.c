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

void	*ft_meal(void *philo)
{
	t_philo	*ph;

	ph = philo;
	ph->strv = ft_time() - ph->rules->start;
	if (ph->id % 2 == 0)
		my_sleep(ph->rules->time_eat, ph->rules);
	while (1)
	{
		ft_take_forks(ph);
		ft_philo_msg(ph->rules, ph->id, "is eating");
		ph->n_eat++;
		if (ph->n_eat == ph->rules->must_eat)
			ph->end = 1;
		ph->strv = ft_time() - ph->rules->start;
		my_sleep(ph->rules->time_eat, ph->rules);
		pthread_mutex_unlock(ph->right);
		pthread_mutex_unlock(ph->left);
		if (ph->rules->finish == 1)
			break ;
		ft_philo_msg(ph->rules, ph->id, "is sleeping");
		my_sleep(ph->rules->time_sleep, ph->rules);
		ft_philo_msg(ph->rules, ph->id, "is thinking");
	}
	return (NULL);
}

int	ft_finish(t_philo *ph)
{
	int	tmp;
	int	i;
	int	check;

	tmp = ft_time() - ph->rules->start;
	check = 0;
	i = 0;
	while (i < ph->rules->n_ph)
	{
		if (tmp - ph[i].strv > ph->rules->time_death)
		{
			ft_philo_msg(ph->rules, ph[i].id, "died");
			ph->rules->finish = 1;
			return (1);
		}
		if (ph[i].end == 1)
			check++;
		i++;
	}
	if (check == ph->rules->n_ph)
	{
		ph->rules->finish = 1;
		return (1);
	}
	return (0);
}

void	*ft_monitor(void *philo)
{
	t_philo		*ph;

	ph = philo;
	while (1)
	{
		if (ft_finish(ph) == 1)
			return (NULL);
	}
	return (NULL);
}

void	ft_exit(t_rules *rules)
{
	int		i;
	t_philo	*philo;

	philo = rules->philo;
	pthread_join(rules->death, NULL);
	i = 0;
	while (i < rules->n_ph)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < rules->n_ph)
	{
		pthread_mutex_destroy(&rules->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&rules->lock);
	free(rules->forks);
	free(philo);
}

void	ft_thread(t_rules *rules)
{
	int		i;
	t_philo	*philo;

	philo = rules->philo;
	rules->start = ft_time();
	pthread_create(&rules->death, NULL, ft_monitor, rules->philo);
	i = 0;
	while (i < rules->n_ph)
	{
		pthread_create(&philo[i].thread, NULL, ft_meal, &philo[i]);
		i++;
	}
	ft_exit(rules);
}
