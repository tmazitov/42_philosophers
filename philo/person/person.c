/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   person.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:41:56 by tmazitov          #+#    #+#             */
/*   Updated: 2024/03/06 15:45:34 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "person.h"

t_person	*make_person(int id)
{
	t_person	*person;

	person = malloc(sizeof(t_person));
	if (!person)
		return (NULL);
	person->id = id;
	person->left_fork = NULL;
	person->right_fork = NULL;
	person->eat_dur = 0;
	person->sleep_dur = 0;
	person->die_time = 0;
	person->last_eat = 0;
	person->eat_count = 0;
	person->eat_limit = -1;
	person->storage = NULL;
	return (person);
}

void	*free_person(t_person *person)
{
	if (!person)
		return (NULL);
	free(person);
	return (NULL);
}
