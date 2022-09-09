/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:38:21 by vaghazar          #+#    #+#             */
/*   Updated: 2022/09/09 11:02:38 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	create_proc(t_global *global)
{
	int		i;
	int 	pid;

	i = -1;
	while (++i < global->n_philo)
	{
		global->philo[i].rules = global->philo[0].rules;
		// philo[i].fork_l_id = i;
		// if (i == philo->rules->n_philo - 1)
		// 	philo[i].fork_r_id = 0;
		// else
		// 	philo[i].fork_r_id = i + 1;
		global->philo[i].id = i + 1;
	}
	global->philo->rules->start_prog = get_current_time();
	global->philo->rules->current_time = global->philo->rules->start_prog;
	i = -1;
	while (++i < global->n_philo)
	{
		global->philo[i].start_live = global->philo->rules->start_prog;
		global->philo[i].pid = fork();
		if (pid == 0)
			routine(&global->philo[i]);
	}
	// if (philo->rules->ac == 6)
	// 		ft_check_eat(philo);
	return (0);
}

void	routine(void *arg_philo)
{
	t_philo	*philo;

	philo = arg_philo;
	pthread_create(&philo->ptid, NULL, &dead_check_bonus, philo);
	if (philo->id % 2 == 0)
		usleep(15000);
	while (1)
	{
		philo_eat_sem(philo);
		philo->t_live = 0;
		philo->start_live = get_current_time();
		print_actions_bonus(philo, "is sleeping");
		philo->t_n_eat++;
		philo->start_sleep = get_current_time();
		philo->t_tmp = 0;
		while (philo->t_tmp < philo->rules->t_to_sleep && !usleep(200))
			philo->t_tmp = get_current_time() - philo->start_sleep;
		print_actions_bonus(philo, "is thinking");
	}
	exit(0);
}

int	main(int ac, char **av)
{
	t_global	global;

	if (ac == 5 || ac == 6)
	{
		if (!valid_args(av, ac))
			return (1);
		if (get_args_bonus(av, ac, &global))
			return (1);
		ft_init_sem(&global);
		create_proc(&global);
		printf("barev\n");
		ft_destroy_all_bonus(&global);
	}
	else
		printf("Error: usage -> number_of_philosophers time_to_die time_to_eat\
 time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	return (0);
}
