/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 17:58:20 by vaghazar          #+#    #+#             */
/*   Updated: 2022/09/09 09:50:57 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_fork_l);
	print_actions(philo, "has taken a fork");
	pthread_mutex_lock(philo->mutex_fork_r);
	print_actions(philo, "has taken a fork");
	print_actions(philo, "is eating");
	philo->start_eat = philo->rules->current_time;
	philo->t_tmp = 0;
	while (philo->t_tmp < philo->rules->t_to_eat && !usleep(200))
		philo->t_tmp = philo->rules->current_time - philo->start_eat;
	pthread_mutex_unlock(philo->mutex_fork_l);
	pthread_mutex_unlock(philo->mutex_fork_r);
}

void	*start_cycle(void *arg_philo)
{
	t_philo	*philo;

	philo = arg_philo;
	if (philo->id % 2 == 0)
		usleep(15000);
	while (1)
	{
		philo_eat(philo);
		philo->t_live = 0;
		philo->start_live = philo->rules->current_time;
		print_actions(philo, "is sleeping");
		philo->t_n_eat++;
		philo->start_sleep = philo->rules->current_time;
		philo->t_tmp = 0;
		while (philo->t_tmp < philo->rules->t_to_sleep && !usleep(200))
			philo->t_tmp = philo->rules->current_time - philo->start_sleep;
		print_actions(philo, "is thinking");
	}
	return (0);
}

int	create_threads(t_global *global)
{
	int		i;

	i = -1;
	while (++i < global->n_philo)
	{
		global->philo[i].rules = global->philo[0].rules;
		global->philo[i].mutex_fork_l = &(global->mutex_fork[i]);
		if (i == global->n_philo - 1)
			global->philo[i].mutex_fork_r = &(global->mutex_fork[0]);
		else
			global->philo[i].mutex_fork_r = &(global->mutex_fork[i + 1]);
		global->philo[i].id = i + 1;
	}
	global->philo->rules->start_prog = get_current_time();
	global->philo->rules->current_time = global->philo->rules->start_prog;
	i = -1;
	while (++i < global->n_philo)
	{
		global->philo[i].start_live = global->philo->rules->start_prog;
		pthread_create(&global->philo[i].ptid, NULL, &start_cycle, &global->philo[i]);
	}
	if (global->ac == 6)
		pthread_create(&global->eat_ptid, NULL, &ft_check_eat, global);
	return (0);
}

int	dead_check(t_global *global)
{
	int	i;
	while (!global->philo_ate && !global->is_dead)
	{
		i = 0;
		while (i < global->n_philo)
		{
			global->philo->rules->current_time = get_current_time();
			global->philo[i].t_live = global->philo->rules->current_time - global->philo[i].start_live;
			if (global->philo->rules->t_to_die < global->philo[i].t_live)
			{
				print_actions(&global->philo[i], "died");
				global->is_dead = 1;
				break ;
			}
			i++;
		}
	}
	return (0);
}

void	*ft_check_eat(void *arg)
{
	t_global	*global;
	int			i;

	global = arg;
	i = 0;
	while (i != global->n_philo)
	{
		i = 0;
		while (i < global->n_philo
				&& global->philo[i].t_n_eat >= global->philo->rules->n_t_to_eat)
				i++;
	}
	global->philo_ate = 1;
	return (0);
}
