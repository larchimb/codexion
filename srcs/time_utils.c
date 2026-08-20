/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larchimb <larchimb@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/12 09:22:10 by larchimb          #+#    #+#             */
/*   Updated: 2026/08/20 09:52:33 by larchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long long	get_time_ms(void)
{
	struct timespec	ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (ts.tv_sec * 1000LL + ts.tv_nsec / 1000000L);
}

long long	get_exec_time(t_data *data)
{
	long	actual_time;

	actual_time = get_time_ms();
	return (actual_time - data->starting_time);
}

void	add_time_ms(struct timespec *ts, long long time_to_add)
{
	clock_gettime(CLOCK_MONOTONIC, ts);
	ts->tv_nsec += time_to_add * 1000000L;
	if (ts->tv_nsec >= 1000000000L)
	{
		ts->tv_sec += 1;
		ts->tv_nsec -= 1000000000L;
	}
}
