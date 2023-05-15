#include "philosophers.h"

int	death_check(t_philo_data *philo, int **flag_die)
{
	pthread_mutex_t	change_flag;

	pthread_mutex_lock(philo->philo_die_mutex);
	if ((return_time() - philo->start_program_time \
		- philo->time_philo) > philo->time_to_die)
	{
		pthread_mutex_lock(&change_flag);
		**flag_die = 1;
		pthread_mutex_unlock(&change_flag);
		pthread_mutex_unlock(philo->philo_die_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->philo_die_mutex);
	return (0);
}

int	end_program(t_philo_data **philo, int count)
{
	int	i;

	i = -1;
	while (++i < count)
	{
		if (philo[i]->eat_count != philo[i]->optional_argument)
			return (0);
	}
	return (1);
}

void	check_end(int count, t_philo_data ***philo, int *flag_die)
{
	int				i;
	pthread_mutex_t	print_die;

	while (1)
	{
		i = -1;
		while (++i < count)
			if (death_check((*philo)[i], &flag_die))
				break ;
		if (end_program(*philo, count))
			break ;
		if (*flag_die)
			break ;
	}
	pthread_mutex_lock(&print_die);
	if (*flag_die)
		printf(PHILO_DIE, (return_time() - \
			(*philo)[i]->start_program_time), (*philo)[i]->index_philosophers);
	pthread_mutex_unlock(&print_die);
}

void	print_philo_action(t_philo_data *philo, int flag)
{
	pthread_mutex_lock(philo->print_mutex);
	if (flag == FORK && !(*(philo->ptr_philo_die)))
		printf(PHILO_FORK, (return_time() - \
			philo->start_program_time), philo->index_philosophers);
	if (flag == EAT && !(*(philo->ptr_philo_die)))
		printf(PHILO_EAT, (return_time() - \
			philo->start_program_time), philo->index_philosophers);
	if (flag == THINK && !(*(philo->ptr_philo_die)))
		printf(PHILO_THINK, (return_time() - \
			philo->start_program_time), philo->index_philosophers);
	if (flag == SLEEP && !(*(philo->ptr_philo_die)))
		printf(PHILO_SLEEP, (return_time() - \
			philo->start_program_time), philo->index_philosophers);
	pthread_mutex_unlock(philo->print_mutex);
}
