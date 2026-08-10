/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larchimb <larchimb@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 07:56:48 by larchimb          #+#    #+#             */
/*   Updated: 2026/08/10 14:55:15 by larchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

static t_dongle *create_dongles(t_args *args)
{
	t_dongle	*dongles;
	int 		i;

	dongles = malloc(sizeof(t_dongle) * args->nb_coders);
	if (!dongles)
		return (NULL);
	i = 0;
	while (i < args->nb_coders)
	{
	    dongles[i].state = 0;
	    dongles[i].last_release = 0;
	    pthread_mutex_init(&dongles[i].mutex, NULL);
	    i++;
	}
	return (dongles);
}

static t_coder *create_coders(t_args *args, t_dongle *dongles)
{
	t_coder		*coders;
	int 		i;

	i = 0;
	coders = malloc(sizeof(t_coder) * args->nb_coders);
	if (!coders)
		return (NULL);
	while (i < args->nb_coders)
	{
		coders[i].id = i + 1;
		coders[i].compiles_done = 0;
		coders[i].burnout = 0;
		coders[i].state = "Refactoring";
		coders[i].last_start = 0;
		coders[i].left = &dongles[i];
		coders[i].right = &dongles[(i + 1) % args->nb_coders];
		pthread_mutex_init(&coders[i].mutex, NULL);
		i++;
	}
	return (coders);
}

int	initialize_data(int ac, char **av, t_data *data)
{
	data->args = malloc(sizeof(t_args));
    if (!data->args)
		return (-1);
	if (parser(ac, av, data->args) == -1)
		return (-1);
	data->dongles = create_dongles(data->args);
	if (!data->dongles)
		return (-1);
	data->coders = create_coders(data->args, data->dongles);
	if (!data->coders)
		return (-1);
	return (0);
}
