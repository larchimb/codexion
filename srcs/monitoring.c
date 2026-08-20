/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larchimb <larchimb@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 10:36:54 by larchimb          #+#    #+#             */
/*   Updated: 2026/08/20 10:00:43 by larchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	burnout_signal(t_data *data, int i)
{
	long	burnout;
	long	actual;
	t_coder	*coder;

	burnout = data->args->time_to_burnout;
	actual = get_time_ms();
	coder = &data->coders[i];
	pthread_mutex_lock(&coder->c_mutex);
	if (coder->is_finished == 0 && actual - coder->last_start >= burnout)
	{
		coder->burnout = 1;
		pthread_mutex_unlock(&coder->c_mutex);
		printf("%lld %d burned out\n", get_exec_time(data), coder->id);
		pthread_mutex_lock(&data->stop_mutex);
		data->stop = 1;
		pthread_mutex_unlock(&data->stop_mutex);
		return (-1);
	}
	pthread_mutex_unlock(&coder->c_mutex);
	return (0);
}

void	*time_checker(void *args)
{
	t_data	*data;
	int		i;

	data = (t_data *)args;
	while (read_stop(data) == 0)
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
