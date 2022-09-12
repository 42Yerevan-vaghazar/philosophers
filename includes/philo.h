/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 12:47:51 by vaghazar          #+#    #+#             */
/*   Updated: 2022/09/12 21:30:51 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_rules
{
	unsigned int	t_to_think;
	unsigned int	t_to_eat;
	unsigned int	t_to_sleep;
	unsigned int	t_to_die;
	unsigned int	n_t_to_eat;
	double			start_prog;
	unsigned int	t_start_prog;
	double			current_time;
	pthread_mutex_t	mutex_print;
}				t_rules;

typedef struct s_philo
{
	unsigned int	id;
	pthread_t		ptid;
	double			start_live;
	unsigned int	t_live;
	double			start_eat;
	unsigned int	t_n_eat;
	double			start_sleep;
	unsigned int	t_tmp;
	pthread_mutex_t	*mutex_fork_l;
	pthread_mutex_t	*mutex_fork_r;
	t_rules			*r;
}				t_philo;

typedef struct s_global
{
	pthread_t		eat_ptid;
	int				n_philo;
	int				philo_ate;
	pthread_mutex_t	*mutex_fork;
	int				is_dead;
	int				ac;
	t_philo			*p;
}				t_global;

int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_atoi(const char *nptr);
int			valid_args(char **str, int ac);
void		*ft_check_eat(void *arg);
long double	get_current_time(void);
void		print_actions(t_philo *philo, char *message);
int			ft_init(t_global *general);
int			get_args(char **av, int ac, t_global *general);
int			dead_check(t_global *general);
int			create_threads(t_global *general);
void		philo_eat(t_philo *philo);
int			ft_destroy_all(t_global *general);
#endif
