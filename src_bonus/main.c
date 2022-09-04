#include "../includes/philo_bonus.h"

int	create_threads(t_philo *philo)
{
	int		i;
	int 	pid;

	i = -1;
	while (++i < philo->data->n_philo)
	{
		philo[i].data = philo[0].data;
		philo[i].fork_l_id = i;
		if (i == philo->data->n_philo - 1)
			philo[i].fork_r_id = 0;
		else
			philo[i].fork_r_id = i + 1;
		philo[i].id = i + 1;
	}
	philo->data->start_prog = get_current_time();
	philo->data->current_time = philo->data->start_prog;
	i = -1;
	while (++i < philo->data->n_philo)
	{
		philo[i].start_live = philo->data->start_prog;
		pid = fork();
		if (pid != 0)
			create_processes(philo);
	}
	if (philo->data->ac == 6) {
		pid = fork();
		if (pid != 0)
			ft_check_eat(philo);
	}
		// pthread_create(&philo->data->eat_ptid, NULL, &ft_check_eat, philo);
	return (0);
}

int	ft_init_semaphore(t_philo *philo)
{
	int	i;

	i = -1;
	while (i < philo->data->n_philo)
	{
		philo[i].t_live = 0;
		philo[i].t_n_eat = 0;
		i++;
	}
	philo->data->sem_dead = sem_open(NULL, 0, 1);
	sem_init(&philo->data->sem_dead, 0, 1);
	sem_init(&philo->data->sem_print, 0, 1);
	i = -1;
	while (++i < philo->data->n_philo)
		sem_init(&philo->data->sem_fork[i], 0, 1);
	return (0);
}

void	*create_processes(void *arg_philo)
{
	t_philo	*philo;

	philo = arg_philo;
	if (philo->id % 2 == 0)
		usleep(15000);
	while (!philo->data->is_dead)
	{
		philo_eat(philo);
		philo->t_live = 0;
		philo->start_live = philo->data->current_time;
		print_actions(philo, "is sleeping");
		philo->t_n_eat++;
		philo->start_sleep = philo->data->current_time;
		philo->t_tmp = 0;
		while (philo->t_tmp < philo->data->t_to_sleep && !usleep(200))
			philo->t_tmp = philo->data->current_time - philo->start_sleep;
		print_actions(philo, "is thinking");
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_philo	*philo;

	if (ac == 5 || ac == 6)
	{
		if (!valid_args(av, ac))
			return (1);
		if (get_args(&philo, av, ac))
			return (1);
		create_threads(philo);
		dead_check(philo);
	}
	else
		printf("Error: usage -> number_of_philosophers time_to_die time_to_eat\
 time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	return (0);
}
