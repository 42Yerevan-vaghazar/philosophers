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

int	ft_isdigit(int arg)
{
	if (!(arg <= 57 && arg >= 48))
	{
		return (0);
	}
	return (1);
}

int	valid_args(char **str, int ac)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < ac)
	{
		while (str[i][j])
		{
			if ((!ft_isdigit((int)str[i][j]) && str[i][0] != '+' )
				|| (!ft_isdigit((int)str[i][j]) && j != 0))
			{
				printf("Error: not valid\n");
				return (0);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}


// void *start_cycle(void *arg_philo)
// {
// 	t_philo 	*philo;
// 	// unsigned int	start_prog;
	
// 	usleep(100000);
// 	philo = arg_philo;
// 	philo->start_live = philo->data->start_prog;
// 	if (philo->id % 2 == 0)
// 		usleep(10000);
// 	// initializer(&philo->data->t_start_prog, &philo->t_live, &philo->t_eat, &philo->t_sleep);
// 	while (philo->t_live < philo->data->t_to_die)
// 	{
// 		if (!ft_strncmp(philo->status, "is thinking", 20))
// 		{
// 			if (philo->id == philo->data->n_philo)
// 			{
// 				if (!philo->data->fork[0].lock)
// 				{
// 					// ft_lock(philo, start_prog);
// 					pthread_mutex_lock(&philo->data->mutex[0]);
// 					philo->data->fork[0].lock = 1;
// 					philo->fork_2 = 1;
// 					printf("%d %d %s has taken a fork\n", philo->data->t_start_prog, philo->id, philo->status);
// 				}
// 				if (!philo->data->fork[philo->id -1].lock)
// 				{
// 					pthread_mutex_lock(&philo->data->mutex[philo->id -1]);
// 					philo->data->fork[philo->id -1].lock = 1;
// 					philo->fork_1 = 1;
// 					printf("%d %d %s has taken a fork\n", philo->data->t_start_prog, philo->id, philo->status);
// 				}	
// 			}
// 			else
// 			{
// 				if (!philo->data->fork[philo->id].lock)
// 				{
// 					pthread_mutex_lock(&philo->data->mutex[philo->id]);
// 					philo->data->fork[philo->id].lock = 1;
// 					philo->fork_1 = 1;
// 					printf("%d %d %s has taken a fork\n", philo->data->t_start_prog, philo->id, philo->status);
// 				}
// 				if (!philo->data->fork[philo->id - 1].lock)
// 				{
// 					pthread_mutex_lock(&philo->data->mutex[philo->id - 1]);
// 					philo->data->fork[philo->id -1].lock = 1;
// 					philo->fork_2 = 1;
// 					printf("%d %d %s has taken a fork\n", philo->data->t_start_prog, philo->id, philo->status);
// 				}
// 			}
// 			if (ft_strncmp(philo->status, "is eating", 20)
// 					&& philo->fork_1 && philo->fork_2)
// 			{
// 				philo->t_eat = 0;
// 				philo->start_eat = get_current_time();
// 				philo->status = "is eating";
// 				printf("%d %d %s is eating\n", philo->data->t_start_prog, philo->id, philo->status);
// 			}
// 		}
// 		if (philo->t_eat >= philo->data->t_to_eat
// 			&& !ft_strncmp(philo->status, "is eating", 20))
// 		{
// 			if (philo->id == philo->data->n_philo)
// 			{
// 					pthread_mutex_unlock(&philo->data->mutex[0]);
// 					philo->data->fork[0].lock = 0;
// 					philo->fork_2 = 0;
// 					pthread_mutex_unlock(&philo->data->mutex[philo->id -1]);
// 					philo->data->fork[philo->id -1].lock = 0;
// 					philo->fork_1 = 0;
// 			}
// 			else
// 			{
// 					pthread_mutex_unlock(&philo->data->mutex[philo->id]);
// 					philo->data->fork[philo->id].lock = 0;
// 					philo->fork_1 = 0;
// 					pthread_mutex_unlock(&philo->data->mutex[philo->id - 1]);
// 					philo->data->fork[philo->id -1].lock = 0;
// 					philo->fork_2 = 0;
// 			}
// 			philo->status = "is sleeping";
// 			printf("%d %d %s is sleeping\n", philo->data->t_start_prog, philo->id, philo->status);
// 			philo->start_live = get_current_time();
// 			philo->start_sleep = philo->start_live;
// 			philo->t_eat = 0;
// 			philo->t_live = 0;
// 		}
// 		if (philo->t_sleep >= philo->data->t_to_sleep 
// 			&& !ft_strncmp(philo->status, "is sleeping", 20))
// 		{
// 			philo->status = "is thinking";
// 			philo->t_sleep = 0;
// 		}
// 		if (!ft_strncmp(philo->status, "is sleeping", 20))
// 			philo->t_sleep = get_current_time() - philo->start_sleep;
// 		if (!ft_strncmp(philo->status, "is eating", 20))
// 			philo->t_eat = get_current_time() - philo->start_eat;
// 		philo->t_live = get_current_time() - philo->start_live;
// 		philo->data->t_start_prog = get_current_time() - philo->data->start_prog;
// 	}
// 	pthread_mutex_lock(&philo->data->mutex_dead);
// 	philo->data->is_dead = 0;
// 	printf("%d %d %s died-----------------\n", philo->data->t_start_prog, philo->id, philo->status);
// 	return (0);
// }