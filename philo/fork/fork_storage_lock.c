/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_storage_lock.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:12:38 by tmazitov          #+#    #+#             */
/*   Updated: 2024/04/05 13:02:17 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fork.h"

void	fs_lock(t_fork_storage *storage)
{
	pthread_mutex_lock(&storage->locker);
}

void	fs_unlock(t_fork_storage *storage)
{
	pthread_mutex_unlock(&storage->locker);
}
