/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:38:08 by vaghazar          #+#    #+#             */
/*   Updated: 2022/09/09 10:18:14 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	ft_init_sem(t_global *global)
{
	int	i;

	i = -1;
	while (i < global->n_philo)
	{
		global->philo[i].t_live = 0;
		global->philo[i].t_n_eat = 0;
		i++;
	}
	sem_unlink("/sem_fork");
	sem_unlink("/sem_print");
	sem_unlink("/sem_dead");
	global->philo->sem_fork = sem_open("/sem_fork", O_CREAT, S_IRWXU, global->n_philo);
	global->philo->sem_print = sem_open("/sem_print", O_CREAT, S_IRWXU, 1);
	global->philo->sem_dead = sem_open("/sem_dead", O_CREAT, S_IRWXU, 0);
	return (0);
}

int	get_args_bonus(char **av, int ac, t_global *global)
{
	global->philo = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	global->philo->rules = (t_var *)malloc(sizeof(t_var));
	global->philo->sem_fork = malloc(sizeof(t_philo) * ft_atoi(av[1]));
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