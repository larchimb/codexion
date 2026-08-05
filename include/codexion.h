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

typedef struct s_args
{
    int 	nb_coders;
    long	time_to_burnout;
    long	time_to_compile;
    long	time_to_debug;
    long	time_to_refractor;
    int 	compiles_required;
    long	dongle_cooldown;
    int 	scheduler;
}
#endif