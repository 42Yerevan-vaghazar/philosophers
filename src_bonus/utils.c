/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 18:29:00 by vaghazar          #+#    #+#             */
/*   Updated: 2022/09/08 14:20:03 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	ft_destroy_all_bonus(t_philo *philo)
{
	int	i;
	int res;

	i = 0;
	while (i < philo->data->n_philo)
	{
		waitpid(-1, &res, 0);
		if (res != 0)
		{
			i = -1;
			while (++i < philo->data->n_philo)
				kill(123, 15);
			break ;
		}
		i++;
	}
	sem_close(philo->data->sem_fork);
	sem_close(philo->data->sem_dead);
	sem_close(philo->data->sem_print);
	sem_unlink("/sem_fork");
	sem_unlink("/sem_print");
	sem_unlink("/sem_dead");
	free(philo->data);
	free(philo);
	return (0);
}

void	print_actions_bonus(t_philo *philo, char *message)
{
	sem_wait(philo->data->sem_print);
	philo->data->t_start_prog = get_current_time()
		- philo->data->start_prog;
	printf("%d %d %s %d\n", philo->data->t_start_prog,
		philo->id, message, philo->t_n_eat);
	if (ft_strncmp(message, "died", 5))
		sem_post(philo->data->sem_print);
}