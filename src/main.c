/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 11:01:25 by vaghazar          #+#    #+#             */
/*   Updated: 2022/07/10 17:07:48 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(const char *nptr)
{
	int	num;
	int	temp;

	num = 0;
	temp = 1;
	while (*nptr == ' ' || *nptr == '\t' || *nptr == '\n'
		|| *nptr == '\v' || *nptr == '\f' || *nptr == '\r')
	nptr++;
	if (*nptr == '-')
	{
		temp *= -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		num = (num * 10) + (*nptr - '0');
		if (!(*(nptr + 1) >= '0' && *(nptr + 1) <= '9'))
			return (num * temp);
		nptr++;
	}
	return (num * temp);
}

unsigned int get_millisecond(struct timeval start)
{
	struct timeval end;
	unsigned int time_taken;
	
	gettimeofday(&end, NULL);
	time_taken = (end.tv_sec - start.tv_sec) * 1000000;
	time_taken = (time_taken + (end.tv_usec - start.tv_usec)) / 1000;
	return (time_taken);
}

void *start_cycle(void *arg_philo)
{
	t_philo *philo;
	struct timeval start, end;
	unsigned int time_taken = 0;
	
	philo = arg_philo;
	// printf("time_taken = %d  philo->id = %d\n", time_taken, philo->id);
	printf("time_taken = %d  philo->ptid = %d\n", time_taken, philo->ptid);
	while (/*time_taken < philo->t_to_die*/ 1)
	{
		time_taken = get_millisecond(philo->start);
	}
	// printf("%d %d died\n", time_taken, philo->id);
	// printf("%d %d died\n", time_taken, philo->ptid);
	pthread_exit(NULL);
}

int main(int ac, char **av)
{
	t_philo philo[200];
	t_var	vars;
	struct timeval start, end;
	double time_taken;
	
	if (ac != 5 && ac != 6)
		return (1);
	vars.n_philo = ft_atoi(av[1]);
	vars.t_to_die = ft_atoi(av[2]);
	vars.t_to_eat = ft_atoi(av[3]);
	vars.t_to_sleep = ft_atoi(av[4]);
	philo.forks = malloc(sizeof(t_fork) * vars.n_philo);
	gettimeofday(&philo.start, NULL);
	if (ac == 6)
		philo.n_t_to_eat = ft_atoi(av[5]);
	vars.i = 1;
	while (vars.i <= vars.n_philo)
	{
		philo.forks->id = vars.i;
		philo.forks->lock = 0;
		philo.id = vars.i;
		philo.t_to_die = vars.t_to_die;
		philo.t_to_eat = vars.t_to_eat;
		philo.t_to_sleep = vars.t_to_sleep;
		philo.status = "is thinking";
		pthread_create(&philo.ptid, NULL, &start_cycle, (void *)&philo);
		printf("philo.ptid = %d\n", philo.ptid);
		vars.i++;
	}
	while (1)
	{
		
	}	
	return (0);
}