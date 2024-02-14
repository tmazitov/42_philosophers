/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:49:30 by tmazitov          #+#    #+#             */
/*   Updated: 2024/02/14 18:10:48 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_state	*make_state(int amount)
{
	t_state	*state;

	state = malloc(sizeof(t_state));
	if (!state)
		return (NULL);
	state->forks = make_fork_storage(amount);
	if (!state->forks)
		return (free_state(state));
	state->persons = make_person_storage(amount);
		return (free_state(state));
	return (state);
}

void	*free_state(t_state *state)
{
	if (!state)
		return (NULL);
	if (state->forks)
		free_fork_storage(state->forks);
	if (state->persons)
		free_person_storage(state->persons);
	free(state);
	return (NULL);
}