/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_proc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 17:58:20 by vaghazar          #+#    #+#             */
/*   Updated: 2022/09/12 21:44:00 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	philo_eat_sem(t_philo *p)
{
	sem_wait(p->r->sem_fork);
	print_actions_bonus(p, "has taken a fork");
	sem_wait(p->r->sem_fork);
	print_actions_bonus(p, "has taken a fork");
	print_actions_bonus(p, "is eating");
	p->start_eat = p->r->current_time;
	p->t_tmp = 0;
	while (p->t_tmp < p->r->t_to_eat && !usleep(200))
		p->t_tmp = get_current_time() - p->start_eat;
	sem_post(p->r->sem_fork);
	sem_post(p->r->sem_fork);
}

void	*dead_check_bonus(void *arg)
{
	int		i;
	t_philo	*p;

	p = arg;
	while (1)
	{
		i = 0;
		p->r->current_time = get_current_time();
		p->t_live = p->r->current_time - p->start_live;
		if (p->r->t_to_die < p->t_live)
		{
			print_actions_bonus(p, "died");
			exit(0);
			break ;
		}
		i++;
	}
	return (0);
}

void	*ft_check_eat_bonus(void *arg)
{
	t_global	*g;
	int			i;

	g = arg;
	i = 0;
	while (i != g->n_philo)
	{
		sem_wait(g->p->r->sem_eat_check);
		i++;
	}
	kill(g->p->pid, 15);
	return (0);
}
