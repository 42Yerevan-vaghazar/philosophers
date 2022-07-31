/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 11:01:25 by vaghazar          #+#    #+#             */
/*   Updated: 2022/07/31 15:34:36 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long double	get_current_time()
{
	struct timeval time;
	long double time_taken;
	gettimeofday(&time, NULL);
	time_taken = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	return (time_taken);
}

void print_actions(t_philo *philo,char *message)
{
	philo->data->t_start_prog = philo->data->current_time - philo->data->start_prog;
	printf("%d %d %s\n", philo->data->t_start_prog, philo->id, message);
}

void *start_cycle(void *arg_philo)
{
	t_philo 	*philo;
	
	philo = arg_philo;
	if (philo->id % 2 == 0)
		usleep(15000);
		// usleep(100000);
	while (1)
	{
		pthread_mutex_lock(&philo->data->mutex[philo->fork_l_id]);
		print_actions(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->mutex[philo->fork_r_id]);
		print_actions(philo, "has taken a fork");
		philo->t_eat = 0;
		philo->start_eat = philo->data->current_time;
		print_actions(philo, "is eating");
		while (philo->t_eat <= philo->data->t_to_eat)
			philo->t_eat = philo->data->current_time - philo->start_eat;
		pthread_mutex_unlock(&philo->data->mutex[philo->fork_l_id]);
		pthread_mutex_unlock(&philo->data->mutex[philo->fork_r_id]);
		philo->t_n_eat++;
		philo->t_live = 0;
		while (philo->t_func_checker)
		{
		}
		philo->start_live = philo->data->current_time;
		philo->start_sleep = philo->start_live;
		print_actions(philo, "is sleeping");
		philo->t_sleep = 0;
		while (philo->t_sleep <= philo->data->t_to_sleep)
			philo->t_sleep = philo->data->current_time - philo->start_sleep;
		print_actions(philo, "is thinking");
	}
	pthread_mutex_lock(&philo->data->mutex_dead);
	// philo->data->is_dead = 0;
	return (0);
}



void get_args(t_philo	**arg, char **av, int ac)
{
	t_philo	*philo;
	
	*arg = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	philo = *arg;
	philo[0].data = malloc(sizeof(t_var));
	(*arg)->data->mutex = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	philo[0].data->n_philo = ft_atoi(av[1]);
	philo[0].data->t_to_die = ft_atoi(av[2]);
	philo[0].data->t_to_eat = ft_atoi(av[3]);
	philo[0].data->t_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		philo[0].data->n_t_to_eat = ft_atoi(av[5]);
	philo->data->is_dead = 1;
	philo->data->t_start_prog = 0;
}

int	create_threads(t_philo **arg)
{
	int		i;
	t_philo	*philo;

	philo = *arg;
	i = 0;
	// philo->data->start_prog = get_current_time();
	while (i < philo->data->n_philo)
	{
		// philo[i].start_live = philo->data->start_prog;
		philo[i].data = philo[0].data;
		philo[i].fork_l_id = i;
		if (i == philo->data->n_philo - 1)
			philo[i].fork_r_id = 0;
		else
			philo[i].fork_r_id = i + 1;
		philo[i].id = i + 1;
		philo[i].status = "is thinking";
		philo[i].t_func_checker = 0;
		zero_initializer(&philo[i].t_n_eat, &philo[i].t_live, &philo[i].t_eat, &philo[i].t_sleep);
		// printf("philo->t_live) = %d\n", philo[i].t_live);
		i++;
	}
	// philo->data->start_prog = get_current_time();
	i = 0;
	philo->data->start_prog = get_current_time();
	philo->data->current_time = philo->data->start_prog;
	i = 0;
	while (i < philo->data->n_philo)
	{
		philo[i].start_live = philo->data->start_prog;
		pthread_create(&philo[i].ptid, NULL, &start_cycle, &philo[i]);
		i++;
	}
	return (0);
}

int main(int ac, char **av)
{
	t_philo 		*philo;
	int	i;
	
	if (ac == 5 || ac == 6)
	{
		if (!valid_args(av, ac))
			return (1);
		get_args(&philo, av, ac);
		pthread_mutex_init(&philo->data->mutex_dead, NULL);
		i = -1;
		while(++i < philo->data->n_philo)
			pthread_mutex_init(&philo->data->mutex[i], NULL);
		create_threads(&philo);
		i = 0;
		// usleep(1000000);
		// philo[i].start_live = get_current_time();
		// printf("philo[i].t_live = %d\n", philo[i].t_live);

		while (philo->data->t_to_die > philo[i].t_live)
		{
			// if (!philo->data->is_dead)
			// {
			// 	printf("barvee\n");
			// 	break;
			// }
			philo[i].t_func_checker = 1;
			philo->data->current_time = get_current_time();
			philo[i].t_live = philo->data->current_time - philo[i].start_live;
			// philo[i].t_live = get_current_time() - philo[i].start_live;
			philo[i].t_func_checker = 0;
			
			// usleep(1100);
			// printf("i = %d , %d\n", i, philo[i].t_live);
		// printf("%d\n", philo[i].t_live);
			// // printf("i = %d philo[i].t_live = %d\n", i, philo[i].t_live);
			if (i == philo->data->n_philo - 1)
				i = -1;
			i++;
		}
		print_actions(&philo[i], "died");
		free(philo->data->mutex);
		free(philo->data);
		free(philo);
	}
	else
		printf("Error: usage -> number_of_philosophers time_to_die time_to_eat\
 time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	return (0);
}