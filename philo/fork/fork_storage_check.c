/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_storage_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 11:48:56 by tmazitov          #+#    #+#             */
/*   Updated: 2024/03/19 13:13:41 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fork.h"

t_bool	fs_check_free_forks(t_fork_storage *storage)
{
	int		amount;
	t_bool	result;

	amount = storage->free_amount;
	result = (t_bool)(amount >= 1);
	return (result);
}
