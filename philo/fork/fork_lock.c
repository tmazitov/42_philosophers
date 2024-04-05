/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_lock.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:51:00 by tmazitov          #+#    #+#             */
/*   Updated: 2024/04/05 13:03:10 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fork.h"

void	fork_lock(t_fork *fork)
{
	pthread_mutex_lock(&fork->locker);
	fork->locker_is_enabled = true;
}

void	fork_unlock(t_fork *fork)
{
	fork->locker_is_enabled = false;
	pthread_mutex_unlock(&fork->locker);
}
