/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:03:30 by tmazitov          #+#    #+#             */
/*   Updated: 2024/02/15 13:41:47 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_state *state)
{
	int counter;
	
	printf("Philo state: \n");	
	printf("\ttime to eat: %d\n", state->time_to_eat);	
	printf("\ttime to die: %d\n", state->time_to_die);	
	printf("\ttime to sleep: %d\n", state->time_to_sleep);
	printf("\tamount to eat: %d\n", state->eat_count);
	counter = 0;
	printf("\tphilosophers:\n");
	while (state->forks->forks[counter])
		print_fork(state->forks->forks[counter++]);
	counter = 0;
	printf("\tforks:\n");
	while (state->persons->persons[counter])
		print_person(state->persons->persons[counter++]);
}