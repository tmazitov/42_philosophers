/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:52:03 by tmazitov          #+#    #+#             */
/*   Updated: 2024/04/05 14:14:26 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fork.h"

t_fork	*make_fork(int id)
{
	t_fork	*fork;

	fork = malloc(sizeof(t_fork));
	if (!fork)
		return (NULL);
	fork->id = id;
	fork->locker_is_enabled = false;
	fork->locker_is_created = false;
	if (pthread_mutex_init(&fork->locker, NULL) != 0)
		return (free_fork(fork));
	fork->locker_is_created = true;
	fork->last_owner = 0;
	return (fork);
}

void	*free_fork(t_fork *fork)
{
	if (!fork)
		return (NULL);
	if (fork->locker_is_created) 
		pthread_mutex_destroy(&fork->locker);
	free(fork);
	return (fork);
}
