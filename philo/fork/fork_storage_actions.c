/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_storage_actions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 12:58:50 by tmazitov          #+#    #+#             */
/*   Updated: 2024/03/21 15:57:11 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fork.h"

static t_fork	*take_fork(t_fork_storage *storage, t_fork *fork)
{
	int id;

	id = fork->id;
	storage->free_forks[id-1] = false;
	fork_lock(fork);
	return (fork);
}

static void		put_fork(t_fork_storage *storage, t_fork *fork)
{
	int	id;

	id = fork->id;
	storage->free_forks[id-1] = true;
	fork_unlock(fork);
}

t_fork	*fs_take_fork(t_fork_storage *storage, int fork_id) 
{
	t_fork	**forks;
	t_fork	*result_fork;
	int		counter;
	
	counter = 0;
	if (fork_id > storage->amount || fork_id <= 0)
		return (NULL);
	forks = storage->forks;
	while (forks[counter])
	{
		if (forks[counter]->id == fork_id)
			result_fork = forks[counter]; 
		counter++;
	}
	return (take_fork(storage, result_fork));
}

void	fs_put_pair(t_fork_storage *storage, t_fork_pair pair)
{
	fs_lock(storage);
	put_fork(storage, pair.left);
	put_fork(storage, pair.right);
	fs_unlock(storage);
}

t_bool	fs_check_fork(t_fork_storage *storage, int fork_id)
{
	t_fork	**forks;
	int		counter;
	
	counter = 0;
	if (fork_id > storage->amount || fork_id <= 0)
		return (true);
	forks = storage->forks;
	while (forks[counter])
	{
		if (forks[counter]->id == fork_id)
			return (forks[counter]->locker_is_enabled); 
		counter++;
	}
	return (true);
}
