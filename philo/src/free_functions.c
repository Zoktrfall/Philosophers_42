#include "philosophers.h"

void	free_philo(t_philo_data ***philo, int count)
{
	int	i;

	i = -1;
	if (*philo == NULL)
		return ;
	while (++i < count)
	{
		if ((*philo)[i] == NULL)
			break ;
		free((*philo)[i]->thread_philo);
		free((*philo)[i]);
	}
	free(*philo);
}

void	free_mutex(pthread_mutex_t ***mutex, int count)
{
	int	i;

	i = -1;
	if (*mutex == NULL)
		return ;
	while (++i < count)
	{
		if ((*mutex)[i] == NULL)
			break ;
		pthread_mutex_destroy((*mutex)[i]);
		free((*mutex)[i]);
	}
	free(*mutex);
}

int	del_philosophers(t_philo_data ***philo, \
	pthread_mutex_t ***mutex, int mas_0, int end_program)
{
	free_philo(philo, mas_0);
	free_mutex(mutex, mas_0);
	if (end_program == MALLOC_ERROR)
		return (printf(PRINT_MALLOC_ERROR));
	if (end_program == THREAD_ERROR)
		return (printf(PRINT_THREAD_ERROR));
	if (end_program == JOIN_ERROR)
		return (printf(PRINT_JOIN_ERROR));
	return (0);
}

int	free_global(t_philo_data ***philo, \
	pthread_mutex_t *str, pthread_mutex_t *ptr)
{
	if (philo == NULL)
	{
		if (str != NULL)
			pthread_mutex_destroy(str);
		if (ptr != NULL)
			pthread_mutex_destroy(ptr);
		free(str);
		free(ptr);
		return (1);
	}
	if ((*philo)[0]->philo_die_mutex != NULL)
		pthread_mutex_destroy((*philo)[0]->philo_die_mutex);
	if ((*philo)[0]->print_mutex != NULL)
		pthread_mutex_destroy((*philo)[0]->print_mutex);
	free((*philo)[0]->philo_die_mutex);
	free((*philo)[0]->print_mutex);
	return (1);
}
