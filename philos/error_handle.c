#include "philos.h"

void	error(char *s)
{
	write(2, s, ft_strlen(s));
	exit(1);
}
