/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:42:15 by tmazitov          #+#    #+#             */
/*   Updated: 2024/03/27 12:54:53 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include "../utils/utils.h"
# include "../person/person.h"

void	*run_person_checker(void *data);
void	*make_death(t_person_storage *storage, t_person *person);
#endif // !CHECKER_H