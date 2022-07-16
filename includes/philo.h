/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 12:47:51 by vaghazar          #+#    #+#             */
/*   Updated: 2022/07/10 17:24:02 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include <sys/time.h>
// #include <stddef.h>
#define N_PHILO 200

typedef struct s_fork
{
	int		id;
	int		lock;
}				t_fork;

typedef struct s_var
{
	unsigned int    t_to_think;
	unsigned int    t_to_eat;
	unsigned int    t_to_sleep;
	unsigned int    t_to_die;
	unsigned int	n_t_to_eat;
	unsigned int	n_philo;
	double			start_prog;
	struct			timeval start_time;
	t_fork			fork[N_PHILO];
	pthread_mutex_t	mutex[N_PHILO];
}				t_var;

typedef struct s_philo
{
	int				id;
	pthread_t		ptid;
	struct			timeval restart_time;
	double			start_live;
	double			start_eat;
	double			start_sleep;
	unsigned int	t_live;
	unsigned int	t_eat;
	unsigned int	t_sleep;
	char			*status;
	int				fork_1;
	int				fork_2;
	t_var			*data;
}				t_philo;

int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	ft_atoi(const char *nptr);


#endif
