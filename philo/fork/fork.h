/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:42:03 by tmazitov          #+#    #+#             */
/*   Updated: 2024/02/15 13:13:03 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORK_H
# define FORK_H

# include <stdio.h>

# include "stdlib.h"

typedef struct s_fork
{
	int id;
}		t_fork;

typedef struct s_fork_storage 
{
	t_fork **forks;
	int		amount;
}		t_fork_storage;

// Fork storage

t_fork_storage	*make_fork_storage(int amount);
void			*free_fork_storage(t_fork_storage *storage);

// Fork

t_fork	*make_fork(int id);
void	*free_fork(t_fork *fork);
void	print_fork(t_fork *fork);
#endif