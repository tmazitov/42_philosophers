/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   person_behavior.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:02:13 by tmazitov          #+#    #+#             */
/*   Updated: 2024/04/10 12:52:37 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "person.h"

static t_person	*person_eat(t_person *person, t_fork_storage *forks)
{
	if (person_wait_pair(person, forks))
		return (NULL);
	if (print_person_state(person, TAKE_FORK))
		return (person_relise_pair(person, forks));
	if (print_person_state(person, TAKE_FORK))
		return (person_relise_pair(person, forks));
	set_person_meal(person);
	if (print_person_state(person, EATING))
		return (person_relise_pair(person, forks));
	if (person_wait(person, EATING))
		return (person_relise_pair(person, forks));
	person_relise_pair(person, forks);
	return (NULL);
}

static t_person	*person_sleep(t_person *person)
{
	if (print_person_state(person, SLEEPING))
		return (person);
	if (person_wait(person, SLEEPING))
		return (person);
	return (NULL);
}

int	is_someone_died(t_person *person)
{
	int					value;
	t_person_storage	*storage;

	storage = (t_person_storage *)person->storage;
	ps_lock(storage);
	if (!storage->dead_log && 
		diff(now(), person->last_meal) >= person->die_time)
		storage->dead_log = person->id;
	value = storage->dead_log;
	ps_unlock(storage);
	return (value);
}

static t_person	*person_think(t_person *person)
{
	if (print_person_state(person, THINKING))
		return (person);
	return (NULL);
}

void	*person_behavior(void *data)
{
	t_person			*person;
	t_fork_storage		*forks;

	person = (t_person *)data;
	forks = person->fork_storage;
	set_person_meal(person);
	if (forks->amount == 1)
		return (person_wait(person, DIE), NULL);
	if (person->id % 2 != 0)
		person_wait(person, EATING);
	while (true)
	{
		if (is_someone_died(person))
			break ;
		if (person->eat_limit != -1 && person->eat_count >= person->eat_limit)
			return (NULL);
		if (person_eat(person, forks))
			return (NULL);
		if (person_sleep(person))
			return (NULL);
		if (person_think(person))
			return (NULL);
	}
	return (NULL);
}
