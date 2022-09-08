/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:38:21 by vaghazar          #+#    #+#             */
/*   Updated: 2022/09/08 14:24:36 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

// #define _POSIX_SOURCE
// #include <sys/types.h>
// #include <signal.h>
// #include <unistd.h>
// #include <sys/wait.h>

int	create_proc(t_philo *philo)
{
	int		i;
	int 	pid;

	i = -1;
	while (++i < philo->data->n_philo)
	{
		philo[i].data = philo[0].data;
		philo[i].fork_l_id = i;
		if (i == philo->data->n_philo - 1)
			philo[i].fork_r_id = 0;
		else
			philo[i].fork_r_id = i + 1;
		philo[i].id = i + 1;
	}
	philo->data->start_prog = get_current_time();
	philo->data->current_time = philo->data->start_prog;
	i = -1;
	while (++i < philo->data->n_philo)
	{
		philo[i].start_live = philo->data->start_prog;
		pid = fork();
		if (pid == 0)
			routine(&philo[i]);
		else
			philo[i].pid = getpid();
	}
	// if (philo->data->ac == 6)
	// 		ft_check_eat(philo);
	return (0);
}



void	*routine(void *arg_philo)
{
	t_philo	*philo;

	philo = arg_philo;
	pthread_create(&philo->ptid, NULL, &dead_check_bonus, philo);
	if (philo->id % 2 == 0)
		usleep(15000);
	while (!philo->data->is_dead)
	{
		philo_eat_sem(philo);
		philo->t_live = 0;
		philo->start_live = get_current_time();
		print_actions_bonus(philo, "is sleeping");
		philo->t_n_eat++;
		philo->start_sleep = get_current_time();
		philo->t_tmp = 0;
		while (philo->t_tmp < philo->data->t_to_sleep && !usleep(200))
			philo->t_tmp = get_current_time() - philo->start_sleep;
		print_actions_bonus(philo, "is thinking");
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_philo	*philo;

	if (ac == 5 || ac == 6)
	{
		if (!valid_args(av, ac))
			return (1);
		if (get_args_bonus(&philo, av, ac))
			return (1);
		ft_init_sem(philo);
		create_proc(philo);
		ft_destroy_all_bonus(philo);
	}
	else
		printf("Error: usage -> number_of_philosophers time_to_die time_to_eat\
 time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	return (0);
}
