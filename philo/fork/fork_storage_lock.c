/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_storage_lock.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:18:02 by tmazitov          #+#    #+#             */
/*   Updated: 2024/03/21 18:37:27 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fork.h"

int	fs_lock(t_fork_storage *storage)
{
	pthread_mutex_lock(&storage->locker);
	storage->locker_is_enabled = true;
	return (0);
}

int	fs_unlock(t_fork_storage *storage)
{	
	storage->locker_is_enabled = false;
	return pthread_mutex_unlock(&storage->locker);
}