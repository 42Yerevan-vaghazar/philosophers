/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 18:29:00 by vaghazar          #+#    #+#             */
/*   Updated: 2022/09/14 19:58:32 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	ft_destroy_helper(t_global *g)
{
	sem_close(g->p->r->sem_fork);
	sem_close(g->p->r->sem_dead);
	sem_close(g->p->r->sem_print);
	sem_close(g->p->r->sem_eat_check);
	sem_unlink("/sem_fork");
	sem_unlink("/sem_print");
	sem_unlink("/sem_dead");
	sem_unlink("/sem_eat_check");
	free(g->p->r);
	free(g->p);
}

void	ft_destroy_all_bonus(t_global *g)
{
	int	i;
	int	res;

	i = -1;
	while (++i < g->n_philo)
	{
		waitpid(-1, &res, 0);
		if (WEXITSTATUS(res) == 0 && ++g->is_dead)
		{
			sem_post(g->p->r->sem_eat_check);
			i = -1;
			while (++i < g->n_philo)
				kill(g->p[i].pid, 15);
			break ;
		}
	}
	ft_destroy_helper(g);
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

long double	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
