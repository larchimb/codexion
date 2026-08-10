/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larchimb <larchimb@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 10:36:54 by larchimb          #+#    #+#             */
/*   Updated: 2026/08/10 15:18:47 by larchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long	get_time_ms()
{
	struct 	timeval tv;
    struct 	timezone tz;

	gettimeofday(&tv, &tz);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	*time_checker(void *data)
{
	t_data	*dat;
	int		i;
	long 	actual;
	long	burnout;

	dat = (t_data *)data;
	burnout = dat->args->time_to_burnout;
	while (dat->stop = 0)
	{
		i = 0;
		while (i < dat->args->nb_coders)
		{
			actual = get_time_ms();
			if (actual - dat->coders[i].last_start >= burnout)
			{
				pthread_mutex_lock(&dat->coders[i].mutex);
				dat->coders[i].burnout = 1;
				dat->stop = 1;
				pthread_mutex_unlock(&dat->coders[i].mutex);
			}
			i++;
		}
		usleep(1000)
	}
	return (NULL);
}

int	monitoring(t_data *data)
{
	pthread_t	monitor;

	pthread_create()
}