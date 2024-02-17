/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_storage_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 11:48:56 by tmazitov          #+#    #+#             */
/*   Updated: 2024/02/17 15:24:48 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fork.h"

bool	fs_check_free_forks(t_fork_storage *storage)
{
	int		amount;
	bool	result;

	amount = storage->free_amount;
	result = (bool)(amount >= 2);
	return (result);
}