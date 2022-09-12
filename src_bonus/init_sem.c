/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:38:08 by vaghazar          #+#    #+#             */
/*   Updated: 2022/09/12 21:43:05 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	ft_init_sem(t_global *g)
{
	int	i;

	i = -1;
	while (i < g->n_philo)
	{
		g->p[i].t_live = 0;
		g->p[i].t_n_eat = 0;
		g->p[i].is_dead = 0;
		i++;
	}
	sem_unlink("/sem_fork");
	sem_unlink("/sem_eat_check");
	sem_unlink("/sem_print");
	sem_unlink("/sem_dead");
	g->p->r->sem_fork = sem_open("/sem_fork", O_CREAT, S_IRWXU, g->n_philo);
	g->p->r->sem_eat_check = sem_open("/sem_eat_check", O_CREAT, S_IRWXU, 0);
	g->p->r->sem_print = sem_open("/sem_print", O_CREAT, S_IRWXU, 1);
	g->p->r->sem_dead = sem_open("/sem_dead", O_CREAT, S_IRWXU, 0);
	return (0);
}

int	get_args_bonus(char **av, int ac, t_global *g)
{
	g->p = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	g->p->r = (t_rules *)malloc(sizeof(t_rules));
	g->n_philo = ft_atoi(av[1]);
	g->p->r->t_to_die = ft_atoi(av[2]);
	g->p->r->t_to_eat = ft_atoi(av[3]);
	g->p->r->t_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		g->p[0].r->n_t_to_eat = ft_atoi(av[5]);
		if (g->p[0].r->n_t_to_eat == 0)
			return (1);
	}
	g->is_dead = 0;
	g->p->r->t_start_prog = 0;
	g->philo_ate = 0;
	g->ac = ac;
	return (0);
}
