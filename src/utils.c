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

void zero_init(t_philo **philo)
{
	int	i;

	i = 0;
	while (i < (*philo)->data->n_philo)
	{
		(*philo)[i].t_live = 0;
		(*philo)[i].t_n_eat = 0;
		i++;
	}
}

void *ft_check_eat(void *arg)
{
	t_philo *philo;
	int		i;

	philo = arg;
	while (i != philo->data->n_philo && !philo->data->is_dead)
	{
		i = 0;
		while (!philo->data->is_dead && i < philo->data->n_philo
				&& philo[i].t_n_eat >= philo->data->n_t_to_eat)
				i++;
	}
	philo->data->philo_ate = 1;
	return (0);
}