/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 12:47:51 by vaghazar          #+#    #+#             */
/*   Updated: 2022/09/08 14:22:18 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/time.h>
# include <semaphore.h>

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
	sem_t			*sem_fork;
	sem_t			*sem_print;
	sem_t			*sem_dead;
	int				is_dead;
	sem_t			*eat_ptid;
	int				philo_ate;
	sem_t			*philoAte;
	int				ac;
}				t_var;

typedef struct s_philo
{
	unsigned int	id;
	double			start_live;
	unsigned int	t_live;
	double			start_eat;
	double			start_sleep;
	unsigned int	t_tmp;
	int				fork_l_id;
	int				fork_r_id;
	unsigned int	t_n_eat;
	pthread_t		ptid;
	pid_t			pid;
	t_var			*data;
}				t_philo;

int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_atoi(const char *nptr);
int			valid_args(char **str, int ac);
void		*ft_check_eat(void *arg);
long double	get_current_time(void);
void		print_actions_bonus(t_philo *philo, char *message);
int			ft_init_sem(t_philo *philo);
int			get_args_bonus(t_philo	**arg, char **av, int ac);
void		*dead_check_bonus(void *arg);
void		*routine(void *arg_philo);
void		philo_eat_sem(t_philo *philo);
int			ft_destroy_all_bonus(t_philo *philo);
#endif
