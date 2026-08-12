/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larchimb <larchimb@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 10:36:54 by larchimb          #+#    #+#             */
/*   Updated: 2026/08/12 18:35:51 by larchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	burnout_signal(t_data *data, int i)
{
	long	burnout;
	long	actual;

	burnout = data->args->time_to_burnout;
	actual = get_time_ms();
	if (actual - data->coders[i].last_start >= burnout)
	{
		pthread_mutex_lock(&data->stop_mutex);
		data->coders[i].burnout = 1;
		data->stop = 1;
		pthread_mutex_unlock(&data->stop_mutex);
		print_message(get_exec_time(data), "burned out", data->coders[i]->id);
		return (-1);
	}
	return (0);
}

void	*time_checker(void *args)
{
	t_data	*data;
	int		i;

	data = (t_data *)args;
	while (data->stop == 0)
	{
		i = 0;
		while (i < data->args->nb_coders)
		{
			if (burnout_signal(data, i) == -1)
				break ;
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
