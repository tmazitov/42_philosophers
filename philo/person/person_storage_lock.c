/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   person_storage_lock.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:43:30 by tmazitov          #+#    #+#             */
/*   Updated: 2024/04/05 12:59:51 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "person.h"

void	ps_lock(t_person_storage *storage)
{
	pthread_mutex_lock(&storage->locker);
	storage->locker_is_enabled = true;
}

void	ps_unlock(t_person_storage *storage)
{
	storage->locker_is_enabled = false;
	pthread_mutex_unlock(&storage->locker);
}
