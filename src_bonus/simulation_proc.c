/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_proc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 17:58:20 by vaghazar          #+#    #+#             */
/*   Updated: 2022/09/08 14:22:36 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	philo_eat_sem(t_philo *philo)
{
	sem_wait(philo->data->sem_fork);
	print_actions_bonus(philo, "has taken a fork");
	sem_wait(philo->data->sem_fork);
	print_actions_bonus(philo, "has taken a fork");
	print_actions_bonus(philo, "is eating");
	philo->start_eat = philo->data->current_time;
	philo->t_tmp = 0;
	while (philo->t_tmp < philo->data->t_to_eat && !usleep(200))
		philo->t_tmp =  get_current_time() - philo->start_eat;
	sem_post(philo->data->sem_fork);
	sem_post(philo->data->sem_fork);
}

void	*dead_check_bonus(void *arg)
{
	int	i;
	t_philo *philo;

	philo = arg;
	while (!philo->data->is_dead)
	{
		i = 0;
		philo->data->current_time = get_current_time();
		philo->t_live = philo->data->current_time - philo->start_live;
		if (philo->data->t_to_die < philo->t_live)
		{
			print_actions_bonus(philo, "died");
			philo->data->is_dead = 1;
			break ;
		}
		i++;
	}
	return (0);
}