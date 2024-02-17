/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   person.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:43:16 by tmazitov          #+#    #+#             */
/*   Updated: 2024/02/17 12:33:13 by tmazitov         ###   ########.fr       */
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
	int			id;
	pthread_t	thread_id;
	t_fork		*left_fork;
	t_fork		*right_fork;
	int			eat_dur;
	int			sleep_dur;
	int			die_time;
	int			last_eat;
	int			eat_count;
	int			eat_limit;
	t_fork_storage	*fork_storage;
}		t_person;

typedef struct s_person_storage
{
	t_person	**persons;
}		t_person_storage;

// Person

t_person	*make_person(int id);
void		*free_person(t_person *person);
void		print_person(t_person *person);
void		print_person_state(t_person *person, t_person_state state);
void		set_time(t_person_storage *storage, t_person_time time);
void		set_forks(t_person_storage *storage, t_fork_storage *forks);
void		*person_behavior(void *data);


// Person Storage

t_person_storage	*make_person_storage(int amount);
void				*free_person_storage(t_person_storage *storage);

#endif