/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:21:04 by tmazitov          #+#    #+#             */
/*   Updated: 2024/03/20 11:53:30 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>

# include "./utils/utils.h"
# include "./person/person.h"
# include "./fork/fork.h"

typedef struct s_state
{
	int	philo_amount;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int eat_limit;

	t_fork_storage		*forks;
	t_person_storage	*persons;
}		t_state;


int		validate(int ac, char **av);
t_state	*make_state(char **av);
void	*free_state(t_state *state);

#endif