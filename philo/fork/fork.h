/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:42:03 by tmazitov          #+#    #+#             */
/*   Updated: 2024/02/17 11:59:57 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORK_H
# define FORK_H

# include <stdio.h>
# include <stdlib.h>

# include "../utils/utils.h"

typedef struct s_fork
{
	int 	id;
	bool	free;
}		t_fork;

typedef struct s_fork_storage 
{
	t_fork **forks;
	int		amount;
	int		free_amount;
}		t_fork_storage;

// Fork storage

t_fork_storage	*make_fork_storage(int amount);
void			*free_fork_storage(t_fork_storage *storage);
bool			check_free_forks(t_fork_storage *storage);


// Fork

t_fork	*make_fork(int id);
void	*free_fork(t_fork *fork);
void	print_fork(t_fork *fork);
#endif