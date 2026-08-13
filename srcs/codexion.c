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
		free(data->dongles);
	if (data->args)
	{
		pthread_mutex_destroy(&data->stop_mutex);
		pthread_mutex_destroy(&data->d_mutex);
		free(data->args);
	}
	free(data);
}

static int	threads_joined(t_data *data)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (i < data->args->nb_coders)
	{
		pthread_join(data->coders[i].coder, NULL);
		if (data->coders[i++].is_finished == 1)
			result += 1;
	}
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
	data->args = NULL;
	data->coders = NULL;
	data->dongles = NULL;
	data->stop = 0;
	data->starting_time = get_time_ms();
	if (initialize_datas(ac, av, data) == -1)
	{
		free_all(data);
		return (1);
	}
	pthread_create(&data->monitor, NULL, time_checker, data);
	while (i < data->args->nb_coders)
		launch_routine(data, i++);
	if (threads_joined(data) == data->args->nb_coders)
		data->stop = 1;
	pthread_join(data->monitor, NULL);
	free_all(data);
	return (0);
}
