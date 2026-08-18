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

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_args
{
	int	nb_coders;
	int	time_to_burnout;
	int	time_to_compile;
	int	time_to_debug;
	int	time_to_refractor;
	int	compiles_required;
	int	dongle_cooldown;
	int	scheduler; //0 = FIFO, 1 = EDF
}	t_args;

typedef struct s_request
{
	int			coder_id;
	long long	ticket;
	long long	deadline;
}	t_request;

typedef struct s_heap
{
	t_request	heap[2];
	int			size;
}	t_heap;

typedef struct s_dongle
{
	int			state; //1 available, 0 locked
	long long	last_release;
	t_heap		queue;
}	t_dongle;

typedef struct s_coder
{
	pthread_t		coder;
	pthread_mutex_t	c_mutex; //For locking burnout statement
	int				id;
	int				compiles_done;
	int				burnout;
	int				is_finished;
	long long		last_start;
	t_dongle		*left;
	t_dongle		*right;
}	t_coder;

typedef struct s_data
{
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	d_mutex;
	pthread_cond_t	cond;
	pthread_t		monitor;
	t_args			*args;
	t_dongle		*dongles;
	t_coder			*coders;
	int				stop;
	long long		starting_time;
	struct timespec	ts;
	int				thread_created;
}	t_data;

typedef struct s_thread
{
	t_data	*data;
	int		i;
}	t_thread;

int			check_scheduler(const char *str);
int			check_values(t_args *args);
int			parser(int ac, char **av, t_args *args);
int			initialize_data_struc(t_data *data);
int			initialize_datas(int ac, char **av, t_data *data);
int			check_cooldowns(t_thread *datas_index);
int			create_thread(t_data *data, int index);
long long	get_time_ms(void);
long long	get_exec_time(t_data *data);
void		print_message(t_data *data, char *sentence, int id);
void		*time_checker(void *args);
void		delay_to_sleep(t_data *data, long long delay);
void		add_time_ms(struct timespec *ts, long long time_to_add);
void		change_states(t_data *data, t_coder *coder);

#endif
