/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:21:04 by tmazitov          #+#    #+#             */
/*   Updated: 2024/02/14 14:51:36 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "./utils/utils.h"
# include "./person/person.h"

typedef struct s_state
{
	philosophers	**t_person;
}		t_state;


int		validate(int ac, char **av);
t_state	*make_state();
void	*free_state(t_state *state);


#endif