/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   person.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:43:16 by tmazitov          #+#    #+#             */
/*   Updated: 2024/02/15 13:11:38 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PERSON_H
# define PERSON_H

# include <stdlib.h>
# include <stdio.h>
# include "../utils/utils.h"

typedef struct s_person
{
	int	id;
}		t_person;

typedef struct s_person_storage
{
	t_person	**persons;
}		t_person_storage;


t_person	*make_person(int id);
void		*free_person(t_person *person);
void		print_person(t_person *person);

t_person_storage	*make_person_storage(int amount);
void				*free_person_storage(t_person_storage *storage);

#endif