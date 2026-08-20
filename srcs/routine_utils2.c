/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larchimb <larchimb@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 15:00:19 by larchimb          #+#    #+#             */
/*   Updated: 2026/08/20 15:24:41 by larchimb         ###   ########.fr       */
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

void	lock_d_mutexes(t_coder *coder)
{
	if (coder->left == coder->right)
	{
		pthread_mutex_lock(&coder->left->d_mutex);
		return ;
	}
	if (coder->left < coder->right)
	{
		pthread_mutex_lock(&coder->left->d_mutex);
		pthread_mutex_lock(&coder->right->d_mutex);
	}
	else
	{
		pthread_mutex_lock(&coder->right->d_mutex);
		pthread_mutex_lock(&coder->left->d_mutex);
	}
}

void	unlock_d_mutexes(t_coder *coder)
{
	pthread_mutex_unlock(&coder->left->d_mutex);
	if (coder->left != coder->right)
		pthread_mutex_unlock(&coder->right->d_mutex);
}
