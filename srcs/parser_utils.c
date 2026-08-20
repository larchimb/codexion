/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larchimb <larchimb@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 11:09:01 by larchimb          #+#    #+#             */
/*   Updated: 2026/08/20 09:59:47 by larchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	check_scheduler(const char *str)
{
	if (strcmp(str, "fifo") == 0)
		return (0);
	else if (strcmp(str, "edf") == 0)
		return (1);
	fprintf(stderr, "[ERROR]: %s isn't 'fifo' or 'edf'.\n", str);
	return (-1);
}

static int	check_values_bis(t_args *args)
{
	if (args->time_to_refractor < 0)
		return (-1);
	if (args->compiles_required == 0)
	{
		fprintf(stdout, "[INFO]: Simulation finished\n");
		return (-1);
	}
	else if (args->compiles_required < 0)
		return (-1);
	if (args->dongle_cooldown < 0)
		return (-1);
	if (args->scheduler < 0)
		return (-1);
	return (0);
}

int	check_values(t_args *args)
{
	if (args->nb_coders == 0)
	{
		fprintf(stderr, "[ERROR]: You need at least 1 coder\n");
		return (-1);
	}
	else if (args->nb_coders > 1000)
	{
		fprintf(stderr, "[ERROR]: Too many coders can make crah the program\n");
		return (-1);
	}
	else if (args->nb_coders < 1)
		return (-1);
	if (args->time_to_burnout < 0)
		return (-1);
	if (args->time_to_compile < 0)
		return (-1);
	if (args->time_to_debug < 0)
		return (-1);
	return (check_values_bis(args));
}
