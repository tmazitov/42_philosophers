/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_storage_actions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 12:58:50 by tmazitov          #+#    #+#             */
/*   Updated: 2024/04/05 13:04:27 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fork.h"

static t_fork	*take_fork(t_fork *fork)
{
	fork_lock(fork);
	return (fork);
}

static void	put_fork(t_fork *fork)
{
	fork_unlock(fork);
}

t_fork	*fs_take_fork(t_fork_storage *storage, int fork_id)
{
	t_fork	*result_fork;
	int		counter;

	counter = 0;
	while (storage->forks[counter])
	{
		if (storage->forks[counter]->id == fork_id)
			result_fork = storage->forks[counter];
		counter++;
	}
	return (take_fork(result_fork));
}

t_bool	fs_check_fork(t_fork_storage *storage, int fork_id, int id)
{
	t_fork	*result_fork;
	int		counter;

	counter = 0;
	while (storage->forks[counter])
	{
		if (storage->forks[counter]->id == fork_id)
			result_fork = storage->forks[counter];
		counter++;
	}
	return (result_fork->last_owner == id);
}

void	fs_put_pair(int id, t_fork_storage *storage, t_fork_pair pair)
{
	if (storage->amount % 2 != 0 && id == storage->amount)
	{
		put_fork(pair.right);
		put_fork(pair.left);
	}
	else
	{
		put_fork(pair.left);
		put_fork(pair.right);
	}
}
