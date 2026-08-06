/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larchimb <larchimb@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 12:10:25 by larchimb          #+#    #+#             */
/*   Updated: 2026/08/03 12:10:25 by larchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	intialize(t_args *args)
{
	int		i;
	t_coder		*coders;
	t_dongle	*dongles;

	coders = malloc(sizeof(t_coder) * args->nb_coders);
	if (!coders)
		return (-1)
	dongles = malloc(sizeof(t_dongle) * args->nb_coders);
	if (!dongles)
	{
		free(coders);
		return (-1)
	}
	i = 0;
	
	while (i < args->nb_coders)
	{
	    dongles[i].state = 0;
	    dongles[i].last_release = 0;
	    pthread_mutex_init(&dongles[i].mutex, NULL);
	    i++;
	}
	i = 0;
	while (i < args->nb_coders)
	{
		tmp->id = i + 1;
		tmp->compiles_done = 0;
		tmp->state = "waiting";
		tmp->last_start = 0;
		coders[0] =
	}
}

int main(int ac, char **av)
{
    t_args  *args;

    args = malloc(sizeof(t_args));
    if (!args)
        return (1);
    if (parser(ac, av, args) == -1)
	{
		free(args);
		return (1);
	}
	free(args)
	return (0);
}