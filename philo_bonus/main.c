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

#include "philo_bonus.h"

static sem_t	*ft_semaphore(const char *name, unsigned int value)
{
	sem_t	*sem;

	sem = sem_open(name, O_CREAT | O_EXCL, 0644, value);
	if (sem != SEM_FAILED)
		return (sem);
	sem_unlink(name);
	return (sem_open(name, O_CREAT, S_IRUSR | S_IWUSR, value));
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
	rules->msg = ft_semaphore("/message", 1);
	rules->fork = ft_semaphore("/forks", rules->n_ph);
	rules->finish = ft_semaphore("/must_eat", 0);
	rules->dead = ft_semaphore("/dead", 0);
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
		rules->philo[i].rules = rules;
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
