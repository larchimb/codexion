/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larchimb <larchimb@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 17:52:11 by larchimb          #+#    #+#             */
/*   Updated: 2026/08/11 15:40:33 by larchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int to_compile()
{
	//compile puis envoie le signal de liberation des dongles
}


void dongles_availables(t_data *data, int i)
{
	t_dongle	actual_dongle;
	t_dongle	next_dongle;

	actual_dongle = data->dongles[i];
	next_dongle = data->dongles[(i + 1) % data->args->nb_coders;

	pthread_mutex_lock(actual_dongle.mutex);
	pthread_mutex_lock(next_dongle.mutex);
	while (actual_dongle.state == 1 && next_dongle.state == 1)
		pthread_cond_wait(&cond, &mutex) /// a modifier
	actual_dongle.state = 0;
	next_dongle.state = 0;
	pthread_mutex_unlock(actual_dongle.mutex);
	pthread_mutex_unlock(next_dongle.mutex);
}

int	thread_finished(t_data *data, t_coder coder)
{
	if (coder.compiles_done == data->args->compiles_required)
		coder.is_finished = 1;
}

void routine(void *dat, int i)
{
	t_data	*data;
	int		i;

	data = (t_data *)dat;
	while (data->stop == 0)
	{

			if (data->coders[i]->is_finished == 1)
			{
				i++;
				continue;
			}
			dongles_availables(data, i);
			to_compile(data->coders[i]);
			to_debug(data->coders[i]);
			to_refactoring(data->coders[i]);
			thread_finished(data, coders[i]);
		}
	}
}
