/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larchimb <larchimb@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 15:13:03 by larchimb          #+#    #+#             */
/*   Updated: 2026/08/03 15:13:03 by larchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>

typedef struct s_args
{
    int 	nb_coders;
    long	time_to_burnout;
    long	time_to_compile;
    long	time_to_debug;
    long	time_to_refractor;
    int 	compiles_required;
    long	dongle_cooldown;
    int 	scheduler; //0 = FIFO, 1 = EDF
}   t_args;

typedef struct s_dongle
{
    int state; //0 available, 1 locked
    long last_release;
    pthread_mutex_t mutex;
}   t_dongle;

typedef struct s_coder
{
    pthread_t   coder;
    int         id;
    int         compiles_done;
    char        *state;
    long        last_start;
    t_dongle    *left;
    t_dongle    *right;
}   t_coder;

int	check_scheduler(const char *str);
int check_values(t_args *args);
int	parser(int ac, char **av, t_args *args);

#endif
