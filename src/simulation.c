/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 17:58:20 by vaghazar          #+#    #+#             */
/*   Updated: 2022/09/07 10:32:31 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_fork[philo->fork_l_id]);
	print_actions(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->mutex_fork[philo->fork_r_id]);
	print_actions(philo, "has taken a fork");
	print_actions(philo, "is eating");
	philo->start_eat = philo->data->current_time;
	philo->t_tmp = 0;
	while (philo->t_tmp < philo->data->t_to_eat && !usleep(200))
		philo->t_tmp = philo->data->current_time - philo->start_eat;
	pthread_mutex_unlock(&philo->data->mutex_fork[philo->fork_l_id]);
	pthread_mutex_unlock(&philo->data->mutex_fork[philo->fork_r_id]);
}

void	*start_cycle(void *arg_philo)
{
	t_philo	*philo;

	philo = arg_philo;
	if (philo->id % 2 == 0)
		usleep(15000);
	while (!philo->data->is_dead)
	{
		philo_eat(philo);
		philo->t_live = 0;
		philo->start_live = philo->data->current_time;
		print_actions(philo, "is sleeping");
		philo->t_n_eat++;
		philo->start_sleep = philo->data->current_time;
		philo->t_tmp = 0;
		while (philo->t_tmp < philo->data->t_to_sleep && !usleep(200))
			philo->t_tmp = philo->data->current_time - philo->start_sleep;
		print_actions(philo, "is thinking");
	}
	return (0);
}

int	create_threads(t_philo *philo)
{
	int		i;

	i = -1;
	while (++i < philo->data->n_philo)
	{
		philo[i].data = philo[0].data;
		philo[i].fork_l_id = i;
		if (i == philo->data->n_philo - 1)
			philo[i].fork_r_id = 0;
		else
			philo[i].fork_r_id = i + 1;
		philo[i].id = i + 1;
	}
	philo->data->start_prog = get_current_time();
	philo->data->current_time = philo->data->start_prog;
	i = -1;
	while (++i < philo->data->n_philo)
	{
		philo[i].start_live = philo->data->start_prog;
		pthread_create(&philo[i].ptid, NULL, &start_cycle, &philo[i]);
	}
	if (philo->data->ac == 6)
		pthread_create(&philo->data->eat_ptid, NULL, &ft_check_eat, philo);
	return (0);
}

int	dead_check(t_philo *philo)
{
	int	i;

	while (!philo->data->philo_ate && !philo->data->is_dead)
	{
		i = 0;
		while (i < philo->data->n_philo)
		{
			philo->data->current_time = get_current_time();
			philo[i].t_live = philo->data->current_time - philo[i].start_live;
			if (philo->data->t_to_die < philo[i].t_live)
			{
				print_actions(&philo[i], "died");
				philo->data->is_dead = 1;
				break ;
			}
			i++;
		}
	}
	return (0);
}

void	*ft_check_eat(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = arg;
	i = 0;
	while (i != philo->data->n_philo && !philo->data->is_dead)
	{
		i = 0;
		while (!philo->data->is_dead && i < philo->data->n_philo
			&& philo[i].t_n_eat >= philo->data->n_t_to_eat)
				i++;
	}
	philo->data->philo_ate = 1;
	return (0);
}
