/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   person.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:43:16 by tmazitov          #+#    #+#             */
/*   Updated: 2024/03/26 17:06:54 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PERSON_H
# define PERSON_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>

# include "../fork/fork.h"
# include "../utils/utils.h"

typedef enum s_person_state
{
	SLEEPING	= 1,
	THINKING	= 2,
	EATING		= 3,
	TAKE_FORK	= 4,
	DIE			= 5,
}		t_person_state;

typedef struct s_person_time
{
	int		eat_dur;
	int		sleep_dur;
	int		die_time;
	int		eat_limit;
}		t_person_time;

typedef struct s_person
{
	int				id;
	pthread_t		thread_id;
	t_fork			*left_fork;
	t_fork			*right_fork;
	int				eat_dur;
	int				sleep_dur;
	int				die_time;
	int				eat_count;
	int				eat_limit;
	size_t			last_meal;
	size_t			start;
	void			*storage;
	t_fork_storage	*fork_storage;
	pthread_mutex_t	locker;
	t_bool			locker_is_created;
	t_bool			locker_is_enabled;
}		t_person;

typedef struct s_person_storage
{
	t_person		**persons;
	pthread_mutex_t	locker;
	t_bool			locker_is_created;
	t_bool			locker_is_enabled;
	int				dead_log;
	size_t			start;
}		t_person_storage;

// Person

t_person			*make_person(int id);
void				*free_person(t_person *person);
void				print_person(t_person *person);
int					print_person_state(t_person *person, t_person_state state);
void				set_time(t_person_storage *storage, t_person_time time);
void				set_forks(t_person_storage *storage, t_fork_storage *forks);
void				*person_behavior(void *data);
void				set_person_meal(t_person *person);
size_t				get_person_meal(t_person *person);
void				person_meal_lock(t_person *person);
void				person_meal_unlock(t_person *person);

// Person Storage

t_person_storage	*make_person_storage(int amount);
void				*free_person_storage(t_person_storage *storage);
void				ps_death_set(t_person *person);
void				ps_lock(t_person_storage *storage);
void				ps_unlock(t_person_storage *storage);

#endif