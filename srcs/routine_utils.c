/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larchimb <larchimb@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/12 16:27:14 by larchimb          #+#    #+#             */
/*   Updated: 2026/08/13 12:48:27 by larchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	print_message(t_data *data, char *sentence, int id)
{
	pthread_mutex_lock(&data->stop_mutex);
	if (data->stop == 1)
	{
		pthread_mutex_unlock(&data->stop_mutex);
		return ;
	}
	pthread_mutex_unlock(&data->stop_mutex);
	printf("%ld %d %s\n", get_exec_time(data), id, sentence);
}

void	delay_to_sleep(t_data *data, long delay)
{
	pthread_mutex_lock(&data->stop_mutex);
	if (data->stop == 1)
	{
		pthread_mutex_unlock(&data->stop_mutex);
		return ;
	}
	pthread_mutex_unlock(&data->stop_mutex);
	usleep(delay * 1000);
}

void	delay_cooldown(t_data *data, long delay)
{
	pthread_mutex_lock(&data->d_mutex);
	if (data->stop == 1)
	{
		pthread_mutex_unlock(&data->d_mutex);
		return ;
	}
	usleep(delay * 1000);
	pthread_mutex_unlock(&data->d_mutex);
}
