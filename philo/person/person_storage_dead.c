/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   person_storage_dead.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:47:42 by tmazitov          #+#    #+#             */
/*   Updated: 2024/03/20 14:54:20 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "person.h"

t_bool	ps_death_check(t_person	*person)
{
	t_person_storage	*storage;
	t_bool				is_died;

	storage = (t_person_storage *)person->storage;
	ps_lock(storage);
	is_died = storage->dead_log;
	ps_unlock(storage);
	return (is_died);
}

void	ps_death_set(t_person *person)
{
	t_person_storage	*storage;
	t_fork_storage		*storage_fork;
	t_fork				*fork;
	int					counter;
	
	storage = (t_person_storage *)person->storage;
	storage_fork = person->fork_storage;
	ps_lock(storage);
	storage->dead_log = true;
	ps_unlock(storage);
	counter = 0;
	while(storage_fork->forks[counter])
	{
		fork = storage_fork->forks[counter]; 
		if (fork->locker_is_enabled)
			pthread_mutex_unlock(&fork->locker);
		counter++;
	}
}
