#include "philos.h"

int main(int ac, char **av)
{
	t_data	data;
	t_philo	*philo;
	//pthread_mutex_t	forks[];

	philo = malloc(sizeof(t_philo));
	data.av = av;
	data.ac = ac;
	data.atoi_flag = 1;
	parsing(&data);
	if ((pthread_mutex_init(((t_philo *)philo)->fork1, NULL) != 0)
			|| (pthread_mutex_init(((t_philo *)philo)->fork2, NULL) != 0))
		error("Error after creating mutex\n");
	creation(&data);
}
