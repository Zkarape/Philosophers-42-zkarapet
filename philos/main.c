#include "philos.h"

int main(int argc, char **argv)
{
	int		i;
	t_data	*data;
	t_philo	*philo;
	//pthread_mutex_t	forks[];

	i = -1;
	data = malloc(sizeof(t_data));
	philo = malloc(sizeof(t_philo));
	data->av = argv;
	data->ac = argc;
	data->atoi_flag = 1;
	parsing(data);
	while (++i < data->num_of_philos)
		if (pthread_mutex_init(&data->forks[i], NULL) !=0)
			error("Mutex initialization error\n");
	creation(data);
}
