/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   person_storage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 18:02:20 by tmazitov          #+#    #+#             */
/*   Updated: 2024/03/26 17:09:03 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "person.h"

static void	init_person_storage(t_person_storage *storage)
{
	storage->locker_is_created = false;
	storage->persons = NULL;
	storage->dead_log = 0;
	storage->start = now();
}

t_person_storage	*make_person_storage(int amount)
{
	t_person_storage	*storage;
	int					counter;
	
	storage = malloc(sizeof(t_person_storage));
	if (!storage)
		return (NULL);
	init_person_storage(storage);
	if (pthread_mutex_init(&storage->locker, NULL) != 0)
		return (free_person_storage(storage));
	storage->locker_is_created = true;
	storage->persons = malloc(sizeof(t_person *) * (amount + 1));
	if (!storage->persons)
		return (free_person_storage(storage));
	counter = 0;
	while (counter < amount)
	{
		storage->persons[counter] = make_person(counter + 1);
		if (!storage->persons[counter])
			return (free_person_storage(storage));
		storage->persons[counter++]->storage = storage;
	}
	storage->persons[counter] = NULL;
	return (storage);
}

void	*free_person_storage(t_person_storage *storage)
{
	int	counter;

	if (!storage)
		return (NULL);
	if (storage->locker_is_enabled)
		ps_unlock(storage);
	if (storage->locker_is_created)
		pthread_mutex_destroy(&storage->locker);
	if (storage->persons)
	{
		counter = 0;
		while (storage->persons[counter])
		{
			free_person(storage->persons[counter]);
			counter++;
		}
		free(storage->persons);
	}
	free(storage);
	return (NULL);
}

void	set_time(t_person_storage *storage, t_person_time time)
{
	int			counter;
	t_person	**persons;

	counter = 0;
	persons = storage->persons;
	while (persons[counter])
	{
		persons[counter]->sleep_dur = time.sleep_dur;
		persons[counter]->eat_limit = time.eat_limit;
		persons[counter]->die_time = time.die_time;
		persons[counter]->eat_dur = time.eat_dur;
		counter++;
	}
}

void	set_forks(t_person_storage *storage, t_fork_storage *forks)
{
	int			counter;
	t_person	**persons;

	counter = 0;
	persons = storage->persons;
	while (persons[counter])
	{
		persons[counter]->fork_storage = forks;
		counter++;
	}
}
