/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   person_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:09:05 by tmazitov          #+#    #+#             */
/*   Updated: 2024/02/17 10:56:16 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "person.h"

void	print_person(t_person *person)
{
	printf("\t\tphilo %d: \n", person->id);
}

void	print_person_state(t_person *person, t_person_state state)
{
	struct timeval	current_time;
	char			*message;

	if (state == SLEEPING)
		message = "sleeping";
	else if (state == THINKING)
		message = "thinking";
	else if (state == EATING)
		message = "eating";
	else if (state == DIE)
		message = "died";
	else if (state == TAKE_FORK)
		message = "has taken a fork";
	else
		return ;

  	gettimeofday(&current_time, NULL);
	printf("%ld %d is %s\n", current_time.tv_usec, person->id, message);
}