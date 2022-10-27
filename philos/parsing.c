#include "philos.h"

int	parsing(t_data *pars)
{
	if (pars->ac < 2)
		error("too few args\n");
	else
	{
		pars->num_of_philos = ft_atoi(pars->av[1], pars);
		pars->time_to_die = ft_atoi(pars->av[2], pars);
		pars->time_to_eat = ft_atoi(pars->av[3], pars);
		pars->time_to_sleep = ft_atoi(pars->av[4], pars);
		if ((pars->num_of_philos <= 0) && pars->atoi_flag == 2)
			error("Number of philos must be a positive int\n");	
		if ((pars->time_to_die) <= 0  && pars->atoi_flag == 2)
			error("Time_to_die must be a positive int\n");
		if ((pars->time_to_eat) <= 0 && pars->atoi_flag == 2)
			error("Time_to_eat must be a positive int\n");
		if ((pars->time_to_sleep) <= 0 && pars->atoi_flag == 2)
			error("Time_to_sleep must be a positive int\n");
	}
	return (0);
}
