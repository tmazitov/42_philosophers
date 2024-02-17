/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_storage_actions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 12:58:50 by tmazitov          #+#    #+#             */
/*   Updated: 2024/02/17 15:44:31 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fork.h"

static t_fork	*take_fork(t_fork_storage *storage, t_fork *fork)
{
	fork->free = false;
	storage->free_amount -= 1;
	return (fork);
}

static void		put_fork(t_fork_storage *storage, t_fork *fork)
{
	fork->free = true;
	storage->free_amount += 1;
}

t_fork_pair	fs_take_pair(t_fork_storage *storage)
{
	t_fork_pair	pair;
	t_fork		**forks;
	int			counter;

	pair.left = NULL;
	pair.right = NULL;
	if (fs_check_free_forks(storage) == false)
		return (pair);
	counter = 0;
	forks = storage->forks;
	while (forks[counter])
	{
		if (forks[counter]->free && !pair.left)
			pair.left = take_fork(storage, forks[counter]);
		else if (forks[counter]->free && !pair.right)
			pair.right = take_fork(storage, forks[counter]);
		if (pair.left && pair.right)
			break ;
		counter++;
	}
	return (pair);
}

void	fs_put_pair(t_fork_storage *storage, t_fork_pair pair)
{
	fs_lock(storage);
	put_fork(storage, pair.left);
	put_fork(storage, pair.right);
	fs_unlock(storage);
}