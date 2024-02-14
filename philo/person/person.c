/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   person.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:41:56 by tmazitov          #+#    #+#             */
/*   Updated: 2024/02/14 14:46:51 by tmazitov         ###   ########.fr       */
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
	return (person);
}

void	*free_person(t_person *person)
{
	if (!person)
		return (NULL);
	free(person);
	return (NULL);
}
