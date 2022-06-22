/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabasset <mabasset@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 11:39:36 by mabasset          #+#    #+#             */
/*   Updated: 2022/04/15 11:39:36 by mabasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	int				id;
	int				n_eat;
	long long		strv;
	int				end;
	struct s_rules	*rules;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_t		thread;
	pthread_t		monitor;
}				t_philo;

typedef struct s_rules
{
	long long		n_ph;
	long long		time_death;
	long long		time_eat;
	long long		time_sleep;
	long long		must_eat;
	long long		start;
	int				die;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	die_mutex;
	pthread_mutex_t	must_eat_mutex;
	pthread_mutex_t	philo_time;
	t_philo			*philo;
}				t_rules;

int			ft_error(void);
void		ft_starving(t_philo *ph);
void		ft_death(t_philo *ph);
int			ft_take_forks(t_philo *ph);
void		ft_routine(t_philo *ph);
void		ft_philo_msg(t_philo *ph, int id, char *str);
long long	ft_atoi(const char *str);
int			ft_checker(int argc, char *argv[]);
int			ft_limits(long long nb);
long long	ft_time(void);
void		my_sleep(long long time);
void		ft_thread(t_rules *rules);
int			check_mutex(int flag, t_philo *ph);

#endif