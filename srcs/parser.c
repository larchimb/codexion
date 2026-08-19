/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larchimb <larchimb@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 15:37:53 by larchimb          #+#    #+#             */
/*   Updated: 2026/08/03 15:37:53 by larchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

static long long	ft_atoi(const char *ptr)
{
	long long	res;
	int			i;

	i = 0;
	res = 0;
	if (strlen(ptr) > 17)
		return (-1);
	while ((ptr[i] >= 9 && ptr[i] <= 13) || ptr[i] == ' ')
		i++;
	if (ptr[i] == '+')
		i++;
	while (ptr[i] >= '0' && ptr[i] <= '9')
		res = res * 10 + ptr[i++] - '0';
	return (res);
}

static int	check_int(const char *str)
{
	int			i;
	long long	nbr;

	i = 0;
	if (str[i] == '+')
		i++;
	if (!str[i])
		return (-1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			fprintf(stderr, "[ERROR]: %s isn't a positive integer\n", str);
			return (-1);
		}
		i++;
	}
	nbr = ft_atoi(str);
	if (nbr > INT_MAX || nbr == -1)
	{
		fprintf(stderr, "[ERROR]: %s is superior to INT_MAX\n", str);
		return (-1);
	}
	return (nbr);
}

int	parser(int ac, char **av, t_args *args)
{
	if (ac != 9)
	{
		fprintf(stderr, "[ERROR]: There is %d arguments, need 9.\n", ac);
		return (-1);
	}
	args->nb_coders = check_int(av[1]);
	args->time_to_burnout = check_int(av[2]);
	args->time_to_compile = check_int(av[3]);
	args->time_to_debug = check_int(av[4]);
	args->time_to_refractor = check_int(av[5]);
	args->compiles_required = check_int(av[6]);
	args->dongle_cooldown = check_int(av[7]);
	args->scheduler = check_scheduler(av[8]);
	return (check_values(args));
}
