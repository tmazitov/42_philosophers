/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   person_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:09:05 by tmazitov          #+#    #+#             */
/*   Updated: 2024/03/20 18:58:23 by tmazitov         ###   ########.fr       */
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
		message = "sleeping";
	else if (state == THINKING)
		message = "thinking";
	else if (state == EATING)
		message = "eating";
	else if (state == DIE)
		message = "died";
	else if (state == TAKE_FORK)
		message = "has taken a fork";
	else
		return (0);
	storage = (t_person_storage*)person->storage;
	pthread_mutex_lock(&storage->locker);
	if (storage->dead_log && state != DIE)
	{
		pthread_mutex_unlock(&storage->locker);
		return (1);
	}
	time = now() - storage->start;
	printf("%li %d is %s\n", time, person->id, message);
	pthread_mutex_unlock(&storage->locker);
	return (0);
}
