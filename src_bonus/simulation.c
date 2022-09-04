/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 17:58:20 by vaghazar          #+#    #+#             */
/*   Updated: 2022/09/04 18:32:31 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	philo_eat_sem(t_philo *philo)
{
	sem_wait(&philo->data->sem_fork[philo->fork_l_id]);
	print_actions(philo, "has taken a fork");
	sem_wait(&philo->data->sem_fork[philo->fork_r_id]);
	print_actions(philo, "has taken a fork");
	print_actions(philo, "is eating");
	philo->start_eat = philo->data->current_time;
	philo->t_tmp = 0;
	while (philo->t_tmp < philo->data->t_to_eat && !usleep(200))
		philo->t_tmp = philo->data->current_time - philo->start_eat;
	sem_post(&philo->data->sem_fork[philo->fork_l_id]);
	sem_post(&philo->data->sem_fork[philo->fork_r_id]);
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