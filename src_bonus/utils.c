/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 18:29:00 by vaghazar          #+#    #+#             */
/*   Updated: 2022/09/04 18:31:09 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

// int	ft_destroy_all(t_philo *philo)
// {
// 	int	i;

// 	i = 0;
// 	pthread_mutex_destroy(&philo->data->mutex_dead);
// 	pthread_mutex_destroy(&philo->data->mutex_print);
// 	while (i < philo->data->n_philo)
// 	{
// 		pthread_mutex_destroy(&philo->data->mutex_fork[i++]);
// 	}
// 	free(philo->data->mutex_fork);
// 	free(philo->data);
// 	free(philo);
// 	return (0);
// }

void	print_actions_sem(t_philo *philo, char *message)
{
	sem_wait(&philo->data->sem_print);
	philo->data->t_start_prog = philo->data->current_time
		- philo->data->start_prog;
	printf("%d %d %s %d\n", philo->data->t_start_prog,
		philo->id, message, philo->t_n_eat);
	if (ft_strncmp(message, "died", 5))
		sem_post(&philo->data->sem_print);
}