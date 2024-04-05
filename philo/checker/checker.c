/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:41:58 by tmazitov          #+#    #+#             */
/*   Updated: 2024/04/05 13:17:45 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
#include <stdio.h>

static t_bool	is_person_alive(t_person *person)
{
	long long	last_meal;

	last_meal = get_person_meal(person);
	return ((t_bool)(diff(now(), last_meal) >= person->die_time));
}

static	void	print_dead_log(t_person_storage *storage, int id)
{
	long long	time;

	time = now() - storage->start;
	printf("%lli %d died\n", time, id);
}

void	*make_death(t_person_storage *storage, t_person *person)
{
	storage->dead_log = person->id;
	print_dead_log(storage, person->id);
	return (NULL);
}

static int	check_person(t_person *person, t_person_storage *storage)
{
	if (person->eat_limit != -1 && person->eat_count >= person->eat_limit)
		return (1);
	ps_lock(storage);
	if (is_person_alive(person))
	{
		make_death(storage, person);
		ps_unlock(storage);
		return (2);
	}
	ps_unlock(storage);
	return (0);
}

void	*run_person_checker(void *data)
{
	t_person_storage	*storage;
	t_person			*person;
	int					counter;
	int					checked;
	int					result;

	storage = (t_person_storage *)data;
	while (1)
	{
		checked = 0;
		counter = 0;
		while (storage->persons[counter])
		{
			person = storage->persons[counter];
			result = check_person(person, storage);
			if (result == 2)
				return (NULL);
			if (result != 1)
				checked++;
			counter++;
		}
		if (checked == 0)
			break ;
	}
	return (NULL);
}
