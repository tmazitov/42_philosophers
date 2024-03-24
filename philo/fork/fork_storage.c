/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_storage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:46:56 by tmazitov          #+#    #+#             */
/*   Updated: 2024/03/21 16:17:04 by tmazitov         ###   ########.fr       */
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
		storage->free_forks[counter] = true; 
		counter++;
	}
	storage->forks[counter] = NULL;
	return (1);
}

static void	init_fork_storage(t_fork_storage *storage)
{
	storage->locker_is_created = false;
	storage->locker_is_enabled = false;
}

t_fork_storage	*make_fork_storage(int amount)
{
	t_fork_storage	*storage;

	storage = malloc(sizeof(t_fork_storage));
	if (!storage)
		return (NULL);
	init_fork_storage(storage);
	if (pthread_mutex_init(&storage->locker, NULL) != 0)
		return (free_fork_storage(storage));
	storage->locker_is_created = true;
	storage->amount = amount;
	storage->free_forks = malloc(sizeof(t_bool) * amount);
	if (!storage->free_forks)
		return (free_fork_storage(storage));
	if (!feel_storage(storage))
		return (free_fork_storage(storage));
	return (storage);
}

void	*free_fork_storage(t_fork_storage *storage)
{
	int	counter;

	if (!storage)
		return (NULL);
	if (storage->locker_is_enabled)
		pthread_mutex_unlock(&storage->locker);
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
