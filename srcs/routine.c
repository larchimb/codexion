/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larchimb <larchimb@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 17:52:11 by larchimb          #+#    #+#             */
/*   Updated: 2026/08/19 18:05:03 by larchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	to_compile(t_data *data, t_coder *coder, int i)
{
	pthread_mutex_lock(&data->d_mutex);
	if (coder->has_request == 1)
		coder->has_request = 0;
	else
	push_request(data, coder);
	while (read_stop(data) == 0 && (check_priority(coder) == 0
			|| check_states(coder) == 0 || check_cooldowns(data, i) == 0))
	{
		add_time_ms(&data->ts, 1);
		pthread_cond_timedwait(&data->cond, &data->d_mutex, &data->ts);
	}
	pthread_mutex_lock(&coder->c_mutex);
	coder->last_start = get_time_ms();
	pthread_mutex_unlock(&coder->c_mutex);
	change_states(data, coder);
	pthread_mutex_unlock(&data->d_mutex);
	delay_to_sleep(data, data->args->time_to_compile);
	pthread_mutex_lock(&data->d_mutex);
	change_states(data, coder);
	pthread_cond_broadcast(&data->cond);
	pthread_mutex_unlock(&data->d_mutex);
}

static void	to_debug(t_thread *datas_index)
{
	t_coder	*coder;
	t_data	*data;

	coder = &datas_index->data->coders[datas_index->i];
	data = datas_index->data;
	print_message(data, "is debugging", coder->id);
	delay_to_sleep(data, data->args->time_to_debug);
}

static void	to_refactor(t_thread *datas_index)
{
	t_coder	*coder;
	t_data	*data;

	coder = &datas_index->data->coders[datas_index->i];
	data = datas_index->data;
	print_message(data, "is refactoring", coder->id);
	delay_to_sleep(data, data->args->time_to_refractor);
	pthread_mutex_lock(&data->stop_mutex);
	if (data->stop == 0)
		coder->compiles_done += 1;
	pthread_mutex_unlock(&data->stop_mutex);
}

static void	*routine(void *args)
{
	t_thread	*datas_index;
	t_coder		*coder;

	datas_index = (t_thread *)args;
	coder = &datas_index->data->coders[datas_index->i];
	while (read_stop(datas_index->data) == 0 && read_coder(coder) == 0)
	{
		to_compile(datas_index->data, coder, datas_index->i);
		to_debug(datas_index);
		to_refactor(datas_index);
		if (coder->compiles_done == datas_index->data->args->compiles_required)
		{
			pthread_mutex_lock(&coder->c_mutex);
			coder->is_finished = 1;
			pthread_mutex_unlock(&coder->c_mutex);
		}
	}
	free(datas_index);
	return (NULL);
}

int	create_thread(t_data *data, int index)
{
	t_thread	*datas_index;

	datas_index = malloc(sizeof(t_thread));
	if (!datas_index)
	{
		pthread_mutex_lock(&data->stop_mutex);
		data->stop = 1;
		pthread_mutex_unlock(&data->stop_mutex);
		fprintf(stderr, "[ERROR]: Memory allocation for thread struc"
			" from %d failed\n", index + 1);
		return (-1);
	}
	datas_index->data = data;
	datas_index->i = index;
	if (pthread_create(&data->coders[index].coder, NULL, routine, datas_index))
	{
		pthread_mutex_lock(&data->stop_mutex);
		data->stop = 1;
		pthread_mutex_unlock(&data->stop_mutex);
		fprintf(stderr, "[ERROR]: Thread %d failed\n", index + 1);
		free(datas_index);
		return (-1);
	}
	data->thread_created += 1;
	return (0);
}
