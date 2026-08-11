/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larchimb <larchimb@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 10:36:54 by larchimb          #+#    #+#             */
/*   Updated: 2026/08/11 14:05:05 by larchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	burnout_signal(t_data *dat, int i)
{
	long	burnout;
	long 	actual;

	burnout = dat->args->time_to_burnout;
	actual = get_time_ms();
	if (actual - dat->coders[i].last_start >= burnout)
	{
		pthread_mutex_lock(&dat->coders[i].mutex);
		pthread_mutex_lock(&dat->stop_mutex);
		dat->coders[i].burnout = 1;
		dat->stop = 1;
		pthread_mutex_unlock(&dat->stop_mutex);
		pthread_mutex_unlock(&dat->coders[i].mutex);
		return (-1);
	}
	return (0);
}

long	get_time_ms(void)
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

	dat = (t_data *)data;
	while (dat->stop == 0)
	{
		i = 0;
		while (i < dat->args->nb_coders)
		{
			if (burnout_signal(dat, i) == -1)
				break;
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

int	monitoring(t_data *data)
{
	pthread_t	monitor;

	pthread_create()
}