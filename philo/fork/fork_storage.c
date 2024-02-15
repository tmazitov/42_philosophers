/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_storage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:46:56 by tmazitov          #+#    #+#             */
/*   Updated: 2024/02/15 12:45:50 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fork.h"

t_fork_storage	*make_fork_storage(int amount)
{
	t_fork_storage	*storage;
	int				counter;

	storage = malloc(sizeof(t_fork_storage));
	if (!storage)
		return (NULL);
	storage->forks = malloc(sizeof(t_fork*) * (amount + 1));
	if (!storage->forks)
		return (free_fork_storage(storage));
	counter = 0;
	while (counter < amount) 
	{
		storage->forks[counter] = make_fork(counter+1);
		if (!storage->forks[counter])
			return (free_fork_storage(storage));
 		counter++;
	}
	storage->forks[counter] = NULL;
	return (storage);
}

void	*free_fork_storage(t_fork_storage *storage)
{
	int	counter;

	if (!storage)
		return (NULL);
	if (storage->forks)
	{
		counter = 0;
		while (storage->forks[counter])
		{
			free_fork(storage->forks[counter]);
			counter++;
		}
		free(storage->forks);
	}
	free(storage);
	return (NULL);
}
