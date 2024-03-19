/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_storage_actions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 12:58:50 by tmazitov          #+#    #+#             */
/*   Updated: 2024/03/19 13:06:34 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fork.h"

static t_fork	*take_fork(t_fork_storage *storage, t_fork *fork)
{
	fork->free = false;
	storage->free_amount -= 1;
	return (fork);
}

static void	put_fork(t_fork_storage *storage, t_fork *fork)
{
	fork->free = true;
	storage->free_amount += 1;
}

t_fork	*fs_take_fork(t_fork_storage *storage)
{
	t_fork	**forks;
	int		counter;

	if (fs_check_free_forks(storage) == false)
		return (NULL);
	forks = storage->forks;
	counter = 0;
	while (forks[counter])
	{
		if (forks[counter]->free == true)
			return (take_fork(storage, forks[counter]));
		counter++;
	}
	return (NULL);
}

void	fs_put_pair(t_fork_storage *storage, t_fork_pair pair)
{
	fs_lock(storage);
	put_fork(storage, pair.left);
	put_fork(storage, pair.right);
	fs_unlock(storage);
}
