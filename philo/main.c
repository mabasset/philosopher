/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 18:21:05 by ebondi            #+#    #+#             */
/*   Updated: 2022/04/11 18:21:05 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_forks(t_rules *rules)
{
	int	i;
	int	ph;

	ph = rules->n_ph;
	rules->forks = (pthread_mutex_t *) malloc (sizeof(pthread_mutex_t) * ph);
	i = 0;
	while (i < ph)
	{
		pthread_mutex_init(&rules->forks[i], NULL);
		i++;
	}
}

int	ft_init_rules(t_rules *rules, char *argv[])
{
	rules->n_ph = ft_atoi(argv[1]);
	rules->time_death = ft_atoi(argv[2]);
	rules->time_eat = ft_atoi(argv[3]);
	rules->time_sleep = ft_atoi(argv[4]);
	if (ft_limits(rules->n_ph) == 0 || ft_limits(rules->time_death) == 0
		|| ft_limits(rules->time_eat) == 0 || ft_limits(rules->time_sleep) == 0)
		return (0);
	rules->finish = 0;
	pthread_mutex_init(&rules->lock, NULL);
	ft_init_forks(rules);
	rules->philo = (t_philo *) malloc (sizeof(t_philo) * rules->n_ph);
	if (rules->philo == NULL)
		return (0);
	return (1);
}

void	ft_init_philo(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->n_ph)
	{
		rules->philo[i].id = i + 1;
		rules->philo[i].n_eat = 0;
		rules->philo[i].strv = 0;
		rules->philo[i].rules = rules;
		rules->philo[i].left = &rules->forks[i];
		rules->philo[i].right = &rules->forks[i + 1];
		if (i == rules->n_ph - 1)
			rules->philo[i].right = &rules->forks[0];
		else
			rules->philo[i].right = &rules->forks[i + 1];
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_rules	rules;

	if ((argc != 5 && argc != 6) || ft_checker(argc, argv) == 0)
		return (ft_error());
	if (ft_init_rules(&rules, argv) == 0)
		return (ft_error());
	ft_init_philo(&rules);
	if (rules.n_ph == 1)
	{
		printf("0 1 has taken a fork\n%lld 1 died\n", rules.time_death);
		free(rules.forks);
		free(rules.philo);
		return (0);
	}
	if (argc == 6)
	{
		rules.must_eat = ft_atoi(argv[5]);
		if (ft_limits(rules.must_eat) == 0)
			return (ft_error());
	}
	else
		rules.must_eat = -1;
	ft_thread(&rules);
	return (0);
}
