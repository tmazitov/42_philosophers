/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   person_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:09:05 by tmazitov          #+#    #+#             */
/*   Updated: 2024/03/19 20:44:54 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "person.h"

void	print_person(t_person *person)
{
	printf("\t\tphilo %d: \n", person->id);
}

void	print_person_state(t_person *person, t_person_state state)
{
	char				*message;
	long long			time;
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
		return ;
	storage = (t_person_storage *)person->storage;
	ps_lock(storage);
	time = get_current_time() - storage->start;
	printf("%lli %d is %s\n", time, person->id, message);
	ps_unlock(storage);
}
