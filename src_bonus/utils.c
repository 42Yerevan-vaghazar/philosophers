/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 18:29:00 by vaghazar          #+#    #+#             */
/*   Updated: 2022/09/09 11:04:11 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	ft_destroy_all_bonus(t_global *global)
{
	int	i;
	int res;

	i = 0;
	while (i < global->n_philo)
	{
		waitpid(-1, &res, 0);
		if (res != 0)
		{
			i = -1;
			while (++i < global->n_philo)
				kill(global->philo->pid, 15);
			break ;
		}
		i++;
	}
	sem_close(global->philo->sem_fork);
	sem_close(global->philo->sem_dead);
	sem_close(global->philo->sem_print);
	sem_unlink("/sem_fork");
	sem_unlink("/sem_print");
	sem_unlink("/sem_dead");
	free(global->philo->rules);
	free(global->philo);
	return (0);
}

void	print_actions_bonus(t_philo *philo, char *message)
{
	sem_wait(philo->sem_print);
	philo->rules->t_start_prog = get_current_time()
		- philo->rules->start_prog;
	printf("%d %d %s %d\n", philo->rules->t_start_prog,
		philo->id, message, philo->t_n_eat);
	if (ft_strncmp(message, "died", 5))
		sem_post(philo->sem_print);
}