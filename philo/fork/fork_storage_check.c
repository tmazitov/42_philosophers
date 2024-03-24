/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_storage_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:20:34 by tmazitov          #+#    #+#             */
/*   Updated: 2024/03/21 16:40:35 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fork.h"

t_bool	fs_check_fork_pair(t_fork_storage *storage, int id_1, int id_2)
{
		return ((storage->free_forks[id_1 - 1] && 
			storage->free_forks[id_2 - 1]));
}