/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larchimb <larchimb@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 15:00:19 by larchimb          #+#    #+#             */
/*   Updated: 2026/08/20 09:53:45 by larchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	read_stop(t_data *data)
{
	pthread_mutex_lock(&data->stop_mutex);
	if (data->stop == 0)
	{
		pthread_mutex_unlock(&data->stop_mutex);
		return (0);
	}
	pthread_mutex_unlock(&data->stop_mutex);
	return (1);
}

int	read_coder(t_coder *coder)
{
	pthread_mutex_lock(&coder->c_mutex);
	if (coder->is_finished == 0)
	{
		pthread_mutex_unlock(&coder->c_mutex);
		return (0);
	}
	pthread_mutex_unlock(&coder->c_mutex);
	return (1);
}
