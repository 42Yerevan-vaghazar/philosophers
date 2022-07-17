/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 11:01:25 by vaghazar          #+#    #+#             */
/*   Updated: 2022/07/17 16:09:22 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

unsigned int get_millisecond(struct timeval start)
{
	struct timeval end;
	unsigned int time_taken;
	
	gettimeofday(&end, NULL);
	time_taken = (end.tv_sec - start.tv_sec) * 1000000;
	time_taken = (time_taken + (end.tv_usec - start.tv_usec)) / 1000;
	return (time_taken);
}

double	get_current_time()
{
	struct timeval time;
	double time_taken;
	
	gettimeofday(&time, NULL);
	time_taken = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	return (time_taken);
}

void *start_cycle(void *arg_philo)
{
	t_philo 	*philo;
	unsigned int	start_prog;
	
	philo = arg_philo;
	philo->start_live = philo->data->start_prog;
	if (philo->id % 2 == 0)
		usleep(10000);
	start_prog = 0;
	philo->t_live = 0;
	philo->t_eat = 0;
	philo->t_sleep = 0;
	while (philo->t_live < philo->data->t_to_die)
	{
		if (!ft_strncmp(philo->status, "is thinking", 20))
		{
			if (philo->id == philo->data->n_philo)
			{
				if (!philo->data->fork[0].lock)
				{
					pthread_mutex_lock(&philo->data->mutex[0]);
					philo->data->fork[0].lock = 1;
					philo->fork_2 = 1;
					printf("%d %d %s has taken a fork\n", start_prog, philo->id, philo->status);
				}
				if (!philo->data->fork[philo->id -1].lock)
				{
					pthread_mutex_lock(&philo->data->mutex[philo->id -1]);
					philo->data->fork[philo->id -1].lock = 1;
					philo->fork_1 = 1;
					printf("%d %d %s has taken a fork\n", start_prog, philo->id, philo->status);
				}	
			}
			else
			{
				if (!philo->data->fork[philo->id].lock)
				{
					pthread_mutex_lock(&philo->data->mutex[philo->id]);
					philo->data->fork[philo->id].lock = 1;
					philo->fork_1 = 1;
					printf("%d %d %s has taken a fork\n", start_prog, philo->id, philo->status);
				}
				if (!philo->data->fork[philo->id - 1].lock)
				{
					pthread_mutex_lock(&philo->data->mutex[philo->id - 1]);
					philo->data->fork[philo->id -1].lock = 1;
					philo->fork_2 = 1;
					printf("%d %d %s has taken a fork\n", start_prog, philo->id, philo->status);
				}
			}
			if (ft_strncmp(philo->status, "is eating", 20)
					&& philo->fork_1 && philo->fork_2)
			{
				philo->t_eat = 0;
				philo->start_eat = get_current_time();
				philo->status = "is eating";
				printf("%d %d %s is eating\n", start_prog, philo->id, philo->status);
			}
		}
		if (philo->t_eat >= philo->data->t_to_eat
			&& !ft_strncmp(philo->status, "is eating", 20))
		{
			if (philo->id == philo->data->n_philo)
			{
				if (philo->data->fork[0].lock)
				{
					pthread_mutex_unlock(&philo->data->mutex[0]);
					philo->data->fork[0].lock = 0;
					philo->fork_2 = 0;
				}
				if (philo->data->fork[philo->id -1].lock)
				{
					pthread_mutex_unlock(&philo->data->mutex[philo->id -1]);
					philo->data->fork[philo->id -1].lock = 0;
					philo->fork_1 = 0;
				}
			}
			else
			{
				if (philo->data->fork[philo->id].lock)
				{
					pthread_mutex_unlock(&philo->data->mutex[philo->id]);
					philo->data->fork[philo->id].lock = 0;
					philo->fork_1 = 0;
				}
				if (philo->data->fork[philo->id - 1].lock)
				{
					pthread_mutex_unlock(&philo->data->mutex[philo->id - 1]);
					philo->data->fork[philo->id -1].lock = 0;
					philo->fork_2 = 0;
				}
			}
			philo->status = "is sleeping";
			printf("%d %d %s is sleeping\n", start_prog, philo->id, philo->status);
			philo->start_live = get_current_time();
			philo->start_sleep = philo->start_live;
			philo->t_eat = 0;
			philo->t_live = 0;
		}
		if (philo->t_sleep >= philo->data->t_to_sleep 
			&& !ft_strncmp(philo->status, "is sleeping", 20))
		{
			philo->status = "is thinking";
			philo->t_sleep = 0;
		}
		if (!ft_strncmp(philo->status, "is sleeping", 20))
			philo->t_sleep = get_current_time() - philo->start_sleep;
		if (!ft_strncmp(philo->status, "is eating", 20))
			philo->t_eat = get_current_time() - philo->start_eat;
		philo->t_live = get_current_time() - philo->start_live;
		start_prog = get_current_time() - philo->data->start_prog;
	}
	printf("%d %d %s died\n", start_prog, philo->id, philo->status);
	exit(0);
}

void get_args(t_philo	**arg, char **av, int ac)
{
	t_philo	*philo;
	
	philo = *arg;
	philo[0].data = malloc(sizeof(t_var));
	philo[0].data->n_philo = ft_atoi(av[1]);
	philo[0].data->t_to_die = ft_atoi(av[2]);
	philo[0].data->t_to_eat = ft_atoi(av[3]);
	philo[0].data->t_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		philo[0].data->n_t_to_eat = ft_atoi(av[5]);
	philo->data->start_prog = get_current_time();
}

int	create_threads(t_philo **arg)
{
	unsigned int	i;
	t_philo	*philo;

	philo = *arg;
	i = 0;
	while (i < philo->data->n_philo)
	{
		philo[i].data = philo[0].data;
		philo[i].fork_1 = 0;
		philo[i].fork_2 = 0;
		philo[i].data->fork->lock = 0;
		philo[i].id = i + 1;
		philo[i].status = "is thinking";
		pthread_create(&philo[i].ptid, NULL, &start_cycle, &philo[i]);
		i++;
	}
	return (0);
}

int main(int ac, char **av)
{
	t_philo *philo;
	int		i;
	
	if (ac == 5 || ac == 6)
	{
		if (!valid_args(av, ac))
			return (1);
		philo = malloc(sizeof(t_philo) * ft_atoi(av[1]));
		get_args(&philo, av, ac);
		i = -1;
		while((unsigned int)++i < philo->data->n_philo)
			pthread_mutex_init(&philo[0].data->mutex[i], NULL);
		create_threads(&philo);
		while (1)
		{
			
		}
	}
	else
		printf("Error: usage -> number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	return (0);
}