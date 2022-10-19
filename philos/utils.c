#include "philos.h"

int ft_atoi(char *s, t_forpars *pars)
{
	int i = 0;
	int res = 0;
 	while ((s[i] >= 9 && s[i] <= 13) || s[i] == ' ')
		i++;
	if (s[i] == '+')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10 + (s[i] - 48);
		i++;
	}
	if ((s[i] < 48 || s[i] > 57) && s[i])
		pars->atoi_flag = 2;
	if (!s[i])
		return (res);
	return (0);
}

int ft_strlen(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		;
	return (i);
}
