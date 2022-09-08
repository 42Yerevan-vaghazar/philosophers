/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:38:08 by vaghazar          #+#    #+#             */
/*   Updated: 2022/09/08 13:47:03 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	ft_init_sem(t_philo *philo)
{
	int	i;

	i = -1;
	while (i < philo->data->n_philo)
	{
		philo[i].t_live = 0;
		philo[i].t_n_eat = 0;
		i++;
	}
	sem_unlink("/sem_fork");
	sem_unlink("/sem_print");
	sem_unlink("/sem_dead");
	philo->data->sem_fork = sem_open("/sem_fork", O_CREAT, S_IRWXU, philo->data->n_philo);
	philo->data->sem_print = sem_open("/sem_print", O_CREAT, S_IRWXU, 1);
	philo->data->sem_dead = sem_open("/sem_dead", O_CREAT, S_IRWXU, 1);
	return (0);
}

int	get_args_bonus(t_philo	**arg, char **av, int ac)
{
	t_philo	*philo;

	*arg = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	philo = *arg;
	philo->data = (t_var *)malloc(sizeof(t_var));
	(*arg)->data->sem_fork = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	philo->data->n_philo = ft_atoi(av[1]);
	philo->data->t_to_die = ft_atoi(av[2]);
	philo->data->t_to_eat = ft_atoi(av[3]);
	philo->data->t_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		philo[0].data->n_t_to_eat = ft_atoi(av[5]);
		if (philo[0].data->n_t_to_eat == 0)
			return (1);
	}
	philo->data->is_dead = 0;
	philo->data->t_start_prog = 0;
	philo->data->philo_ate = 0;
	philo->data->ac = ac;
	return (0);
}