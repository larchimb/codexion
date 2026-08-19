/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larchimb <larchimb@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/12 16:27:14 by larchimb          #+#    #+#             */
/*   Updated: 2026/08/19 16:05:52 by larchimb         ###   ########.fr       */
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
	printf("%lld %d %s\n", get_exec_time(data), id, sentence);
	pthread_mutex_unlock(&data->stop_mutex);
}

void	delay_to_sleep(t_data *data, long long delay)
{
	long long	slept;
	long long	chunk;

	slept = 0;
	chunk = 100;
	while (slept < delay)
	{
		pthread_mutex_lock(&data->stop_mutex);
		if (data->stop == 1)
		{
			pthread_mutex_unlock(&data->stop_mutex);
			return ;
		}
		pthread_mutex_unlock(&data->stop_mutex);
		if (delay - slept < chunk)
			usleep((delay - slept) * 1000);
		else
			usleep(chunk * 1000);
		slept += chunk;
	}
}

int	check_cooldowns(t_data *data, int i)
{
	t_coder	*coder;
	long	left_release;
	long	right_release;
	long	cooldown;

	coder = &data->coders[i];
	left_release = coder->left->last_release;
	right_release = coder->right->last_release;
	cooldown = data->args->dongle_cooldown;
	if (get_time_ms() - left_release > cooldown
		&& get_time_ms() - right_release > cooldown)
		return (1);
	return (0);
}
int	check_states(t_coder *coder)
{
	if (&coder->left->state == &coder->right->state)
		return (0);
	if (coder->left->state == 0 || coder->right->state == 0)
		return (0);
	return (1);
}

void	change_states(t_data *data, t_coder *coder)
{
	if (coder->left->state == 1)
	{
		coder->left->state = 0;
		coder->right->state = 0;
		heap_pop(&coder->left->queue);
		heap_pop(&coder->right->queue);
		print_message(data, "has taken a dongle", coder->id);
		print_message(data, "has taken a dongle", coder->id);
		print_message(data, "is compiling", coder->id);
	}
	else
	{
		coder->left->state = 1;
		coder->right->state = 1;
		coder->left->last_release = get_time_ms();
		coder->right->last_release = get_time_ms();
	}
}
