/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   person_storage_dead.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:47:42 by tmazitov          #+#    #+#             */
/*   Updated: 2024/02/17 14:50:22 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "person.h"

bool	ps_death_check(t_person	*person)
{
	t_person_storage	*storage;
	bool				is_died;

	storage = (t_person_storage *)person->storage;
	ps_lock(storage);
	is_died = storage->dead_log;
	ps_unlock(storage);
	return (is_died);
}

void	ps_death_set(t_person *person)
{
	t_person_storage	*storage;

	storage = (t_person_storage *)person->storage;
	ps_lock(storage);	
	storage->dead_log = true;
	ps_unlock(storage);
}