/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_storage_lock.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:59:07 by tmazitov          #+#    #+#             */
/*   Updated: 2024/02/17 15:48:51 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fork.h"

void	fs_lock(t_fork_storage *storage)
{
	pthread_mutex_lock(&storage->locker);
	storage->locker_is_enabled = true;
}

void	fs_unlock(t_fork_storage *storage)
{
	pthread_mutex_unlock(&storage->locker);
	storage->locker_is_enabled = false;
}