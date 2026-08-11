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

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	if (data->coders)
	{
		while (i < data->args->nb_coders)
			pthread_mutex_destroy(&data->coders[i++].mutex);
		free(data->coders);
	}
	i = 0;
	if (data->dongles)
	{
		while (i < data->args->nb_coders)
			pthread_mutex_destroy(&data->dongles[i++].mutex);
		free(data->dongles);
	}
	if (data->args)
	{
		pthread_mutex_destroy(&data->stop_mutex);
		free(data->args);
	}
	free(data);
}

int main(int ac, char **av)
{
    t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	data->args = NULL;
	data->coders = NULL;
	data->dongles = NULL;
	data->stop = 0;
	if (initialize_data(ac, av, data) == -1)
	{
		free_all(data);
		return (1);
	}
	free_all(data);
	return (0);
}
