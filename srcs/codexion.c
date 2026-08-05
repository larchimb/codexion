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