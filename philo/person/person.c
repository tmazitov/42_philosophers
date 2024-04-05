/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   person.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:41:56 by tmazitov          #+#    #+#             */
/*   Updated: 2024/04/05 13:21:08 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "person.h"

static void	init_person(t_person *person)
{
	person->left_fork = NULL;
	person->right_fork = NULL;
	person->eat_dur = 0;
	person->sleep_dur = 0;
	person->die_time = 0;
	person->eat_count = 0;
	person->eat_limit = -1;
	person->storage = NULL;
	person->locker_is_created = false;
}

t_person	*make_person(int id)
{
	t_person	*person;

	person = malloc(sizeof(t_person));
	if (!person)
		return (NULL);
	init_person(person);
	if (pthread_mutex_init(&person->locker, NULL) != 0)
		return (free_person(person));
	person->locker_is_created = true;
	person->id = id;
	return (person);
}

void	*free_person(t_person *person)
{
	if (!person)
		return (NULL);
	if (person->locker_is_enabled)
		person_meal_unlock(person);
	if (person->locker_is_created)
		pthread_mutex_destroy(&person->locker);
	free(person);
	return (NULL);
}
