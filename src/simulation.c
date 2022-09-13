/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 17:58:20 by vaghazar          #+#    #+#             */
/*   Updated: 2022/09/13 18:59:18 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_eat(t_philo *p)
{
	pthread_mutex_lock(p->mutex_fork_l);
	print_actions(p, "has taken a fork");
	pthread_mutex_lock(p->mutex_fork_r);
	print_actions(p, "has taken a fork");
	print_actions(p, "is eating");
	p->start_eat = p->r->current_time;
	p->t_tmp = 0;
	while (p->t_tmp < p->r->t_to_eat && !usleep(200))
		p->t_tmp = p->r->current_time - p->start_eat;
	pthread_mutex_unlock(p->mutex_fork_l);
	pthread_mutex_unlock(p->mutex_fork_r);
}

void	*start_cycle(void *arg_philo)
{
	t_philo	*p;

	p = arg_philo;
	if (p->id % 2 == 0)
		usleep(15000);
	while (1)
	{
		philo_eat(p);
		p->t_live = 0;
		p->start_live = p->r->current_time;
		print_actions(p, "is sleeping");
		p->t_n_eat++;
		p->start_sleep = p->r->current_time;
		p->t_tmp = 0;
		while (p->t_tmp < p->r->t_to_sleep && !usleep(200))
			p->t_tmp = p->r->current_time - p->start_sleep;
		print_actions(p, "is thinking");
	}
	return (0);
}

int	create_threads(t_global *g)
{
	int		i;

	i = -1;
	while (++i < g->n_philo)
	{
		g->p[i].r = g->p[0].r;
		g->p[i].mutex_fork_l = &(g->mutex_fork[i]);
		if (i == g->n_philo - 1)
			g->p[i].mutex_fork_r = &(g->mutex_fork[0]);
		else
			g->p[i].mutex_fork_r = &(g->mutex_fork[i + 1]);
		g->p[i].id = i + 1;
	}
	g->p->r->start_prog = get_current_time();
	g->p->r->current_time = g->p->r->start_prog;
	i = -1;
	while (++i < g->n_philo)
	{
		g->p[i].start_live = g->p->r->start_prog;
		pthread_create(&g->p[i].ptid, NULL, &start_cycle, &g->p[i]);
	}
	if (g->ac == 6)
		pthread_create(&g->eat_ptid, NULL, &ft_check_eat, g);
	return (0);
}

int	dead_check(t_global *g)
{
	int	i;

	while (!g->philo_ate && !g->is_dead)
	{
		i = 0;
		while (i < g->n_philo)
		{
			g->p->r->current_time = get_current_time();
			g->p[i].t_live = g->p->r->current_time - g->p[i].start_live;
			if (g->p->r->t_to_die < g->p[i].t_live)
			{
				print_actions(&g->p[i], "died");
				g->is_dead = 1;
				break ;
			}
			i++;
		}
	}
	return (0);
}

void	*ft_check_eat(void *arg)
{
	t_global	*g;
	int			i;

	g = arg;
	i = 0;
	while (!g->is_dead && i != g->n_philo)
	{
		i = 0;
		while (!g->is_dead && i < g->n_philo
			&& g->p[i].t_n_eat >= g->p->r->n_t_to_eat)
				i++;
	}
	g->philo_ate = 1;
	return (0);
}
