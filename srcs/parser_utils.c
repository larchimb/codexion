/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larchimb <larchimb@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 11:09:01 by larchimb          #+#    #+#             */
/*   Updated: 2026/08/05 11:43:31 by larchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

int	check_scheduler(const char *str)
{
	if (strcmp(str, "fifo") == 0 || strcmp(str, "FIFO") == 0)
		return (0);
	else if (strcmp(str, "edf") == 0 || strcmp(str, "EDF") == 0)
		return (1);
	return (-1);
}

int check_values(t_args *args)
{
	if (args->nb_coders < 0)
		return (-1);
	if (args->time_to_burnout < 0)
		return (-1);
	if (args->time_to_compile < 0)
		return (-1);
	if (args->time_to_debug < 0)
		return (-1);
	if (args->time_to_refractor < 0)
		return (-1);
	if (args->compiles_required < 0)
		return (-1);
	if (args->dongle_cooldown < 0)
		return (-1);
	if (args->scheduler < 0)
		return (-1);
	return (0);
}