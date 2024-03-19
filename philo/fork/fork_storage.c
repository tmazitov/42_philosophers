/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_storage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:46:56 by tmazitov          #+#    #+#             */
/*   Updated: 2024/03/19 13:11:17 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fork.h"

static int	feel_storage(t_fork_storage *storage)
{
	int	counter;

	storage->forks = malloc(sizeof(t_fork *) * (storage->amount + 1));
	if (!storage->forks)
		return (0);
	counter = 0;
	while (counter < storage->amount) 
	{
		storage->forks[counter] = make_fork(counter + 1);
		if (!storage->forks[counter])
			return (0);
		counter++;
	}
	storage->forks[counter] = NULL;
	return (1);
}

t_fork_storage	*make_fork_storage(int amount)
{
	t_fork_storage	*storage;

	storage = malloc(sizeof(t_fork_storage));
	if (!storage)
		return (NULL);
	storage->amount = amount;
	storage->free_amount = amount;
	storage->locker_is_created = false;
	if (pthread_mutex_init(&storage->locker, NULL) != 0)
		return (free_fork_storage(storage));
	storage->locker_is_created = true;
	storage->locker_is_enabled = false;
	if (!feel_storage(storage))
		return (free_fork_storage(storage));
	return (storage);
}

void	*free_fork_storage(t_fork_storage *storage)
{
	int	counter;

	if (!storage)
		return (NULL);
	if (storage->locker_is_created)
		pthread_mutex_destroy(&storage->locker);
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
