#include "philos.h"

int	parsing(t_forpars *pars)
{
	if (pars->ac < 2)
		error("too few args\n");
	else
	{
		pars->forks = ft_atoi(pars->av[1]);
		pars->time_to_die = ft_atoi(pars->av[2]);
		pars->time_to_eat = ft_atoi(pars->av[3]);
		pars->time_to_sleep = ft_atoi(pars->av[4]);
		if ((pars->forks) < 0)
			error("Number of philos must be positive int\n");	
		if ((pars->time_to_die) < 0)
			error("Time_to_die must be positive int\n");
		if ((pars->time_to_eat) < 0)
			error("Time_to_eat must be positive int\n");
		if ((pars->time_to_sleep) < 0)
			error("Time_to_sleep must be positive int\n");
	}
}
