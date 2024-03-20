/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:42:03 by tmazitov          #+#    #+#             */
/*   Updated: 2024/03/20 12:26:50 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORK_H
# define FORK_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

# include "../utils/utils.h"

typedef struct s_fork
{
	int 			id;
	pthread_mutex_t	locker;
	bool			locker_is_created;
	bool			locker_is_enabled;
}		t_fork;

typedef struct s_fork_pair {
	t_fork			*left;
	t_fork			*right;
}		t_fork_pair;

typedef struct s_fork_storage 
{
	t_fork 			**forks;
	int				amount;
}		t_fork_storage;

// Fork storage

t_fork_storage	*make_fork_storage(int amount);
void			*free_fork_storage(t_fork_storage *storage);
void			fs_put_pair(t_fork_pair pair);
t_fork			*fs_take_fork(t_fork_storage *storage, int fork_id);
bool			fs_check_fork(t_fork_storage *storage, int fork_id);

// Fork

t_fork	*make_fork(int id);
void	*free_fork(t_fork *fork);
void	fork_lock(t_fork *fork);
void	fork_unlock(t_fork *fork);
void	fork_print(t_fork *fork);
#endif