/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larchimb <larchimb@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/12 16:27:14 by larchimb          #+#    #+#             */
/*   Updated: 2026/08/12 18:39:12 by larchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	print_message(t_data *data, char *sentence, int id)
{
	pthread_mutex_lock(data->stop_mutex);
	if (data->stop == 1)
	{
		pthread_mutex_unlock(data->stop_mutex);
		return (NULL);
	}
	printf("%f %d %s", get_exec_time(data), id, sentence);
	pthread_mutex_unlock(data->stop_mutex);
}

void	delay_to_sleep(t_data *data, long delay)
{
	pthread_mutex_lock(data->stop_mutex);
	if (data->stop == 1)
	{
		pthread_mutex_unlock(data->stop_mutex);
		return (NULL);
	}
	usleep(delay);
	pthread_mutex_unlock(data->stop_mutex);
}
