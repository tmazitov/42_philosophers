/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:41:58 by tmazitov          #+#    #+#             */
/*   Updated: 2024/03/26 16:28:57 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
#include <stdio.h>

static t_bool	is_person_alive(t_person *person)
{
	size_t				last_meal;

	last_meal = get_person_meal(person);
	return ((t_bool)(diff(now(), last_meal) >= person->die_time));
}	

static	void	print_dead_log(t_person_storage *storage, int id)
{
	size_t	time;

	time = now() - storage->start;
	printf("%li %d died\n", time, id);
}

void	*run_person_checker(void *data)
{
	t_person_storage	*storage;
	t_person			*person;
	int					counter;

	storage = (t_person_storage*)data;
	while (1)
	{
		counter = 0;
		while (storage->persons[counter])
		{
			ps_lock(storage);
			person = storage->persons[counter];
			if (is_person_alive(person))
			{
				storage->dead_log = person->id;
				print_dead_log(storage, person->id);
				ps_death_set(person);
				ps_unlock(storage);
				return (NULL);
			}
			ps_unlock(storage);
			counter++;
		}
		ft_usleep(10);
	}
	return (NULL);
}
