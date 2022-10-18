#ifndef PHILOS_H
# define PHILOS_H

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

typedef	struct	s_forpars
{
	int		ac;
	char	**av;
	int		forks;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
}	t_forpars;

int		ft_atoi(char *s);
int 	ft_strlen(char *s);
void	error(char *s);

#endif
