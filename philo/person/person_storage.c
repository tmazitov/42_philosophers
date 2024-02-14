/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   person_storage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 18:02:20 by tmazitov          #+#    #+#             */
/*   Updated: 2024/02/14 18:09:29 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "person.h"

t_person_storage	*make_person_storage(int amount)
{
	t_person_storage	*storage;
	int					counter;

	storage = malloc(sizeof(t_person_storage));
	if (!storage)
		return (NULL);
	storage->persons = malloc(sizeof(t_person *) * (amount + 1));
	if (!storage->persons)
		return (free_person_storage(storage));
	counter = 0;
	while (storage->persons[counter])
	{
		storage->persons[counter] = make_person(counter);
		if (!storage->persons[counter])
			return (free_person_storage(storage));
		counter++;
	}
	storage->persons[counter] = NULL;
	return (storage);
}

void	*free_person_storage(t_person_storage *storage)
{
	int counter;

	if (!storage)
		return (NULL);
	if (storage->persons)
	{
		counter = 0;
		while(storage->persons[counter])
		{
			free_person(storage->persons[counter]);
			counter++;
		}
		free(storage->persons);
	}
	free(storage);
	return (NULL);
}