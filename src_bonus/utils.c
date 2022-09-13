/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 18:29:00 by vaghazar          #+#    #+#             */
/*   Updated: 2022/09/13 21:48:08 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	ft_destroy_helper(t_global *g)
{
	sem_close(g->p->r->sem_fork);
	sem_close(g->p->r->sem_dead);
	sem_close(g->p->r->sem_print);
	sem_close(g->p->r->sem_eat_check);
	sem_unlink("/sem_fork");
	sem_unlink("/sem_print");
	sem_unlink("/sem_dead");
	sem_unlink("/sem_eat_check");
	free(g->p->r);
	free(g->p);
}

void	ft_destroy_all_bonus(t_global *g)
{
	int	i;
	int	res;

	i = -1;
	while (++i < g->n_philo)
	{
		waitpid(-1, &res, 0);
		if (WEXITSTATUS(res) == 0 && ++g->is_dead)
		{
			sem_post(g->p->r->sem_eat_check);
			i = -1;
			while (++i < g->n_philo)
				kill(g->p[i].pid, 15);
			break ;
		}
	}
	ft_destroy_helper(g);
}

void	print_actions_bonus(t_philo *p, char *message)
{
	sem_wait(p->r->sem_print);
	p->r->t_start_prog = p->r->current_time
		- p->r->start_prog;
	printf("%d %d %s %d\n", p->r->t_start_prog,
		p->id, message, p->t_n_eat);
	if (ft_strncmp(message, "died", 5))
		sem_post(p->r->sem_print);
}
