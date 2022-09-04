/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 12:47:51 by vaghazar          #+#    #+#             */
/*   Updated: 2022/09/04 17:59:13 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_var
{
	unsigned int	t_to_think;
	unsigned int	t_to_eat;
	unsigned int	t_to_sleep;
	unsigned int	t_to_die;
	unsigned int	n_t_to_eat;
	int				n_philo;
	double			start_prog;
	unsigned int	t_start_prog;
	double			current_time;
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_dead;
	int				is_dead;
	pthread_t		eat_ptid;
	int				philo_ate;
	int				ac;
}				t_var;

typedef struct s_philo
{
	unsigned int	id;
	pthread_t		ptid;
	double			start_live;
	unsigned int	t_live;
	double			start_eat;
	double			start_sleep;
	unsigned int	t_tmp;
	int				fork_l_id;
	int				fork_r_id;
	unsigned int	t_n_eat;
	t_var			*data;
}				t_philo;

int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_atoi(const char *nptr);
int			valid_args(char **str, int ac);
void		*ft_check_eat(void *arg);
long double	get_current_time(void);
void		print_actions(t_philo *philo, char *message);
int			ft_init(t_philo *philo);
int			get_args(t_philo	**arg, char **av, int ac);
int			dead_check(t_philo *philo);
int			create_threads(t_philo *philo);
void		philo_eat(t_philo *philo);
#endif
