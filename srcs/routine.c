/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larchimb <larchimb@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 17:52:11 by larchimb          #+#    #+#             */
/*   Updated: 2026/08/14 10:32:52 by larchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	to_compile(t_thread *thread)
{
	t_coder	*coder;
	t_data	*data;

	coder = &thread->data->coders[thread->i];
	data = thread->data;
	pthread_cond_broadcast(&thread->data->cond);
	pthread_mutex_lock(&data->d_mutex);
	while (coder->left->state == 0 || coder->right->state == 0
			|| check_cooldowns(thread) == 0)
	{
		printf("%d dans la boucle \n", thread->i + 1);
		pthread_cond_wait(&data->cond, &data->d_mutex);
	}
	coder->last_start = get_time_ms();
	coder->left->state = 0;
	coder->right->state = 0;
	print_message(data, "is taken a dongle", coder->id);
	print_message(data, "is taken a dongle", coder->id);
	print_message(data, "is compiling", coder->id);
	coder->left->last_release = get_time_ms();
	coder->right->last_release = get_time_ms();
	pthread_mutex_unlock(&data->d_mutex);
	delay_to_sleep(data, data->args->time_to_compile);
	pthread_mutex_lock(&data->d_mutex);
	coder->left->state = 1;
	coder->right->state = 1;
	pthread_mutex_unlock(&data->d_mutex);
}

static void	to_debug(t_thread *thread)
{

	t_coder	*coder;
	t_data	*data;

	coder = &thread->data->coders[thread->i];
	data = thread->data;
	print_message(data, "is debugging", coder->id);
	delay_to_sleep(data, data->args->time_to_debug);
	pthread_cond_broadcast(&thread->data->cond);
}

static void	to_refactor(t_thread *thread)
{
	t_coder	*coder;
	t_data	*data;

	coder = &thread->data->coders[thread->i];
	data = thread->data;
	print_message(data, "is refactoring", coder->id);
	delay_to_sleep(data, data->args->time_to_refractor);
	coder->compiles_done += 1;
	pthread_cond_broadcast(&thread->data->cond);
}

static void	*routine(void *args)
{
	t_thread	*thread;
	t_coder		*coder;

	thread = (t_thread *)args;
	coder = &thread->data->coders[thread->i];
	while (thread->data->stop == 0 && coder->is_finished == 0)
	{
		to_compile(thread);
		pthread_cond_broadcast(&thread->data->cond);
		to_debug(thread);
		to_refactor(thread);
		if (coder->compiles_done == thread->data->args->compiles_required)
		{
			pthread_mutex_lock(&coder->c_mutex);
			coder->is_finished = 1;
			pthread_mutex_unlock(&coder->c_mutex);
		}
	}
	free(thread);
	return (NULL);
}

void	launch_routine(t_data *data, int index)
{
	t_thread	*thread;

	thread = malloc(sizeof(t_thread));
	if (!thread)
		return ;
	thread->data = data;
	thread->i = index;
	pthread_create(&data->coders[index].coder, NULL, routine, thread);
}
