/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 16:31:22 by vaghazar          #+#    #+#             */
/*   Updated: 2022/09/13 18:38:37 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (*s1 && --n)
	{
		if (*s1 != *s2)
		{
			break ;
		}
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

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

long double	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_actions(t_philo *p, char *message)
{
	pthread_mutex_lock(&p->r->mutex_print);
	p->r->t_start_prog = p->r->current_time
		- p->r->start_prog;
	printf("%d %d %s %d\n", p->r->t_start_prog,
		p->id, message, p->t_n_eat);
	if (ft_strncmp(message, "died", 5))
		pthread_mutex_unlock(&p->r->mutex_print);
}

int	ft_destroy_all(t_global *general)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&general->p->r->mutex_print);
	while (i < general->n_philo)
	{
		pthread_mutex_destroy(&general->mutex_fork[i++]);
	}
	free(general->mutex_fork);
	free(general->p->r);
	free(general->p);
	return (0);
}
