/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larchimb <larchimb@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 07:56:48 by larchimb          #+#    #+#             */
/*   Updated: 2026/08/19 13:15:21 by larchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	initialize_data_struc(t_data *data)
{
	data->args = NULL;
	data->coders = NULL;
	data->dongles = NULL;
	pthread_mutex_init(&data->stop_mutex, NULL);
	pthread_mutex_init(&data->d_mutex, NULL);
	if (pthread_cond_init(&data->cond, NULL) != 0)
		return (-1);
	data->stop = 0;
	data->starting_time = get_time_ms();
	data->thread_created = 0;
	data->next_ticket = 0;
	return (0);
}

static t_dongle	*create_dongles(t_args *args)
{
	t_dongle	*dongles;
	int			i;

	dongles = malloc(sizeof(t_dongle) * args->nb_coders);
	if (!dongles)
	{
		fprintf(stderr, "[ERROR]: Memory allocation for dongles failed\n");
		return (NULL);
	}
	memset(dongles, 0, sizeof(t_dongle) * args->nb_coders);
	i = 0;
	while (i < args->nb_coders)
	{
		dongles[i].state = 1;
		dongles[i].last_release = get_time_ms() - (args->dongle_cooldown + 1);
		i++;
	}
	return (dongles);
}

static t_coder	*create_coders(t_data *data, t_args *args, t_dongle *dongles)
{
	t_coder		*coders;
	int			i;

	i = 0;
	coders = malloc(sizeof(t_coder) * args->nb_coders);
	if (!coders)
	{
		fprintf(stderr, "[ERROR]: Memory allocation for coders failed\n");
		return (NULL);
	}
	while (i < args->nb_coders)
	{
		coders[i].id = i + 1;
		coders[i].compiles_done = 0;
		coders[i].burnout = 0;
		coders[i].is_finished = 0;
		coders[i].has_request = 1;
		coders[i].last_start = data->starting_time;
		coders[i].left = &dongles[i];
		coders[i].right = &dongles[(i + 1) % args->nb_coders];
		pthread_mutex_init(&coders[i].c_mutex, NULL);
		i++;
	}
	return (coders);
}

int	initialize_datas(int ac, char **av, t_data *data)
{
	data->args = malloc(sizeof(t_args));
	if (!data->args)
	{
		fprintf(stderr, "[ERROR]: Memory allocation for args failed\n");
		return (-1);
	}
	if (parser(ac, av, data->args) == -1)
		return (-1);
	data->dongles = create_dongles(data->args);
	if (!data->dongles)
		return (-1);
	data->coders = create_coders(data, data->args, data->dongles);
	if (!data->coders)
		return (-1);
	return (0);
}
