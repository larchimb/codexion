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

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <sys/time.h>

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
    pthread_mutex_t mutex; //For locking burnout statement
    int         id;
    int         compiles_done;
    int         burnout;
    char        *state;
    long        last_start;
    t_dongle    *left;
    t_dongle    *right;
}   t_coder;

typedef struct  s_data
{
    t_args      *args;
    t_dongle    *dongles;
    t_coder     *coders;
    int         stop;
}   t_data;

int	    check_scheduler(const char *str);
int     check_values(t_args *args);
int	    parser(int ac, char **av, t_args *args);
int	    initialize_data(int ac, char **av, t_data *data);
long	get_time_ms();

#endif
