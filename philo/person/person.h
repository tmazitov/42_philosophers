/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   person.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:43:16 by tmazitov          #+#    #+#             */
/*   Updated: 2024/02/14 14:47:10 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PERSON_H
# define PERSON_H

# include <stdlib.h>
# include "../utils/utils.h"

typedef struct s_person
{
	int id;
}		t_person;

t_person	*make_person(int id)
void		*free_person(t_person *person);

#endif