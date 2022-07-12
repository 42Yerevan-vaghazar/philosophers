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
	while (time_taken < philo->data->t_to_die)
	{
		time_taken = get_millisecond(philo->start);
	}
	printf("%d %d died\n", time_taken, philo->id);
	printf("%d %ld died\n", time_taken, philo->ptid);
	pthread_exit(NULL);
}

int main(int ac, char **av)
{
	t_philo philo[N_PHILO];
	int		i;
	struct timeval start, end;
	double time_taken;
	
	if (ac != 5 && ac != 6)
		return (1);
	philo[0].data = malloc(sizeof(t_var));
	philo[0].data->n_philo = ft_atoi(av[1]);
	philo[0].data->t_to_die = ft_atoi(av[2]);
	philo[0].data->t_to_eat = ft_atoi(av[3]);
	philo[0].data->t_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		philo[0].data->n_t_to_eat = ft_atoi(av[5]);
	i = 1;
	while (i <= philo->data->n_philo)
	{
		philo[i].data = philo[0].data;
		// philo[i].data->forks.id = i;
		printf("barave\n");
		// philo[i].data->forks.lock = 0;
		gettimeofday(&philo[i].start, NULL);
		philo[i].id = i;
		philo[i].status = "is thinking";
		pthread_create(&philo[i].ptid, NULL, &start_cycle, &philo[i]);
		printf("philo.ptid = %ld\n", philo[i].ptid);
		i++;
	}
	while (1)
	{
		
	}	
	return (0);
}