/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_proc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 17:58:20 by vaghazar          #+#    #+#             */
/*   Updated: 2022/09/14 19:58:37 by vaghazar         ###   ########.fr       */
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
	p->start_eat = get_current_time();
	p->t_tmp = 0;
	while (p->t_tmp < p->r->t_to_eat && !usleep(200))
		p->t_tmp = get_current_time() - p->start_eat;
	sem_post(p->r->sem_fork);
	sem_post(p->r->sem_fork);
}

void	*dead_check_bonus(void *arg)
{
	t_philo	*p;

	p = arg;
	while (1)
	{
		if (get_current_time() - p->start_live > p->r->t_to_die)
		{
			print_actions_bonus(p, "died");
			exit(0);
			break ;
		}
		usleep(900);
	}
	return (0);
}

void	*ft_check_eat_bonus(void *arg)
{
	t_global	*g;
	int			i;

	g = arg;
	i = 0;
	while (!g->is_dead && i != g->n_philo)
	{
		sem_wait(g->p->r->sem_eat_check);
		i++;
	}
	kill(g->p->pid, 15);
	return (0);
}

void	print_actions_bonus(t_philo *p, char *message)
{
	sem_wait(p->r->sem_print);
	p->r->t_start_prog = get_current_time()
		- p->r->start_prog;
	printf("%d %d %s\n", p->r->t_start_prog,
		p->id, message);
	if (ft_strncmp(message, "died", 5))
		sem_post(p->r->sem_print);
}
