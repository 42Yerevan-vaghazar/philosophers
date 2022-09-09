/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 16:28:05 by vaghazar          #+#    #+#             */
/*   Updated: 2022/09/09 09:48:35 by vaghazar         ###   ########.fr       */
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

int	get_args(char **av, int ac, t_global *global)
{
	global->philo = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	global->philo->rules = (t_var *)malloc(sizeof(t_var));
	global->mutex_fork = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	global->n_philo = ft_atoi(av[1]);
	global->philo->rules->t_to_die = ft_atoi(av[2]);
	global->philo->rules->t_to_eat = ft_atoi(av[3]);
	global->philo->rules->t_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		global->philo[0].rules->n_t_to_eat = ft_atoi(av[5]);
		if (global->philo[0].rules->n_t_to_eat == 0)
			return (1);
	}
	global->is_dead = 0;
	global->philo->rules->t_start_prog = 0;
	global->philo_ate = 0;
	global->ac = ac;
	return (0);
}

int	ft_init(t_global *global)
{
	int	i;

	i = -1;
	while (i < global->n_philo)
	{
		global->philo[i].t_live = 0;
		global->philo[i].t_n_eat = 0;
		i++;
	}
	pthread_mutex_init(&global->philo->rules->mutex_print, NULL);
	i = -1;
	while (++i < global->n_philo)
		pthread_mutex_init(&global->mutex_fork[i], NULL);
	return (0);
}

