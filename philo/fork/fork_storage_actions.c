/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_storage_actions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 12:58:50 by tmazitov          #+#    #+#             */
/*   Updated: 2024/03/20 13:20:37 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fork.h"

static t_fork	*take_fork(t_fork *fork)
{
	fork_lock(fork);
	return (fork);
}

static void		put_fork(t_fork *fork)
{
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
	// printf("\twant to take %d\n", fork_id);
	return (take_fork(result_fork));
}

void	fs_put_pair(t_fork_pair pair)
{
	// printf("\tput %d %d\n", pair.left->id, pair.right->id);
	put_fork(pair.left);
	put_fork(pair.right);
}

bool	fs_check_fork(t_fork_storage *storage, int fork_id)
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