/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   person_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:09:05 by tmazitov          #+#    #+#             */
/*   Updated: 2024/03/26 16:45:02 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "person.h"

void	print_person(t_person *person)
{
	printf("\t\tphilo %d: \n", person->id);
}

int	print_person_state(t_person *person, t_person_state state)
{
	char				*message;
	size_t				time;
	t_person_storage	*storage;

	if (state == SLEEPING)
		message = "is sleeping";
	else if (state == THINKING)
		message = "is thinking";
	else if (state == EATING)
		message = "is eating";
	else if (state == DIE)
		message = "died";
	else if (state == TAKE_FORK)
		message = "has taken a fork";
	else
		return (0);
	storage = (t_person_storage*)person->storage;
	ps_lock(storage);
	if (storage->dead_log)
		return (ps_unlock(storage), 1);	
	time = now() - storage->start;
	printf("%li %d %s\n", time, person->id, message);
	ps_unlock(storage);
	return (0);
}
