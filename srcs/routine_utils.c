/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larchimb <larchimb@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/12 16:27:14 by larchimb          #+#    #+#             */
/*   Updated: 2026/08/14 14:11:34 by larchimb         ###   ########.fr       */
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

int	check_cooldowns(t_thread *thread)
{
	t_coder	*coder;
	long	left_release;
	long	right_release;
	long	cooldown;

	coder = &thread->data->coders[thread->i];
	left_release = coder->left->last_release;
	right_release = coder->right->last_release;
	cooldown = thread->data->args->dongle_cooldown;
	if (get_time_ms() - left_release > cooldown
		&& get_time_ms() - right_release > cooldown)
		return (1);
	return (0);
}

void	change_states(t_data *data, t_coder *coder)
{
	pthread_mutex_lock(&data->d_mutex);
	coder->left->state = 1;
	coder->right->state = 1;
	coder->left->last_release = get_time_ms();
	coder->right->last_release = get_time_ms();
	pthread_mutex_unlock(&data->d_mutex);
}
