/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larchimb <larchimb@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 12:10:25 by larchimb          #+#    #+#             */
/*   Updated: 2026/08/03 12:10:25 by larchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	free_all(t_data *data)
{
	int	i;

	i = 0;
	if (data->coders)
	{
		while (i < data->args->nb_coders)
			pthread_mutex_destroy(&data->coders[i++].c_mutex);
		free(data->coders);
	}
	i = 0;
	if (data->dongles)
	{
		while (i < data->args->nb_coders)
			pthread_mutex_destroy(&data->dongles[i++].d_mutex);
		free(data->dongles);
	}
	if (data->args)
		free(data->args);
	pthread_mutex_destroy(&data->stop_mutex);
	pthread_mutex_destroy(&data->ticket_mutex);
	free(data);
}

static int	check_free(t_data *data, int error)
{
	if (error != 0)
	{
		free_all(data);
		return (-1);
	}
	return (0);
}

static int	threads_joined(t_data *data)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (i < data->thread_created)
	{
		pthread_join(data->coders[i].coder, NULL);
		if (data->coders[i++].is_finished == 1)
			result += 1;
	}
	pthread_mutex_lock(&data->stop_mutex);
	data->stop = 1;
	pthread_mutex_unlock(&data->stop_mutex);
	return (result);
}

int	main(int ac, char **av)
{
	t_data	*data;
	int		i;

	i = 0;
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (initialize_data_struc(data) == -1)
	{
		free(data);
		return (1);
	}
	if (check_free(data, initialize_datas(ac, av, data)) == -1)
		return (1);
	if (check_free(data,
			pthread_create(&data->monitor, NULL, time_checker, data)) == -1)
		return (1);
	while (i < data->args->nb_coders)
		if (create_thread(data, i++) == -1)
			break ;
	if (threads_joined(data) == data->args->nb_coders)
		fprintf(stdout, "[INFO]: Simulation finished\n");
	pthread_join(data->monitor, NULL);
	free_all(data);
	return (0);
}
