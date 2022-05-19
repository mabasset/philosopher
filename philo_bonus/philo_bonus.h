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

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_philo
{
	int				id;
	int				n_eat;
	long long		strv;
	struct s_rules	*rules;
	pid_t			pid;
	pthread_t		death;
}				t_philo;

typedef struct s_rules
{
	long long		n_ph;
	long long		time_death;
	long long		time_eat;
	long long		time_sleep;
	long long		must_eat;
	long long		start;
	pthread_t		finish_eat;
	sem_t			*msg;
	sem_t			*fork;
	sem_t			*finish;
	sem_t			*dead;
	t_philo			*philo;
}				t_rules;

int			ft_error(void);
void		ft_philo_msg(t_rules *rules, int id, char *str);
int			ft_isspace(char c);
long long	ft_atoi(const char *str);
int			ft_checker(int argc, char *argv[]);
int			ft_limits(long long nb);
long long	ft_time(void);
void		my_sleep(long long time, t_rules *rules);
void		ft_thread(t_rules *rules);
void		ft_exit(t_rules *rules);

#endif