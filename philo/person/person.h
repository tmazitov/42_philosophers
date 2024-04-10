/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   person.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:43:16 by tmazitov          #+#    #+#             */
/*   Updated: 2024/04/10 12:36:05 by tmazitov         ###   ########.fr       */
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
	long long		last_meal;
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
	long long		start;
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
long long			get_person_meal(t_person *person);
void				person_meal_lock(t_person *person);
void				person_meal_unlock(t_person *person);
int					is_someone_died(t_person *person);
int					person_wait(t_person *person, t_person_state state);
int					person_wait_pair(t_person *person, t_fork_storage *forks);
t_person			*person_relise_pair(t_person *p, t_fork_storage *forks);

// Person Storage
t_person_storage	*make_person_storage(int amount);
void				*free_person_storage(t_person_storage *storage);
void				ps_lock(t_person_storage *storage);
void				ps_unlock(t_person_storage *storage);

#endif