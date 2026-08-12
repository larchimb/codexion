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
	while ((ptr[i] >= 9 && ptr[i] <= 13) || ptr[i] == ' ')
		i++;
	if (ptr[i] == '+')
		i++;
	while (ptr[i] >= '0' && ptr[i] <= '9')
	{
		if (res > (LLONG_MAX - (ptr[i] - '0')) / 10)
			return (-1);
		res = res * 10 + ptr[i++] - '0';
	}
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
			return (-1);
		i++;
	}
	nbr = ft_atoi(str);
	if (nbr > INT_MAX)
		return (-1);
	return (nbr);
}

static long	check_long(const char *str)
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
			return (-1);
		i++;
	}
	nbr = ft_atoi(str);
	return ((long)nbr);
}

int	parser(int ac, char **av, t_args *args)
{
	if (ac != 9)
		return (-1);
	args->nb_coders = check_int(av[1]);
	args->time_to_burnout = check_long(av[2]);
	args->time_to_compile = check_long(av[3]);
	args->time_to_debug = check_long(av[4]);
	args->time_to_refractor = check_long(av[5]);
	args->compiles_required = check_int(av[6]);
	args->dongle_cooldown = check_long(av[7]);
	args->scheduler = check_scheduler(av[8]);
	return (check_values(args));
}
