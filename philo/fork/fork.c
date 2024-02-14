/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:52:03 by tmazitov          #+#    #+#             */
/*   Updated: 2024/02/14 18:01:48 by tmazitov         ###   ########.fr       */
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
	return (fork);
}

void	*free_fork(t_fork *fork)
{
	if (!fork)
		return (NULL);
	free(fork);
	return (fork);
}
