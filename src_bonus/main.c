/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:38:21 by vaghazar          #+#    #+#             */
/*   Updated: 2022/09/12 21:38:30 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"
	// g->p->r->current_time = g->p->r->start_prog;

int	create_proc(t_global *g)
{
	int		i;
	int		pid;

	i = -1;
	while (++i < g->n_philo)
	{
		g->p[i].r = g->p[0].r;
		g->p[i].id = i + 1;
	}
	g->p->r->start_prog = get_current_time();
	i = -1;
	while (++i < g->n_philo)
	{
		g->p[i].start_live = g->p->r->start_prog;
		pid = fork();
		if (pid == -1)
			exit(1);
		if (pid == 0)
			routine(&g->p[i]);
		else
			g->p[i].pid = pid;
	}
	if (g->ac == 6)
		pthread_create(&g->eat_ptid, NULL, &ft_check_eat_bonus, g);
	return (0);
}

void	routine(void *arg_philo)
{
	t_philo	*p;

	p = arg_philo;
	pthread_create(&p->ptid, NULL, &dead_check_bonus, p);
	if (p->id % 2 == 0)
		usleep(15000);
	while (1)
	{
		philo_eat_sem(p);
		p->t_live = 0;
		p->start_live = get_current_time();
		print_actions_bonus(p, "is sleeping");
		p->t_n_eat++;
		if (p->t_n_eat == p->r->n_t_to_eat)
			sem_post(p->r->sem_eat_check);
		p->start_sleep = get_current_time();
		p->t_tmp = 0;
		while (p->t_tmp < p->r->t_to_sleep && !usleep(200))
			p->t_tmp = get_current_time() - p->start_sleep;
		print_actions_bonus(p, "is thinking");
	}
	exit(0);
}

int	main(int ac, char **av)
{
	t_global	g;

	if (ac == 5 || ac == 6)
	{
		if (!valid_args(av, ac))
			return (1);
		if (get_args_bonus(av, ac, &g))
			return (1);
		ft_init_sem(&g);
		create_proc(&g);
		ft_destroy_all_bonus(&g);
	}
	else
		printf("Error: usage -> number_of_philosophers time_to_die time_to_eat\
 time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	return (0);
}
