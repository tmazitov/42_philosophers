/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   person_storage_dead.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:47:42 by tmazitov          #+#    #+#             */
/*   Updated: 2024/03/26 17:08:21 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "person.h"


void	ps_death_set(t_person *person)
{
	t_fork_storage		*storage_fork;
	t_fork				*fork;
	int					counter;
	
	storage_fork = person->fork_storage;
	counter = 0;
	while(storage_fork->forks[counter])
	{
		fork = storage_fork->forks[counter]; 
		if (fork->locker_is_enabled)
			fork_unlock(fork);
		counter++;
	}
}
	