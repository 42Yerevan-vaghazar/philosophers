/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 16:28:05 by vaghazar          #+#    #+#             */
/*   Updated: 2022/09/12 21:31:21 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_isdigit(int arg)
{
	if (!(arg <= 57 && arg >= 48))
	{
		return (0);
	}
	return (1);
}

int	valid_args(char **str, int ac)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < ac)
	{
		while (str[i][j])
		{
			if ((!ft_isdigit((int)str[i][j]) && str[i][0] != '+' )
				|| (!ft_isdigit((int)str[i][j]) && j != 0))
			{
				printf("Error: not valid\n");
				return (0);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

int	get_args(char **av, int ac, t_global *g)
{
	g->p = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	g->p->r = (t_rules *)malloc(sizeof(t_rules));
	g->mutex_fork = malloc(sizeof(t_philo) * ft_atoi(av[1]));
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

int	ft_init(t_global *g)
{
	int	i;

	i = -1;
	while (i < g->n_philo)
	{
		g->p[i].t_live = 0;
		g->p[i].t_n_eat = 0;
		i++;
	}
	pthread_mutex_init(&g->p->r->mutex_print, NULL);
	i = -1;
	while (++i < g->n_philo)
		pthread_mutex_init(&g->mutex_fork[i], NULL);
	return (0);
}
