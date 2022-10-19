#include "philos.h"

int main(int ac, char **av)
{
	t_forpars	pars;

//	pars = malloc(sizeof(t_forpars));
	pars.av = av;
	pars.ac = ac;
	pars.atoi_flag = 1;
	parsing(&pars);
}
